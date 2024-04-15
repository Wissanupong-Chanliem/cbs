#ifndef BUILD_H
#define BUILD_H
#include "../config/config.h"
#include <Windows.h>
#include <unordered_map>
#include <stdexcept>
#include <queue>
#include <numeric>
#include <algorithm>
#include <set>
namespace builder{

    class CodeCompiler{
        std::vector<config::SourceCode*> files;
        std::string outdir;
        public:
            CodeCompiler();
            CodeCompiler(std::vector<config::SourceCode*> files,std::string destination);
            std::vector<std::string> compile();
    };

    class ObjectLinker{
        std::vector<std::string> path_to_obj;
        std::string outdir;
        public:
            ObjectLinker();
            ObjectLinker(std::vector<std::string>& paths,std::string destination);
            void start_linking();
    };

    class ProjectBuilder{
        config::BuildConfig config;
        CodeCompiler compiler;
        ObjectLinker linker;
        public:
            ProjectBuilder();
            bool build();
    };
    
}

#endif