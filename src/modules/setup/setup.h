#ifndef SETUP_H
#define SETUP_H
#include <fstream>
#include <iostream>
#include <filesystem>
#include <stdexcept>
using namespace std::filesystem;

namespace setup{
    class ProjectInitializer{
        std::string project_name="";
        void create_project_structure();
        public:
            ProjectInitializer();
            bool init();
    };

    class ProjectCreator{
        std::string project_name="";
        void create_project_structure();
        public:
            ProjectCreator(std::string name);
            bool create();
    };

}

#endif