#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <filesystem>

namespace fs = std::filesystem;

void analyzeFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Cannot open: " << path << std::endl;
        return;
    }
    
    std::string line;
    int lineNum = 0;
    int todoCount = 0;
    int fixmeCount = 0;
    
    while (std::getline(file, line)) {
        ++lineNum;
        if (line.find("TODO") != std::string::npos) ++todoCount;
        if (line.find("FIXME") != std::string::npos) ++fixmeCount;
    }
    
    std::cout << path << ":\n";
    std::cout << "  Lines: " << lineNum << "\n";
    std::cout << "  TODO: " << todoCount << "\n";
    std::cout << "  FIXME: " << fixmeCount << "\n";
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: code_analyzer <file or directory>" << std::endl;
        return 1;
    }
    
    std::string target = argv[1];
    if (fs::is_directory(target)) {
        for (const auto& entry : fs::recursive_directory_iterator(target)) {
            if (entry.is_regular_file()) {
                auto ext = entry.path().extension();
                if (ext == ".cpp" || ext == ".h" || ext == ".py" || ext == ".js") {
                    analyzeFile(entry.path().string());
                }
            }
        }
    } else if (fs::is_regular_file(target)) {
        analyzeFile(target);
    } else {
        std::cerr << "Not a file or directory." << std::endl;
        return 1;
    }
    return 0;
}