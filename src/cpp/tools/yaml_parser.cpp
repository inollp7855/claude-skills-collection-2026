#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: yaml_parser <file.yaml>" << std::endl;
        return 1;
    }
    
    try {
        YAML::Node config = YAML::LoadFile(argv[1]);
        std::cout << "YAML parsed successfully." << std::endl;
        std::cout << "Top-level keys:" << std::endl;
        for (const auto& kv : config) {
            std::cout << " - " << kv.first.as<std::string>() << std::endl;
        }
    } catch (const YAML::Exception& e) {
        std::cerr << "YAML parse error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}