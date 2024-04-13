#ifndef JSON_H
#define JSON_H

#include <filesystem>
#include <stdexcept>
#include <variant>
#include <unordered_map>
#include "tokenizer/tokenizer.h"
#include <vector>

namespace json{
    class JSON;
    typedef std::unordered_map<std::string,JSON*> object;
    typedef std::vector<JSON*> array;

    class JSON{
        private:
            class tree_node;
            typedef std::unordered_map<std::string,tree_node*> json_object;
            typedef std::vector<tree_node*> json_array;
            class tree_node{
                public:
                    std::variant<json_object,json_array,std::string,int,long long,float,double> val;
                    ~tree_node();

            };
            class jsonParser{
                Tokenizer tokenizer;
                std::string json_string;
                token look_ahead;
                static tree_node* create_Node(json_object val);
                static tree_node* create_Node(json_array val);
                static tree_node* create_Node(std::string val);
                static tree_node* create_Node(double val);
                static tree_node* create_Node(float val);
                static tree_node* create_Node(long long val);
                static tree_node* create_Node(int val);
                public:
                    jsonParser(std::string json_string);
                    tree_node* parse();
                    json_object parseObject();
                    std::pair<std::string,tree_node*> parseField();
                    tree_node* parseLiteral();
                    token eat(t_type type);
            };
            class jsonViewer{
                tree_node* node;
                public:
                    jsonViewer();
                    jsonViewer(tree_node* view);
                    template <typename T> T& get();
                    //Use to access field in object using key and array element using index
                    //Error when used on object that's not compatible with used index type
                    jsonViewer operator[](std::string key);
                    jsonViewer operator[](uint32_t index);
                    
            };
            
            static std::string to_string_helper(tree_node* curr);
            
            tree_node* root;

        public:
            JSON();
            JSON(std::ifstream& json_file);
            JSON(std::string json_string);
            ~JSON();
            std::string to_string();
            std::string to_stringf();
            static JSON from_str(std::string json_string);
            static JSON open(std::filesystem::path json_file);
            //Use to access field in object using key and array element using index
            //Error when used on object that's not compatible with used index type
            JSON::jsonViewer operator[](std::string key);
    };

    // class JSON {
    //     private:
    //         class jsonParser{
    //             Tokenizer tokenizer;
    //             std::string json_string;
    //             token look_ahead;
    //             public:
    //                 jsonParser(std::string json_string);
    //                 json::object parse();
    //                 json::object parseObject();
    //                 std::pair<std::string,JSON*> parseField();
    //                 JSON* parseLiteral();
    //                 token eat(t_type type);
    //         };
    //         std::variant<json::object,json::array,std::string,int,long long,float,double> val;
    //         static JSON* create_JSON(json::object val);
    //         static JSON* create_JSON(json::array val);
    //         static JSON* create_JSON(std::string val);
    //         static JSON* create_JSON(double val);
    //         static JSON* create_JSON(float val);
    //         static JSON* create_JSON(long long val);
    //         static JSON* create_JSON(int val);
        //     static std::string to_string_helper(JSON* curr);
        // public:
            
        //     JSON();
        //     JSON(std::ifstream& json_file);
        //     JSON(std::string json_string);
        //     ~JSON();
        //     std::string to_string();
        //     std::string to_stringf();
        //     static JSON from_str(std::string json_string);
        //     static JSON open(std::filesystem::path json_file);
        //     //Use to get value of current field
        //     template <typename T> T& get();
        //     //Use to access field in object using key and array element using index
        //     //Error when used on object that's not compatible with used index type
        //     JSON& operator[](std::string key);
        //     JSON& operator[](uint32_t index);
            
    // };
    
    // class Node {
    //     public:
    //     std::variant<std::unordered_map<std::string,JSON*>,std::vector<JSON*>> a;
    // };

    // class Object_Node{
    //     std::unordered_map<std::string,std::variant<Object_Node*,Array_Node*,Value_Node*>> fields;
    // };

    // class Array_Node{
    //    std::vector<std::variant<Object_Node*,std::string,double,float,int,long long>> arr;
    // };

    // class Value_Node{
    //     std::variant<std::string,double,float,int,long long> val;
    //     //Use to get value of current field
    //     template <typename T> T get();
    // };

}



#endif