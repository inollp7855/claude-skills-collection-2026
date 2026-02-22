#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "skill_engine.h"
#include "file_processor.h"
#include "pattern_scanner.h"

namespace py = pybind11;
using namespace claude::skills;

PYBIND11_MODULE(claude_skills, m) {
    m.doc() = "Claude Skills C++ bindings for Python";
    
    // SkillEngine
    py::class_<SkillEngine>(m, "SkillEngine")
        .def(py::init<>())
        .def("load_config", &SkillEngine::loadConfig)
        .def("execute", &SkillEngine::execute)
        .def("list_skills", &SkillEngine::listSkills)
        .def("validate_skill", &SkillEngine::validateSkill);
    
    // FileProcessor (static методы)
    m.def("read_file", &FileProcessor::readFile);
    m.def("write_file", &FileProcessor::writeFile);
    m.def("copy_directory", &FileProcessor::copyDirectory);
    m.def("list_files", &FileProcessor::listFiles);
    m.def("file_exists", &FileProcessor::exists);
    m.def("create_directories", &FileProcessor::createDirectories);
    
    // PatternScanner
    py::class_<PatternScanner::Match>(m, "PatternMatch")
        .def_readonly("file_path", &PatternScanner::Match::filePath)
        .def_readonly("line_number", &PatternScanner::Match::lineNumber)
        .def_readonly("line_content", &PatternScanner::Match::lineContent)
        .def_readonly("pattern", &PatternScanner::Match::pattern);
    
    py::class_<PatternScanner>(m, "PatternScanner")
        .def_static("scan_directory", &PatternScanner::scanDirectory)
        .def_static("scan_file", &PatternScanner::scanFile)
        .def_static("scan_pattern", &PatternScanner::scanPattern);
}