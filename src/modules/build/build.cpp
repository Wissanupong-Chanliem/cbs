#include "build.h"

builder::ProjectBuilder::ProjectBuilder(){
    this->config.populate_config("./config.json");
}

bool builder::ProjectBuilder::build(){
    
    std::vector<config::SourceCode*> used_files;
    config::SourceCode* curr_file = &(this->config.src["main"]);
    std::queue<config::SourceCode*> file_queue;
    std::set<config::SourceCode*> added;
    file_queue.push(curr_file);
    while(!file_queue.empty()){
        curr_file = file_queue.front(); file_queue.pop();
        for(auto& depend_on :curr_file->dependencies){
            if(added.count(depend_on)){
                continue;
            }
            file_queue.push(depend_on);
            added.insert(depend_on);
        }
        
        used_files.push_back(curr_file);
        added.insert(curr_file);
    }
    this->compiler = CodeCompiler(used_files,this->config.out_dir.string());
    try{
        std::vector<std::string> obj_files = this->compiler.compile();
        this->linker = ObjectLinker(obj_files,this->config.out_dir.string());
        this->linker.start_linking();
    }
    catch(...){
        return false;
    }
    
    return true;
}

builder::CodeCompiler::CodeCompiler(){
    this->outdir = "";
}

builder::CodeCompiler::CodeCompiler(std::vector<config::SourceCode*> files,std::string destination){
    this->files = files;
    this->outdir = destination;
}

std::vector<std::string> builder::CodeCompiler::compile(){
    std::vector<std::string> files;
    std::vector<std::string> compile_commands;
    if(!std::filesystem::exists(this->outdir)){
        std::filesystem::create_directories(this->outdir);
    }
    if(!std::filesystem::exists(this->outdir+"/obj")){
        std::filesystem::create_directories(this->outdir+"/obj");
    }
    for(auto& it:this->files){
        if(it->name.rfind("lib",0)==0){
            files.push_back(it->path.string());
            continue;
        }
        std::string dest_file = this->outdir+"/obj/"+it->name+".o";
        std::string command = "g++ -c -O"+std::to_string(it->optimization_level)+" "+it->path.string()+" -o "+dest_file;
        compile_commands.push_back(command);
        files.push_back(dest_file);
        
    }
    if(compile_commands.size()>0){
        try{
            
            std::string command = std::accumulate(compile_commands.begin(),compile_commands.end(),compile_commands[0],[](std::string a, std::string b){
                return a+" && "+b;
            });
            system(command.c_str());
        }
        catch(...){
            throw std::runtime_error("failed to compile program");
        }
    }
    
    return files;
}

builder::ObjectLinker::ObjectLinker(){
    this->outdir = "";
}

builder::ObjectLinker::ObjectLinker(std::vector<std::string>& paths,std::string destination){
    this->path_to_obj = paths;
    this->outdir = destination;
}

void builder::ObjectLinker::start_linking(){
    if(!std::filesystem::exists(this->outdir)){
        std::filesystem::create_directories(this->outdir);
    }
    if(!std::filesystem::exists(this->outdir+"/bin")){
        std::filesystem::create_directories(this->outdir+"/bin");
    }
    std::string command = "g++ -o "+this->outdir+"/bin/out";
    for(auto& it:this->path_to_obj){
        command += " " + it;
    }
    try{
        system(command.c_str());
    }
    catch(...){
        throw std::runtime_error("failed to link object file");
    }
}