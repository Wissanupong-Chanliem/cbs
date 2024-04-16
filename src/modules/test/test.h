#ifndef TEST_H
#define TEST_H
#include "../config/config.h"
#include <Windows.h>
#include <unordered_map>
#include <stdexcept>
#include <queue>
#include <numeric>
#include <algorithm>
#include <set>
namespace test{
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
            void start_linking(std::string test_name);
    };

    class TestBuilder{
        config::BuildConfig config;
        CodeCompiler compiler;
        ObjectLinker linker;
        public:
            TestBuilder();
            bool build(std::string test_name);
    };
}

#endif