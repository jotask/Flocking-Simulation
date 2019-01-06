#include "config.hpp"

#include <cassert>

#include <iostream>

namespace aiko
{

    Config::GlobalConfig Config::m_instance = nullptr;

    std::string extractResourcePath(const std::string path)
    {

        std::string s(path.c_str());

#ifdef WIN32
        const char delim = '\\';
#else
        const char delim = '/';
#endif

#ifdef __APPLE__
        // On MacOSX the application is in a 'bundle' and the path has the form:
        //     "Engine.app/Contents/MacOS/Engine"
        const unsigned int nbRfind = 4;
#else
        const unsigned int nbRfind = 1;
#endif

        // Remove the token of path until the executable parent folder is reached
        for (unsigned int i = 0; i < nbRfind; ++i)
            s = s.substr(0, s.rfind(delim));

        // Add the 'Content' folder
        return s + delim + ".." + delim + ".." + delim + "Content";

    }

    void Config::initGlobalConfig(int argc, char** argv)
    {
        // Check if benchmark mode is requested
        const auto benchmark = (argc > 1 && strcmp(argv[1], "-bm") == 0);

        assert(m_instance == nullptr);

        char *fullPath = argv[0];
        auto resourcePath = std::string(argv[0]);

        m_instance = std::make_shared<Config>(resourcePath, benchmark);

    }

    Config::GlobalConfig Config::it()
    {
        assert(m_instance != nullptr);
        return m_instance;
    }

    Config::Config(const std::string path, const bool checkForBenchmarkOption)
        : m_ResourcePath(extractResourcePath(path))
        , m_CheckForBenchmarkOption(checkForBenchmarkOption)
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

