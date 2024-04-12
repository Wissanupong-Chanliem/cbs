#ifndef JSON_H
#define JSON_H
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <variant>
#include <vector>
#include <unordered_map>

namespace json{
    
    class JSON {
        
        private:
            static class field_node{
                std::variant<std::unordered_map<std::string,field_node>,std::string> val;
            };
            field_node root;
        public:
            JSON(std::ifstream file);
            JSON(std::string json_string);
    };
    
    std::string to_string(JSON json_obj);
    JSON parse(std::ifstream file);
    JSON parse(std::string json_string);
}



#endif