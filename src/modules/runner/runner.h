#ifndef BIN_RUNNER_H
#define BIN_RUNNER_H
#include <string>
#include <filesystem>
#include "../config/config.h"
namespace runner{

    class ProjectBinRunner{
        std::string build_dir;
        public:
            ProjectBinRunner();
            void run_program(std::string arguments);
            void run_test(std::string test_name);
    };
    void run_binary(std::filesystem::path bin_path);
}


#endif