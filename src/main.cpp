#include "./modules/setup/setup.h"
#include "./modules/config/config.h"
#include <iostream>
int main(int argc,char * argv[]){
    if(argc<=1){
        std::cout << "no arguments";
    }
    else{
        std::string first_argument(argv[1]);
        if(first_argument=="new"){
            std::string name="";
            std::cout << "Enter project name:";
            std::cin >> name;
            setup::ProjectCreator creator= setup::ProjectCreator(name);
            creator.create();
        }
        else if(first_argument=="init"){
            setup::ProjectInitializer initializer = setup::ProjectInitializer();
            initializer.init();
        }
        else if(first_argument=="build"){
            config::BuildConfig config = config::BuildConfig("./config.json");
            std::cout << config.src["main"].path << '\n';
        }
    }
    return 0;
}