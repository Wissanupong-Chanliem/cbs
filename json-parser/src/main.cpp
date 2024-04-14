#include <iostream>
#include "./modules/json.h"


int main(){
    json::JSON my_json = json::JSON::open("config.json");
    try{
        std::cout << my_json["src"]["json"]["dependencies"][0].get<std::string>() << '\n';
    }
    catch(std::runtime_error err){
        std::cout << err.what() << '\n';
    }
}