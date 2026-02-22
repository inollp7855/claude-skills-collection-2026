#include "skill_engine.h"
#include <yaml-cpp/yaml.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <thread>
#include <mutex>

namespace claude {
namespace skills {

namespace fs = std::filesystem;

class SkillEngine::Impl {
public:
    std::string skillsRoot;
    std::unordered_map<std::string, YAML::Node> skillConfigs;
    std::mutex configMutex;

    bool loadSkillConfig(const std::string& skillName) {
        std::lock_guard<std::mutex> lock(configMutex);
        std::string skillPath = skillsRoot + "/" + skillName;
        std::string skillMdPath = skillPath + "/SKILL.md";

        if (!fs::exists(skillMdPath)) {
            std::cerr << "SKILL.md not found: " << skillMdPath << std::endl;
            return false;
        }

        try {
            auto content = FileProcessor::readFile(skillMdPath);
            std::regex frontmatterRegex(R"(^---\s*\n(.*?)\n---\s*\n)",
                                        std::regex::multiline | std::regex::dotall);
            std::smatch match;
            if (std::regex_search(content, match, frontmatterRegex)) {
                std::string yamlStr = match[1].str();
                skillConfigs[skillName] = YAML::Load(yamlStr);
                return true;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error parsing SKILL.md for " << skillName << ": " << e.what() << std::endl;
        }
        return false;
    }

    std::string executeSkill(const std::string& skillName,
                            const std::unordered_map<std::string, std::string>& params) {
        auto it = skillConfigs.find(skillName);
        if (it == skillConfigs.end()) {
            if (!loadSkillConfig(skillName)) {
                return "Error: Skill '" + skillName + "' not found or invalid.";
            }
            it = skillConfigs.find(skillName);
        }

        const auto& config = it->second;
        std::string result;

        if (config["type"]) {
            std::string type = config["type"].as<std::string>();

            if (type == "cpp") {
                result = runCppBinary(skillName, params);
            } else if (type == "python") {
                result = runPythonScript(skillName, params);
            } else if (type == "js") {
                result = runNodeScript(skillName, params);
            } else {
                result = "Unknown skill type: " + type;
            }
        } else {
            result = "Skill config missing 'type' field";
        }

        return result;
    }

    std::string runCppBinary(const std::string& skillName,
                             const std::unordered_map<std::string, std::string>& params) {
        std::string binaryPath = skillsRoot + "/" + skillName + "/bin/" + skillName + ".exe";
        if (!fs::exists(binaryPath)) {
            return "Error: C++ binary not found for skill '" + skillName + "'";
        }

        std::string cmd = "\"" + binaryPath + "\"";
        for (const auto& [key, value] : params) {
            cmd += " --" + key + " \"" + value + "\"";
        }

        std::array<char, 128> buffer;
        std::string result;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
        if (!pipe) {
            return "Error: Failed to run binary";
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }
        return result;
    }

};

SkillEngine::SkillEngine() : pImpl(std::make_unique<Impl>()) {}
SkillEngine::~SkillEngine() = default;

bool SkillEngine::loadConfig(const std::string& skillPath) {
    pImpl->skillsRoot = skillPath;
    return true;
}

std::string SkillEngine::execute(const std::string& skillName,
                                const std::unordered_map<std::string, std::string>& params) {
    return pImpl->executeSkill(skillName, params);
}

std::vector<std::string> SkillEngine::listSkills() const {
    std::vector<std::string> skills;
    if (!fs::exists(pImpl->skillsRoot)) return skills;

    for (const auto& entry : fs::directory_iterator(pImpl->skillsRoot)) {
        if (entry.is_directory()) {
            std::string skillMdPath = entry.path().string() + "/SKILL.md";
            if (fs::exists(skillMdPath)) {
                skills.push_back(entry.path().filename().string());
            }
        }
    }
    return skills;
}

bool SkillEngine::validateSkill(const std::string& skillPath) const {
    std::string skillMdPath = skillPath + "/SKILL.md";
    if (!fs::exists(skillMdPath)) return false;

    try {
        auto content = FileProcessor::readFile(skillMdPath);
        std::regex frontmatterRegex(R"(^---\s*\n(.*?)\n---\s*\n)",
                                    std::regex::multiline | std::regex::dotall);
        std::smatch match;
        if (!std::regex_search(content, match, frontmatterRegex)) return false;

        YAML::Load(match[1].str());
        return true;
    } catch (...) {
        return false;
    }
}

} // namespace skills
} // namespace claude