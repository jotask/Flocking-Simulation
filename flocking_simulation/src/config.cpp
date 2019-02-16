#include "config.hpp"

#include "engine_utils.hpp"

#include <cassert>
#include <iostream>

namespace aiko
{

    Config::GlobalConfig Config::m_instance = nullptr;

    void Config::initGlobalConfig(int argc, char** argv)
    {
        // Check if benchmark mode is requested
        const auto benchmark = (argc > 1 && strcmp(argv[1], "-bm") == 0);

        assert(m_instance == nullptr);

        char *fullPath = argv[0];
        auto resourcePath = std::string(argv[0]);

        m_instance = std::make_shared<Config>(resourcePath, benchmark);

    }

    Config::GlobalConfig& Config::it()
    {
        assert(m_instance != nullptr);
        return m_instance;
    }

    Config::Config(const std::string path, const bool checkForBenchmarkOption)
        : m_ResourcePath(utils::extractResourcePath(path.c_str()))
        , m_CheckForBenchmarkOption(checkForBenchmarkOption)
        , m_isFullscreen(true)
    {

    }

    std::string Config::getResourcePath()
    {
        return m_ResourcePath;
    }

    bool Config::getCheckForBenchmarkOption()
    {
        return m_CheckForBenchmarkOption;
    }

}

