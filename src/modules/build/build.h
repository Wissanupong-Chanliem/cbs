#ifndef BUILD_H
#define BUILD_H
#include "../config/config.h"

namespace builder{

    class CodeCompiler{
        std::vector<const config::SourceCode&> files;
        public:
            CodeCompiler(std::vector<const config::SourceCode&> files);
            std::vector<std::string> compile();
    };

    class ObjectLinker{

    };

    class ProjectBuilder{
        config::BuildConfig config;
        public:
            ProjectBuilder();
    };
    
}

#endif