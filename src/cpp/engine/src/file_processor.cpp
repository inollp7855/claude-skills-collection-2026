#include "file_processor.h"
#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

namespace claude {
namespace skills {

std::string FileProcessor::readFile(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        return "";
    }
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    return content;
}

bool FileProcessor::writeFile(const std::string& path, const std::string& content) {
    std::ofstream file(path, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    file.write(content.data(), content.size());
    return true;
}

bool FileProcessor::copyDirectory(const std::string& src, const std::string& dst) {
    try {
        fs::copy(src, dst, fs::copy_options::recursive);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Copy error: " << e.what() << std::endl;
        return false;
    }
}

std::vector<std::string> FileProcessor::listFiles(const std::string& dir, 
                                                   const std::string& extension) {
    std::vector<std::string> files;
    if (!fs::exists(dir)) return files;
    
    for (const auto& entry : fs::recursive_directory_iterator(dir)) {
        if (entry.is_regular_file()) {
            if (extension.empty() || entry.path().extension() == extension) {
                files.push_back(entry.path().string());
            }
        }
    }
    return files;
}

bool FileProcessor::exists(const std::string& path) {
    return fs::exists(path);
}

bool FileProcessor::createDirectories(const std::string& path) {
    try {
        return fs::create_directories(path);
    } catch (...) {
        return false;
    }
}

} // namespace skills
} // namespace claude