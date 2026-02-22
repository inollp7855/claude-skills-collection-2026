name: code-reviewer
description: Automated code review with best practices for multiple languages. Use when you need thorough code analysis, bug detection, or style checking.
version: 2.1.0
author: Claude Skills Team
type: python 
tags: [development, code-quality, review, cpp, python, javascript]
allowed-tools: Read, Grep, Glob, Run

# Code Reviewer Skill

This skill performs comprehensive code review using a hybrid approach:
- **C++ engine** for fast pattern matching and AST analysis (when available)
- **Python scripts** for language-specific rules and formatting

## Installation Requirements

The skill requires the compiled C++ analyzer. Download from releases or build from source:

```bash
# Build C++ engine (requires CMake, C++17 compiler)
cd src/cpp/engine
mkdir build && cd build
cmake ..
make
cp cpp_analyzer ../../../skills/code-reviewer/bin/