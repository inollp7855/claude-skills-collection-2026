#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <nlohmann/json-schema.hpp>

using json = nlohmann::json;
using json_schema = nlohmann::json_schema::json_validator;

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: json_validator <schema.json> <instance.json>" << std::endl;
        return 1;
    }
    
    try {
        std::ifstream schemaFile(argv[1]);
        json schemaJson;
        schemaFile >> schemaJson;
        
        std::ifstream instanceFile(argv[2]);
        json instanceJson;
        instanceFile >> instanceJson;
        
        json_schema validator;
        validator.set_root_schema(schemaJson);
        
        validator.validate(instanceJson);
        std::cout << "JSON instance is valid against schema." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Validation error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}