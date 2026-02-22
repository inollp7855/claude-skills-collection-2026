#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>

namespace claude {
namespace skills {

class SkillEngine {
public:
    SkillEngine();
    virtual ~SkillEngine();

    bool loadConfig(const std::string& skillPath);

    std::string execute(const std::string& skillName,
                       const std::unordered_map<std::string, std::string>& params);

    std::vector<std::string> listSkills() const;

    bool validateSkill(const std::string& skillPath) const;

private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

class FileProcessor {
public:
    static std::string readFile(const std::string& path);
    static bool writeFile(const std::string& path, const std::string& content);
    static bool copyDirectory(const std::string& src, const std::string& dst);
    static std::vector<std::string> listFiles(const std::string& dir,
                                             const std::string& extension = "");
};

class PatternScanner {
public:
    struct Match {
        std::string filePath;
        size_t lineNumber;
        std::string lineContent;
        std::string pattern;
    };

    static std::vector<Match> scanDirectory(const std::string& dir,
                                            const std::string& pattern,
                                            bool recursive = true);

    static std::vector<Match> scanFile(const std::string& filePath,
                                       const std::string& pattern);
};

} // namespace skills
} // namespace claude