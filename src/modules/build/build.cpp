#include "build.h"

builder::ProjectBuilder::ProjectBuilder(){
    this->config.populate_config("./config.json");
}

int builder::ProjectBuilder::build(){
    
    std::vector<config::SourceCode*> used_files;
    config::SourceCode* curr_file = &(this->config.src["main"]);
    std::queue<config::SourceCode*> file_queue;
    file_queue.push(curr_file);
    while(!file_queue.empty()){
        curr_file = file_queue.front(); file_queue.pop();
        for(auto& depend_on :curr_file->dependencies){
            file_queue.push(depend_on);
        }
        
        used_files.push_back(curr_file);
    }

    this->compiler = CodeCompiler(used_files,this->config.out_dir.string());
    this->compiler.compile();
    return 1;
}

builder::CodeCompiler::CodeCompiler(){
    this->outdir = "";
}

builder::CodeCompiler::CodeCompiler(std::vector<config::SourceCode*> files,std::string destination){
    this->files = files;
    this->outdir = destination;
}

std::vector<std::string> builder::CodeCompiler::compile(){
    std::vector<std::string> obj_files;
    for(auto& it:this->files){
        std::string dest_file = this->outdir+"/obj/"+it->name+".o";
        std::string command = "/c g++ -c "+it->path.string()+" -o "+dest_file;
        ShellExecuteA(NULL,"open","cmd",command.c_str(),NULL,SW_HIDE);
        
    }
    return obj_files;
}