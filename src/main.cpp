#include "./modules/setup/setup.h"
#include "./modules/config/config.h"
#include "./modules/build/build.h"
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
            builder::ProjectBuilder Builder = builder::ProjectBuilder();
            Builder.build();
        }
    }
    return 0;
}