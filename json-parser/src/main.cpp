#include "./modules/tokenizer/tokenizer.h"
#include "./modules/json.h"


int main(){
    std::string json_string = "";
    std::ifstream file("./text.json");
    char letter;
    if(file.is_open()){
        while(!file.get(letter).eof()){
            json_string +=letter;
        }
    }
    file.close();
    try{
        Tokenizer tokenizer = Tokenizer("{\"abc\":-214.23}");
        while(!tokenizer.reach_the_end()){
            token current = tokenizer.get_next_token();
            switch (current.type){
                case DOUBLE:
                    std::cout << "Type: " << current.get_type_str() << " Value: " << std::get<double>(current.val) << '\n';
                    break;
                case FLOAT:
                    std::cout << "Type: " << current.get_type_str() << " Value: " << std::get<float>(current.val) << '\n';
                    break;
                case LONG:
                    std::cout << "Type: " << current.get_type_str() << " Value: " << std::get<long long>(current.val) << '\n';
                    break;
                case INT:
                    std::cout << "Type: " << current.get_type_str() << " Value: " << std::get<int>(current.val) << '\n';
                    break;
                default:
                    std::cout << "Type: " << current.get_type_str() << " Value: " << "\""<< std::get<std::string>(current.val)<< "\"" << '\n';
                    break;

            }
        }
    }
    catch(std::runtime_error err){
        std::cout<< "error:" << err.what() << '\n';
    }
    
    // json::JSON my_json = json::JSON::open("./config.json");
    // try{
    //     std::cout << my_json["src"]["test"]["dependencies"][0]["abc"].get<double>() << '\n';
    // }
    // catch(std::runtime_error err){
    //     std::cout << err.what() << '\n';
    // }
}