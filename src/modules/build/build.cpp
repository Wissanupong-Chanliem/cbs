#include "build.h"

builder::ProjectBuilder::ProjectBuilder(){
    this->config.populate_config("./config");
}

builder::CodeCompiler::CodeCompiler(std::vector<const config::SourceCode&> files){
    this->files=files;
}

std::vector<std::string> builder::CodeCompiler::compile(){
    
    for(auto& it:this->files){
        (it.path)
    }
}