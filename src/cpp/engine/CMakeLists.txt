cmake_minimum_required(VERSION 3.15)
project(ClaudeSkillsEngine VERSION 2.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(yaml-cpp REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(cxxopts REQUIRED)

include_directories(include)

add_library(skill_engine STATIC
    src/skill_engine.cpp
    src/file_processor.cpp
    src/pattern_scanner.cpp
)

target_link_libraries(skill_engine
    PRIVATE
        yaml-cpp::yaml-cpp
        nlohmann_json::nlohmann_json
        cxxopts::cxxopts
)

install(TARGETS skill_engine
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(DIRECTORY include/ DESTINATION include)