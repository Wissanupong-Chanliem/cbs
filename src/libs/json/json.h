#ifndef JSON_H
#define JSON_H
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <variant>
#include <unordered_map>
#include <stack>
#include <queue>
#include <math.h>
#include "tokenizer/tokenizer.h"

namespace json{
    
    class JSON {
        
        private:
            
            class jsonParser{
                Tokenizer tokenizer;
                std::string json_string;
                token look_ahead;
                public:
                    jsonParser(std::string json_string);
                    std::unordered_map<std::string,JSON*> parse();
                    std::unordered_map<std::string,JSON*> parseObject();
                    std::pair<std::string,JSON*> parseField();
                    JSON* parseLiteral();
                    token eat(t_type type);
            };
            std::variant<std::unordered_map<std::string,JSON*>,std::vector<JSON*>,std::string,double> val;
            static JSON* create_JSON(std::unordered_map<std::string,JSON*> val);
            static JSON* create_JSON(std::string val);
            static JSON* create_JSON(double val);
            static JSON* create_JSON(std::vector<JSON*> val);
            std::string to_string_helper(JSON* curr);
        public:
            JSON();
            JSON(std::ifstream& json_file);
            JSON(std::string json_string);
            std::string to_string();
            std::string to_stringf();
            static JSON from_str(std::string json_string);
            static JSON open(std::filesystem::path json_file);
            ~JSON();
            template <typename T> T get();
            //Use to access field in object using key
            //Error when used on value that's not object (ex. number, string, array)
            JSON& operator[](std::string key);
            JSON& operator[](uint32_t index);
    };
    

}



#endif