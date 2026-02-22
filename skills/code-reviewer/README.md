# Code Reviewer Skill

This skill performs automated code reviews using a hybrid C++/Python engine. It detects bugs, security issues, and style violations across multiple languages.

## Features
- Multi-language support: C++, Python, JavaScript, Java
- Configurable rule sets (security, performance, style)
- Integration with Claude's analysis tools

## Usage
Invoke via Claude:
> "Review the file `main.cpp` with the code-reviewer skill"

Or use the CLI:
```bash
python scripts/run_analyzer.py --file path/to/file --rules security,style