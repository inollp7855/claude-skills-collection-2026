# C++ Analyzer Skill

This skill uses a compiled C++ binary to perform deep static analysis on C++ code.

## Usage
Invoke from Claude:
> "Analyze src/main.cpp with cpp-analyzer"

Or directly via command line:
```bash
bin/cpp_analyzer.exe --file path/to/file.cpp --rules MEMORY_SAFETY,SECURITY