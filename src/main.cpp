#include "./modules/setup/setup.h";
#include <iostream>;
int main(int argc,char * argv[]){
    if(argc==0){
        
    }
    else{
        std::string first_argument(argv[1]);
        if(first_argument=="new"){
            std::string name="";
            std::cout << "Enter project name:";
            std::cin >> name;
            std::cout << '\n';
            setup::ProjectCreator creator= setup::ProjectCreator(name);
            creator.create();
        }
        if(first_argument=="init"){
            setup::ProjectInitializer initializer = setup::ProjectInitializer();
            initializer.init();
        }
    }
    return 0;
}