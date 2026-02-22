#pragma once
#include <string>
#include <vector>
#include <regex>

namespace claude {
namespace skills {

class PatternScanner {
public:
    struct Match {
        std::string filePath;
        size_t lineNumber;
        std::string lineContent;
        std::string pattern;
        std::vector<size_t> positions;
    };

    static std::vector<Match> scanDirectory(const std::string& dir,
                                            const std::string& pattern,
                                            bool recursive = true);
    
    static std::vector<Match> scanFile(const std::string& filePath,
                                       const std::string& pattern);

    static std::vector<uintptr_t> scanPattern(const std::vector<uint8_t>& data,
                                              const std::vector<uint8_t>& pattern,
                                              const std::string& mask);
};

} // namespace skills
} // namespace claude