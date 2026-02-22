#pragma once
#include <string>
#include <vector>
#include <filesystem>

namespace claude {
namespace skills {

class FileProcessor {
public:
    static std::string readFile(const std::string& path);
    
    static bool writeFile(const std::string& path, const std::string& content);
    
    static bool copyDirectory(const std::string& src, const std::string& dst);
    
    static std::vector<std::string> listFiles(const std::string& dir, 
                                              const std::string& extension = "");
    
    static bool exists(const std::string& path);
    
    static bool createDirectories(const std::string& path);
};

} // namespace skills
} // namespace claude