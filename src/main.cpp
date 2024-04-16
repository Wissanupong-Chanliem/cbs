#include "./modules/setup/setup.h"
#include "./modules/build/build.h"
#include "./modules/runner/runner.h"
#include "./modules/config/config.h"
#include "./modules/test/test.h"
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
            std::cout << "Successfully create new project";
        }
        else if(first_argument=="init"){
            setup::ProjectInitializer initializer = setup::ProjectInitializer();
            initializer.init();
            std::cout << "Successfully initialize project";
        }
        else if(first_argument=="build"){
            builder::ProjectBuilder Builder = builder::ProjectBuilder();
            Builder.build();
        }
        else if(first_argument=="run"){
            std::string arguments = "";
            if(argc>2){
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
                std::cout << "Test Command : cbs test <test-name>";
                return 0;
            }
            std::string test_name = argv[2];
            std::cout << "building test \"" + test_name << "\"";
            test::TestBuilder Builder = test::TestBuilder();
            Builder.build(test_name);
            std::cout << " | finished\n";
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
            std::cout << "running test \"" + test_name << "\"\n";
            runner::ProjectBinRunner binrunner = runner::ProjectBinRunner();
            binrunner.run_test(test_name, arguments);
        }
    }
    return 0;
}