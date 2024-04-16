#include "setup.h"
using namespace setup;

void ProjectSetup::set_project_name(std::string p_name){
    this->project_name=p_name;
}

void ProjectSetup::create_project_structure(std::string prefix){
    //build folder
    if(exists(prefix+"/build")){
        for(auto& path:directory_iterator(prefix+"/build")){
            remove_all(path.path());
        }
    }
    else{
        create_directory(prefix+"/build");
    }
    create_directory(prefix+"/build/bin");
    create_directory(prefix+"/build/obj");

    //src
    if(exists(prefix+"/src")){
        for(auto& path:directory_iterator(prefix+"/src")){
            remove_all(path.path());
        }
    }
    else{
        create_directory(prefix+"/src");
    }
    create_directory(prefix+"/src/libs");
    create_directory(prefix+"/src/modules");
    create_directory(prefix+"/src/utils");
    create_directory(prefix+"/src/tests");
    std::ofstream main(prefix+"/src/main.cpp");
    std::string main_content = "#include <iostream>\n\n"
        "\nint main(){"
        "\n    std::cout << \"Hello, World\";"
        "\n    return 0;"
        "\n}";
    main << main_content;
    main.close();
    std::ofstream test(prefix+"/src/tests/example.cpp");
    std::string test_content = "#include <iostream>\n\n"
        "\nint main(){"
        "\n    std::cout << \"Hello, this is example test\";"
        "\n    return 0;"
        "\n}";
    test << test_content;
    test.close();
    //config json file
    std::ofstream config(prefix+"/config.json");
    std::string config_content = "{"
        "\n    \"project_name\":\""+this->project_name+"\","
        "\n    \"outdir\":\"./build\","
        "\n    \"src\":{"
        "\n        \"main\":{"
        "\n            \"path\":\"./src/main.cpp\","
        "\n            \"dependencies\":[],"
        "\n            \"optimization\":0"
        "\n        }"
        "\n    },"
        "\n    \"test\":{"
        "\n        \"example\":{"
        "\n            \"path\":\"./src/tests/example.cpp\","
        "\n            \"dependencies\":[],"
        "\n            \"optimization\":0"
        "\n        }"
        "\n    }"
        "\n}";
    config << config_content;
    config.close();
}

ProjectInitializer::ProjectInitializer(){
    this->set_project_name(current_path().filename().u8string());
}

bool ProjectInitializer::init(){
    this->create_project_structure(".");
    return 1;
}

ProjectCreator::ProjectCreator(std::string name){
    if(name.find('/')!=name.npos||name.find('\\')!=name.npos||name.find('.')!=name.npos){
        throw std::invalid_argument("Project name must not contain path segment.");
    }
    this->set_project_name(name);
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
    this->create_project_structure(this->project_name);
    return 1;
}