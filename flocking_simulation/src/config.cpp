#include "config.hpp"

#include <cassert>

namespace aiko
{

    Config::GlobalConfig Config::m_instance = nullptr;

    void Config::initGlobalConfig(int argc, char** argv)
    {
        // Check if benchmark mode is requested
        const auto benchmark = (argc > 1 && strcmp(argv[1], "-bm") == 0);

        assert(m_instance == nullptr);
        auto resourcePath = std::string(argv[0]);

        m_instance = std::make_shared<Config>(resourcePath, benchmark);

    }

    Config::GlobalConfig Config::it()
    {
        assert(m_instance != nullptr);
        return m_instance;
    }

    Config::Config(const std::string resourcePath, const bool checkForBenchmarkOption)
        : m_ResourcePath(resourcePath)
        , m_CheckForBenchmarkOption(checkForBenchmarkOption)
    {

    }

    std::string Config::getResourcePath() const
    {
        return m_ResourcePath;
    }

    bool Config::getCheckForBenchmarkOption() const
    {
        return m_CheckForBenchmarkOption;
    }

}

