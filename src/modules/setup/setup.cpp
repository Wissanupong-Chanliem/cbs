#include "setup.h"
using namespace setup;

ProjectInitializer::ProjectInitializer(){
    this->project_name=current_path().filename().u8string();
}

void ProjectInitializer::create_project_structure(){

    //build folder
    if(exists("build")){
        for(auto& path:directory_iterator("build")){
            remove_all(path.path());
        }
    }
    else{
        create_directory("build");
    }
    create_directory("build/bin");
    create_directory("build/obj");

    //src
    if(exists("src")){
        for(auto& path:directory_iterator("src")){
            remove_all(path.path());
        }
    }
    else{
        create_directory("src");
    }
    create_directory("src/modules");
    create_directory("src/utils");
    create_directory("src/test");
    std::ofstream main("src/main.cpp");
    main.close();

    //config json file
    std::ofstream config("config.json");
    std::string config_content = "{"
        "\n    \"project_name\":\""+this->project_name+"\","
        "\n    \"outdir\":{"
        "\n        \"obj\":\"./build/obj\","
        "\n        \"bin\":\"./build/bin\""
        "\n    },"
        "\n    \"src\":{"
        "\n        \"program\":{"
        "\n            \"main\":\"./src/main.cpp\","
        "\n            \"dependencies\":[],"
        "\n            \"optimization\":0"
        "\n        },"
        "\n        \"test\":{"
        "\n            \"main\":\"./test/test.cpp\","
        "\n            \"dependencies\":[],"
        "\n            \"optimization\":0"
        "\n        }"
        "\n    }"
        "\n}";
    config << config_content;
    config.close();
}
bool ProjectInitializer::init(){
    this->create_project_structure();
    return 1;
}

ProjectCreator::ProjectCreator(std::string name){
    if(name.find('/')!=name.npos||name.find('\\')!=name.npos||name.find('.')!=name.npos){
        throw std::invalid_argument("Project name must not contain path segment.");
    }
    this->project_name=name;
}


void ProjectCreator::create_project_structure(){
    //build folder
    if(exists(this->project_name+"/build")){
        for(auto& path:directory_iterator(this->project_name+"/build")){
            remove_all(path.path());
        }
    }
    else{
        create_directory(this->project_name+"/build");
    }
    create_directory(this->project_name+"/build/bin");
    create_directory(this->project_name+"/build/obj");

    //src
    if(exists(this->project_name+"/src")){
        for(auto& path:directory_iterator(this->project_name+"/src")){
            remove_all(path.path());
        }
    }
    else{
        create_directory(this->project_name+"/src");
    }
    create_directory(this->project_name+"/src/modules");
    create_directory(this->project_name+"/src/utils");
    create_directory(this->project_name+"/src/test");
    std::ofstream main(this->project_name+"/src/main.cpp");
    main.close();

    //config json file
    std::ofstream config(this->project_name+"/config.json");
    std::string config_content = "{"
        "\n    \"project_name\":\""+this->project_name+"\","
        "\n    \"outdir\":{"
        "\n        \"obj\":\"./build/obj\","
        "\n        \"bin\":\"./build/bin\""
        "\n    },"
        "\n    \"src\":{"
        "\n        \"program\":{"
        "\n            \"main\":\"./src/main.cpp\","
        "\n            \"dependencies\":[],"
        "\n            \"optimization\":0"
        "\n        },"
        "\n        \"test\":{"
        "\n            \"main\":\"./test/test.cpp\","
        "\n            \"dependencies\":[],"
        "\n            \"optimization\":0"
        "\n        }"
        "\n    }"
        "\n}";
    config << config_content;
    config.close();
}

bool ProjectCreator::create(){
    if(exists(this->project_name)){
        char confirmation = false;
        while(true){
            std::cout << "Directory with the same name already existed\n";
            std::cout << "Overwrite? (Y/n): ";
            std::cin >> confirmation;        
            if(tolower(confirmation)=='y'){
                for(auto& path:directory_iterator(this->project_name)){
                    remove_all(path.path());
                }
                break;
            }
            else if(tolower(confirmation)=='n'){
                return 0;
            }
        }    
    }
    else{
        create_directory(this->project_name);
    }
    this->create_project_structure();
}