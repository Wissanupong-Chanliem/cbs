#ifndef SETUP_H
#define SETUP_H
#include <fstream>
#include <iostream>
#include <filesystem>
#include <stdexcept>
using namespace std::filesystem;

namespace setup{
    class ProjectSetup{
        protected:
            std::string project_name = "";
            void get_config_string();
            void create_project_structure(std::string prefix);
            void set_project_name(std::string p_name);
    };

    class ProjectInitializer : private ProjectSetup {
        public:
            ProjectInitializer();
            bool init();
    };

    class ProjectCreator : private ProjectSetup{
        public:
            ProjectCreator(std::string name);
            bool create();
    };

}

#endif