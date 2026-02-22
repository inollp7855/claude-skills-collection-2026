# Building C++ Components

The Claude Skills Collection includes high-performance C++ components that need to be compiled before use.

## Prerequisites

- **C++17 compiler** (MSVC 2019+, GCC 9+, Clang 10+)
- **CMake** 3.15+
- **vcpkg** (optional, for dependency management)
- **Python** 3.8+ (for bindings)

## Dependencies

The C++ engine uses:
- **yaml-cpp** - YAML parsing
- **cxxopts** - Command line argument parsing
- **nlohmann/json** - JSON handling (header-only)
- **pybind11** - Python bindings (optional)
- **node-addon-api** - Node.js bindings (optional)

### Install with vcpkg (recommended)

```bash
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.bat  # Windows
./vcpkg install yaml-cpp cxxopts nlohmann-json pybind11