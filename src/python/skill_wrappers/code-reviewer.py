#!/usr/bin/env python3
"""
Python wrapper for the C++ code reviewer.
Handles language-specific rules and formats output for Claude.
"""
import os
import sys
import json
import subprocess
import argparse
from pathlib import Path
from typing import Dict, List, Any
import yaml


class CodeReviewer:
    def __init__(self, config_path: str = None):
        self.config = self._load_config(config_path)
        self.cpp_analyzer_path = self._find_cpp_analyzer()

    def _load_config(self, config_path: str) -> Dict:
        """Load configuration from YAML file."""
        default_config = {
            "rules": {
                "cpp": ["MEMORY_SAFETY", "SECURITY", "PERFORMANCE"],
                "python": ["SECURITY", "STYLE"],
                "javascript": ["SECURITY", "PERFORMANCE"]
            }
        }

        if not config_path or not os.path.exists(config_path):
            return default_config

        with open(config_path, 'r', encoding='utf-8') as f:
            try:
                config = yaml.safe_load(f)
                return config or default_config
            except yaml.YAMLError:
                return default_config

    def _find_cpp_analyzer(self) -> Path:
        """Find the compiled C++ analyzer in the skill directory."""
        possible_paths = [
            Path(__file__).parent.parent / "skills" / "cpp-analyzer" / "bin" / "cpp_analyzer.exe",
            Path(__file__).parent.parent.parent / "dist" / "cpp_analyzer.exe",
            Path.cwd() / "cpp_analyzer.exe"
        ]

        for path in possible_paths:
            if path.exists():
                return path
        return None

    def review_file(self, file_path: str, language: str = "auto",
                    rules: List[str] = None, format: str = "json") -> Dict:
        """
        Review a single file using C++ analyzer or fallback to Python rules.
        """
        if language == "auto":
            language = self._detect_language(file_path)

        if rules is None:
            rules = self.config["rules"].get(language, ["DEFAULT"])

        if self.cpp_analyzer_path and language == "cpp":
            return self._run_cpp_analyzer(file_path, rules, format)

        return self._apply_python_rules(file_path, language, rules)

    def _run_cpp_analyzer(self, file_path: str, rules: List[str],
                          format: str) -> Dict:
        """Run the compiled C++ analyzer."""
        try:
            result = subprocess.run(
                [str(self.cpp_analyzer_path),
                 "--file", file_path,
                 "--rules", ",".join(rules),
                 "--output", format],
                capture_output=True,
                text=True,
                timeout=30
            )

            if result.returncode != 0:
                return {
                    "error": f"C++ analyzer failed: {result.stderr}",
                    "issues": []
                }

            if format == "json":
                return json.loads(result.stdout)
            else:
                return {
                    "output": result.stdout,
                    "issues": [] 
                }

        except (subprocess.TimeoutExpired, FileNotFoundError, json.JSONDecodeError) as e:
            return {
                "error": f"Failed to run C++ analyzer: {str(e)}",
                "issues": []
            }

    def _apply_python_rules(self, file_path: str, language: str,
                            rules: List[str]) -> Dict:
        """Apply Python-based rules as fallback."""
        issues = []

        if language == "python":
            with open(file_path, 'r', encoding='utf-8') as f:
                lines = f.readlines()
                for i, line in enumerate(lines, 1):
                    if "eval(" in line and "SECURITY" in rules:
                        issues.append({
                            "file": file_path,
                            "line": i,
                            "severity": "critical",
                            "rule": "EVAL_USAGE",
                            "message": "Use of eval() is dangerous",
                            "suggestion": "Avoid eval() - use safer alternatives"
                        })

        return {
            "summary": {
                "files": 1,
                "issues": len(issues)
            },
            "issues": issues
        }

    def _detect_language(self, file_path: str) -> str:
        """Detect programming language from file extension."""
        ext = Path(file_path).suffix.lower()
        mapping = {
            '.cpp': 'cpp', '.cxx': 'cpp', '.cc': 'cpp', '.h': 'cpp',
            '.py': 'python',
            '.js': 'javascript', '.jsx': 'javascript',
            '.ts': 'typescript',
            '.java': 'java',
            '.rs': 'rust'
        }
        return mapping.get(ext, 'unknown')


def main():
    parser = argparse.ArgumentParser(description="Claude Code Reviewer")
    parser.add_argument("--file", help="File to review")
    parser.add_argument("--dir", help="Directory to review")
    parser.add_argument("--language", default="auto",
                       help="Programming language")
    parser.add_argument("--rules", help="Comma-separated rules")
    parser.add_argument("--format", default="json",
                       choices=["text", "json", "markdown"],
                       help="Output format")
    parser.add_argument("--config", help="Path to config.yaml")

    args = parser.parse_args()

    reviewer = CodeReviewer(args.config)

    if not args.file and not args.dir:
        print(json.dumps({"error": "Either --file or --dir required"}))
        sys.exit(1)

    rules = args.rules.split(",") if args.rules else None

    if args.file:
        result = reviewer.review_file(args.file, args.language, rules, args.format)
    else:
        # Directory scan
        all_issues = []
        for root, _, files in os.walk(args.dir):
            for file in files:
                file_path = os.path.join(root, file)
                result = reviewer.review_file(file_path, args.language, rules, "json")
                if "issues" in result:
                    all_issues.extend(result["issues"])

        result = {
            "summary": {
                "files": len(all_issues),
                "issues": len(all_issues)
            },
            "issues": all_issues
        }

    if args.format == "json":
        print(json.dumps(result, indent=2))
    else:
        print(f"Found {result['summary']['issues']} issues\n")
        for issue in result.get('issues', []):
            print(f"[{issue['severity'].upper()}] {issue['file']}:{issue['line']}")
            print(f"  {issue['message']}")
            print(f"  Suggestion: {issue['suggestion']}\n")


if __name__ == "__main__":
    main()