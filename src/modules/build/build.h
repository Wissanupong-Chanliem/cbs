#ifndef BUILD_H
#define BUILD_H
#include "../config/config.h"
#include <Windows.h>
#include <unordered_map>
#include <queue>
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

    };

    class ProjectBuilder{
        config::BuildConfig config;
        CodeCompiler compiler;
        ObjectLinker linker;
        public:
            ProjectBuilder();
            int build();
    };
    
}

#endif