#include "json.h"
using namespace json;

JSON::JSON(){
    this->val="";
}

JSON::JSON(std::ifstream& json_file){
    std::string json_string = "";
    char letter;
    if(json_file.is_open()){
        while(!json_file.get(letter).eof()){
            json_string +=letter;
        }
    }
    jsonParser parser = jsonParser(json_string);
    this->val = parser.parse();
}

JSON::JSON(std::string json_string){
    jsonParser parser = jsonParser(json_string);
    this->val = parser.parse();
}

JSON* JSON::create_JSON(std::unordered_map<std::string,JSON*> val){
    JSON* new_json = new JSON();
    new_json->val= val;
    return new_json;
}
JSON* JSON::create_JSON(std::string val){
    JSON* new_json = new JSON();
    new_json->val= val;
    return new_json;
}
JSON* JSON::create_JSON(double val){
    JSON* new_json = new JSON();
    new_json->val= val;
    return new_json;
}

JSON* JSON::create_JSON(std::vector<JSON*> val){
    JSON* new_json = new JSON();
    new_json->val= val;
    return new_json;
}

JSON::jsonParser::jsonParser(std::string json_string){
    this->json_string=json_string;
    this->tokenizer.add_json_string(json_string);
}

std::unordered_map<std::string,JSON*> JSON::jsonParser::parse(){
    look_ahead = this->tokenizer.get_next_token();
    return this->parseObject();
}

std::unordered_map<std::string,JSON*> JSON::jsonParser::parseObject(){
    this->eat(OPEN_BRACE);
    std::unordered_map<std::string,JSON*> fields;
    while(this->look_ahead.type!=CLOSE_BRACE){
        fields.insert(this->parseField());
        if(this->look_ahead.type!=CLOSE_BRACE){
            this->eat(COMMA);
        }
    }
    this->eat(CLOSE_BRACE);
    return fields;
}

std::pair<std::string,JSON*> JSON::jsonParser::parseField(){
    
    token field_name = this->eat(STRING_LITERAL);
    this->eat(COLON);
    JSON* value = this->parseLiteral();
    return std::make_pair(std::get<std::string>(field_name.val),value);
}

JSON* JSON::jsonParser::parseLiteral(){
    JSON* new_node = nullptr;
    switch(this->look_ahead.type){
        case OPEN_BRACE:{
            return create_JSON(this->parseObject());
        }
        case OPEN_BRACKET:{
            std::vector<JSON *> values;
            this->eat(OPEN_BRACKET);
            while (!this->tokenizer.reach_the_end() && this->look_ahead.type != CLOSE_BRACKET){
                values.push_back(this->parseLiteral());
                if (this->look_ahead.type == COMMA)
                {
                    this->eat(COMMA);
                }
            }
            this->eat(CLOSE_BRACKET);
            return create_JSON(values);
        }
        case FLOAT:
            new_node = create_JSON(std::get<float>(this->look_ahead.val));
            this->eat(FLOAT);
            return new_node;
        case DOUBLE:
            new_node = create_JSON(std::get<double>(this->look_ahead.val));
            this->eat(DOUBLE);
            return new_node;
        case INT:
            new_node = create_JSON(std::get<int>(this->look_ahead.val));
            this->eat(INT);
            return new_node;
        case LONG:
            new_node = create_JSON(std::get<long long>(this->look_ahead.val));
            this->eat(LONG);
            return new_node;
        default:
            new_node = create_JSON(std::get<std::string>(this->look_ahead.val));
            this->eat(STRING_LITERAL);
            return new_node;
    }
}

token JSON::jsonParser::eat(t_type type){
    token current = this->look_ahead;
    // if(current.val_is<double>()){
    //     std::cout << std::get<double>(current.val) << '\n';
    // }
    // else if(current.val_is<std::string>()){
    //     std::cout << "\""<< std::get<std::string>(current.val)<< "\"" << '\n';
    // }
    if (current.type != type){
        //std::cout << "Unexpected Token of type " + this->look_ahead.get_type_str() + ". Expected: " + token::tokentype_to_string(type) + ".";
        throw std::runtime_error("Unexpected Token of type " + this->look_ahead.get_type_str() + ". Expected: " + token::tokentype_to_string(type) + ".");
    }
    
    this->look_ahead = this->tokenizer.get_next_token();
    return current;
}


JSON::~JSON(){
    if(std::holds_alternative<std::unordered_map<std::string, JSON*>>(this->val)){
        std::unordered_map<std::string, JSON*> child_map = std::get<std::unordered_map<std::string, JSON*>>(this->val);
        for (auto &it : child_map){
            std::cout << "Deleting Object " << it.first << '\n';
            delete it.second;
        }
    }
    else if(std::holds_alternative<std::vector<JSON*>>(this->val)){
        std::vector<JSON*> array = std::get<std::vector<JSON*>>(this->val);
        for (int i=0;i<array.size();i++){
            std::cout << "Deleting Array"  << '\n';
            delete array[i];
        }
    }
    else if (std::holds_alternative<double>(this->val)){
        double number = std::get<double>(this->val);
        double int_part;
        if(std::modf(number,&int_part)!=0){
            std::cout << "Delete number: " << number << '\n';
        }
        else{
            std::cout << "Delete number: " << std::to_string((int) int_part) << '\n';
        }
    }
    else if (std::holds_alternative<std::string>(this->val)){
        std::cout << "Delete string: " << std::get<std::string>(this->val) << '\n';
    }
}
std::string JSON::to_string_helper(JSON* curr){
    std::string out = "";

    if (std::holds_alternative<std::unordered_map<std::string, JSON*>>(curr->val)){
        std::unordered_map<std::string, JSON*> child_map = std::get<std::unordered_map<std::string, JSON*>>(curr->val);
        int counter = 0;
        out+="{";
        for (auto& it:child_map){
            out+=it.first+":"+to_string_helper(it.second);
            if(counter<child_map.size()-1){
                out+=",";
            }
            counter++;
        }
        out+="}";
    }
    else if (std::holds_alternative<std::vector<JSON*>>(curr->val)){
        std::vector<JSON*> array = std::get<std::vector<JSON*>>(curr->val);
        out+="[";
        for (int i=0;i<array.size();i++){
            out+=to_string_helper(array[i]);
            if(i<array.size()-1){
                out+=",";
            }
        }
        out+="]";
    }
    else if (std::holds_alternative<double>(curr->val)){
        double number = std::get<double>(curr->val);
        double int_part;
        if(std::modf(number,&int_part)!=0){
            out+=number;
        }
        else{
            out+=std::to_string((int) int_part);
        }
    }
    else if (std::holds_alternative<std::string>(curr->val)){
        out+="\""+std::get<std::string>(curr->val)+"\"";
    }
    return out;
}

std::string JSON::to_string(){
    return to_string_helper(this);
}

std::string JSON::to_stringf(){
    std::string json_string = to_string_helper(this);
    std::string fstring = "";
    int level = 0;
    bool in_array = false;
    for(int i=0;i<json_string.length();i++){
        switch(json_string[i]){
            case '[':
                in_array=true;
                fstring+=json_string[i];
                break;
            case ']':
                in_array=false;
                fstring+=json_string[i];
                break;
            case '{':
                if(!in_array){
                    fstring+=json_string[i];
                    fstring+='\n';
                    level++;
                    for(int j=0;j<level;j++){
                        fstring+="    ";
                    }
                }
                else{
                    fstring+=json_string[i];
                }
                break;
            case '}':
                
                if(!in_array){
                    fstring+='\n';
                    level--;
                    for(int j=0;j<level;j++){
                        fstring+="    ";
                    }
                }
                fstring+=json_string[i];
                
                break;
            case ',':
                fstring+=json_string[i];
                if(!in_array){
                    fstring+='\n';
                    for(int j=0;j<level;j++){
                        fstring+="    ";
                    }
                }
                break;
            default:

                fstring+=json_string[i];
                break;
        }
    }
    
    return fstring;
}

JSON JSON::from_str(std::string json_string){
    jsonParser parser = jsonParser(json_string);
    JSON new_json = JSON();
    new_json.val = parser.parse();
    return new_json;
}

JSON JSON::open(std::filesystem::path json_file){
    std::string json_string = "";
    std::ifstream file(json_file);
    char letter;
    if(file.is_open()){
        while(!file.get(letter).eof()){
            json_string +=letter;
        }
    }
    
    jsonParser parser = jsonParser(json_string);
    JSON new_json = JSON();
    new_json.val = parser.parse();
    return new_json;
}

template <typename T>
T JSON::get(){
    if(std::holds_alternative<T>(this->val)){
        return std::get<T>(this->val);
    }
    const std::string type_map[4] = {
        "Object",
        "Array",
        "String",
        "Number"
    };
    throw std::runtime_error("Mismatched type: Field contain value of type "+type_map[this->val.index()]+" Not "+ typeid(T).name());
}

template double JSON::get<double>();
template std::string JSON::get<std::string>();
template std::vector<JSON*> JSON::get<std::vector<JSON*>>();
template std::unordered_map<std::string, JSON*> JSON::get<std::unordered_map<std::string, JSON*>>();

JSON& JSON::operator[](std::string key){
    if (std::holds_alternative<std::unordered_map<std::string, JSON*>>(this->val)){
        auto map = std::get<std::unordered_map<std::string, JSON*>>(this->val);
        if(map.count(key)>0){
            return *((std::get<std::unordered_map<std::string, JSON*>>(this->val))[key]);
        }
        throw std::runtime_error("error: object does not contains key \""+key+"\".");
    }
    
    throw std::runtime_error("error: use of key on non-object type value.");
}
JSON& JSON::operator[](uint32_t index){
    if (std::holds_alternative<std::vector<JSON*>>(this->val)){
        auto vec = std::get<std::vector<JSON*>>(this->val);
        if(index>=0&&index<vec.size()){
            return *((std::get<std::vector<JSON*>>(this->val))[index]);
        }
        throw std::runtime_error("error: use of out of bound index.");
    }
    throw std::runtime_error("error: use of index on non-array type value.");
}