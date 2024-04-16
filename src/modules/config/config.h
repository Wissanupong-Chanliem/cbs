#ifndef CONFIG_H
#define CONFIG_H
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include "../../libs/json/json.h"


namespace config{
    class SourceCode{
        public:
            std::string name;
            std::filesystem::path path;
            std::vector<SourceCode*> dependencies;
            int optimization_level;
            SourceCode();
    };
    class BuildConfig{
        public:
            std::string project_name;
            std::filesystem::path out_dir;
            std::unordered_map<std::string,SourceCode> src;
            std::unordered_map<std::string,SourceCode> tests;
            BuildConfig();
            BuildConfig(std::filesystem::path config_path);
            void populate_config(std::filesystem::path config_path);
    };
    
}

#endif