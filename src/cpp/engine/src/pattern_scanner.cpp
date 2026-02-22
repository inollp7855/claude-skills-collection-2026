#include "pattern_scanner.h"
#include <fstream>
#include <regex>
#include <filesystem>

namespace fs = std::filesystem;

namespace claude {
namespace skills {

std::vector<PatternScanner::Match> PatternScanner::scanDirectory(
    const std::string& dir,
    const std::string& pattern,
    bool recursive) {
    
    std::vector<Match> results;
    std::regex re(pattern, std::regex::multiline);
    
    auto iterator = recursive ? fs::recursive_directory_iterator(dir) 
                              : fs::directory_iterator(dir);
    
    for (const auto& entry : iterator) {
        if (entry.is_regular_file()) {
            auto matches = scanFile(entry.path().string(), pattern);
            results.insert(results.end(), matches.begin(), matches.end());
        }
    }
    return results;
}

std::vector<PatternScanner::Match> PatternScanner::scanFile(
    const std::string& filePath,
    const std::string& pattern) {
    
    std::vector<Match> results;
    std::ifstream file(filePath);
    if (!file.is_open()) return results;
    
    std::regex re(pattern);
    std::string line;
    size_t lineNum = 0;
    
    while (std::getline(file, line)) {
        ++lineNum;
        std::smatch match;
        if (std::regex_search(line, match, re)) {
            Match m;
            m.filePath = filePath;
            m.lineNumber = lineNum;
            m.lineContent = line;
            m.pattern = pattern;
            results.push_back(m);
        }
    }
    return results;
}

std::vector<uintptr_t> PatternScanner::scanPattern(
    const std::vector<uint8_t>& data,
    const std::vector<uint8_t>& pattern,
    const std::string& mask) {
    
    std::vector<uintptr_t> results;
    size_t patternSize = pattern.size();
    if (patternSize == 0 || data.size() < patternSize) return results;
    
    for (size_t i = 0; i <= data.size() - patternSize; ++i) {
        bool found = true;
        for (size_t j = 0; j < patternSize; ++j) {
            if (mask[j] == 'x' && data[i + j] != pattern[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            results.push_back(i);
        }
    }
    return results;
}

} // namespace skills
} // namespace claude