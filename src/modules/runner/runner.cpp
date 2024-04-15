#include "runner.h"

runner::ProjectBinRunner::ProjectBinRunner(){
    config::BuildConfig config = config::BuildConfig("./config.json");
    this->build_dir = config.out_dir.string();
}

void runner::ProjectBinRunner::run_program(std::string arguments){
    std::filesystem::path p = std::filesystem::absolute(this->build_dir+"/bin/out");
    std::string command = p.string() + " " + arguments;
    system(command.c_str());
}

void runner::ProjectBinRunner::run_test(std::string test_name,std::string arguments){
    std::filesystem::path p = std::filesystem::absolute(this->build_dir+"/bin/tests/"+test_name);
    std::string command = p.string() + " " + arguments;
    system(command.c_str());
}

void runner::run_binary(std::filesystem::path bin_path){
    std::string command = bin_path.string();
    system(command.c_str());
}