#pragma once

#include "types.hpp"

#include <string>

namespace aiko
{

    class Config
    {
    public:

        using GlobalConfig = aiko::AikoPtr<Config>;

        static void initGlobalConfig(int argc, char** argv);
        static GlobalConfig it();

        Config(const std::string resourcePath, const bool checkForBenchmarkOption);
        ~Config() = default;

        std::string getResourcePath() const;

        bool getCheckForBenchmarkOption() const;

    private:

        static GlobalConfig m_instance;

        int m_argc;
        char ** m_argv;

        const std::string m_ResourcePath;
        const bool m_CheckForBenchmarkOption;

    };

}

