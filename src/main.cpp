#include "./modules/setup/setup.h"
#include "./modules/build/build.h"
#include "./modules/runner/runner.h"
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
            builder::ProjectBuilder Builder = builder::ProjectBuilder();
            Builder.build();
        }
        else if(first_argument=="run"){
            std::string arguments = "";
            if(argc>=2){
                if(strcmp(argv[2],"-a")==0){
                    for(int i=3;i<argc;i++){
                        if(i>3){
                            arguments+=" ";
                        }
                        arguments+=std::string(argv[i]);
                    }

                }
            }
            runner::ProjectBinRunner binrunner = runner::ProjectBinRunner();
            binrunner.run_program(arguments);
        }
        else if(first_argument=="test"){
            if(argc<=2){
                std::cout << "cbs test <test-name>";
                return;
            }
            std::string test_name = argv[2];
            std::string arguments = "";
            if(argc>3){
                if(strcmp(argv[3],"-a")==0){
                    for(int i=4;i<argc;i++){
                        if(i>4){
                            arguments+=" ";
                        }
                        arguments+=std::string(argv[i]);
                    }

                }
            }
            runner::ProjectBinRunner binrunner = runner::ProjectBinRunner();
            binrunner.run_test(test_name,arguments);
        }
    }
    return 0;
}