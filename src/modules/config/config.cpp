#include "config.h"

config::BuildConfig::BuildConfig(){
    this->project_name="";
    this->out_dir="";
}

config::BuildConfig::BuildConfig(std::filesystem::path config_path){
    json::JSON config = json::JSON::open(config_path);
    this->project_name = config["project_name"].get<std::string>();
    this->out_dir = config["outdir"].get<std::string>();
    json::json_object src_segment = config["src"].get<json::json_object>();
    for(auto& it:src_segment){
        SourceCode curr;
        if(this->src.count(it.first)>0){
            curr = this->src[it.first];
        }
        else{
            curr = SourceCode();
        }
        curr.path=(*it.second)["path"].get<std::string>();
        curr.optimization_level=(*it.second)["optimization"].get<int>();
        json::json_array dependencies_list = (*it.second)["dependencies"].get<json::json_array>();
        curr.dependencies.reserve(dependencies_list.size());
        for(auto& dit:dependencies_list){
            std::string file_name = dit->get<std::string>();
            if(this->src.count(file_name)>0){
                curr.dependencies.push_back(&(this->src[file_name]));
                continue;
            }
            this->src[file_name]= SourceCode();
        }
        this->src[it.first]= curr;
    }
}


void config::BuildConfig::populate_config(std::filesystem::path config_path){
    json::JSON config = json::JSON::open(config_path);
    this->project_name = config["project_name"].get<std::string>();
    this->out_dir = config["outdir"].get<std::string>();
    json::json_object src_segment = config["src"].get<json::json_object>();
    for(auto& it:src_segment){
        SourceCode curr;
        if(this->src.count(it.first)>0){
            curr = this->src[it.first];
        }
        else{
            curr = SourceCode();
        }
        std::string source_path = (*it.second)["path"].get<std::string>();
        if(!std::filesystem::exists(source_path)){
            throw std::logic_error("Error reading source file path of \""+it.first+"\". make sure the path is valid.");
        }
        curr.path = source_path;
        try{
            curr.optimization_level=(*it.second)["optimization"].get<int>();
        }
        catch(...){
            throw std::logic_error("Error reading optimization level of \""+it.first+"\". make sure it's integer from 0 to 3.");
        }
        json::json_array dependencies_list;
        try{
            dependencies_list=(*it.second)["dependencies"].get<json::json_array>();
        }
        catch(...){
            throw std::logic_error("Error reading dependencies of \""+it.first+"\". make sure it's an array of string.");
        }
        curr.dependencies.reserve(dependencies_list.size());
        for(auto& dit:dependencies_list){
            std::string file_name = dit->get<std::string>();
            if(this->src.count(file_name)>0){
                curr.dependencies.push_back(&(this->src[file_name]));
                continue;
            }
            this->src[file_name] = SourceCode();
        }
        this->src[it.first] = curr;
    }
}

config::SourceCode::SourceCode(){
    this->path = "";
    this->optimization_level = 0;
}
