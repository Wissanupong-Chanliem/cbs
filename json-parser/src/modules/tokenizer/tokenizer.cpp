#include "tokenizer.h"


token::token(){
    this->type=UNDEFINED;
    this->val="";
}

token::token(t_type token_type,std::string value){
    this->type=token_type;
    this->val=value;
}

token::token(t_type token_type,float value){
    this->type=token_type;
    this->val=value;
}

token::token(t_type token_type,double value){
    this->type=token_type;
    this->val=value;
}

token::token(t_type token_type,char value){
    this->type=token_type;
    this->val=std::string(1,value);
}

token::token(t_type token_type,int value){
    this->type=token_type;
    this->val=value;
}

token::token(t_type token_type,long long value){
    this->type=token_type;
    this->val=value;
}

template<typename T> T token::get_val(){
    return std::get<T>(this->val);
}
template std::string token::get_val<std::string>();
template double token::get_val<double>();
template int token::get_val<int>();
template float token::get_val<float>();
template long long token::get_val<long long>();

template<typename A> bool token::val_is(){
    return std::holds_alternative<A>(this->val);
}

template bool token::val_is<std::string>();
template bool token::val_is<double>();
template bool token::val_is<int>();
template bool token::val_is<float>();
template bool token::val_is<long long>();

std::string token::get_type_str(){
    return tokentype_to_string(this->type);
}

std::string token::tokentype_to_string(t_type type){
    static std::unordered_map<t_type,std::string> TokenTypeString={
        {OPEN_BRACE,"OPEN_BRACE"},
        {CLOSE_BRACE,"CLOSE_BRACE"},
        {OPEN_BRACKET,"OPEN_BRACKET"},
        {CLOSE_BRACKET,"CLOSE_BRACKET"},
        {COLON,"COLON"},
        {COMMA,"COMMA"},
        {STRING_LITERAL,"STRING_LITERAL"},
        {FLOAT,"FLOAT"},
        {DOUBLE,"DOUBLE"},
        {INT,"INT"},
        {LONG,"LONG"},
        {END,"END"},
        {UNDEFINED,"UNDEFINED"}
    };
    return TokenTypeString[type];
}

Tokenizer::Tokenizer(){
    this->cursor=0;
    this->content="";
}

Tokenizer::Tokenizer(std::string json_string){
    this->cursor=0;
    this->content=json_string;
}

void Tokenizer::add_json_string(std::string json_string){
    this->content=json_string;
}

bool Tokenizer::reach_the_end(){
    return this->cursor>=this->content.length();
}

token Tokenizer::get_next_token(){
    while(!this->reach_the_end()&&isspace(this->content[this->cursor])){
        this->cursor++;
    }
    if(this->reach_the_end()){
        return token(END,"");
    }
    
    char current_char = this->content[this->cursor];
    switch(current_char){
        case '{':
            this->cursor++;
            return token(OPEN_BRACE,current_char);
        case '}':
            this->cursor++;
            return token(CLOSE_BRACE,current_char);
        case '[':
            this->cursor++;
            return token(OPEN_BRACKET,current_char);
        case ']':
            this->cursor++;
            return token(CLOSE_BRACKET,current_char);
        case ',':
            this->cursor++;
            return token(COMMA,current_char);
        case ':':
            this->cursor++;
            return token(COLON,current_char);
        default:
            if(std::isdigit(current_char)||current_char=='-'){
                std::string number = "";
                bool isfloat = false;
                int decimal_count = 0;
                do{ 
                    if(isfloat){
                        decimal_count+=1;
                    }
                    number+=current_char;
                    this->cursor++;
                    current_char = this->content[this->cursor];
                    if(current_char=='.'){
                        if(isfloat){
                            throw std::runtime_error("error: floating point value contain two or more decimal point.");
                        }
                        else{
                            isfloat=true;
                        }
                    }

                } while(std::isdigit(current_char)||current_char=='.');
                if(decimal_count==0){
                    if(isfloat){
                        number.pop_back();
                    }
                    if(number[0]=='-'){
                        if(number.compare(std::to_string(INT_MIN))<=0){
                            return token(INT,stoi(number));
                        }
                        else{
                            return token(LONG,stoll(number));
                        }
                    }
                    else{
                        if(number.compare(std::to_string(INT_MAX))<=0){
                            return token(INT,stoi(number));
                        }
                        else{
                            return token(LONG,stoll(number));
                        }
                    }
                }
                else{
                    if(decimal_count>7){
                        return token(DOUBLE,stod(number));
                    }
                    return token(FLOAT,stof(number));
                }
                
            }
            else if(current_char=='"'){
                this->cursor++;
                current_char = this->content[this->cursor];
                std::string string_literal = "";
                while(current_char!='"'||this->content[this->cursor-1]=='\\'){
                    if(current_char=='\\'){
                        this->cursor++;
                        current_char = this->content[this->cursor];
                    }
            
                    string_literal+=current_char;
                    this->cursor++;
                    if(this->reach_the_end()){
                        throw std::runtime_error("Unexpected end of string.");
                    }
                    current_char = this->content[this->cursor];
                }
                this->cursor++;
                return token(STRING_LITERAL,string_literal);
            }
            else{
                throw std::runtime_error("String contain unrecognized symbol. found:" + current_char);
            }
            
    }
    
}