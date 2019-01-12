#pragma once

#include "types.hpp"

#include "Horde3D.h"
#include <string>

namespace aiko
{

    class Config
    {
    public:

        using GlobalConfig = aiko::AikoPtr<Config>;

        static void initGlobalConfig(int argc, char** argv);
        static GlobalConfig it();

        Config(const std::string path, const bool checkForBenchmarkOption);
        ~Config() = default;

        std::string getResourcePath();
        std::string getWindowTitle() { return "Aiko"; };

        int getWindowWidth() { return 1024; };
        int getWindowHeight() { return 576; };

        bool getCheckForBenchmarkOption();
        bool isFullScreen() { return false; };
        bool showCursorInScreen() { return false; };

        H3DRenderDevice::List   getRenderInterface() { return H3DRenderDevice::OpenGL4; };

    private:

        static GlobalConfig m_instance;

        int m_argc;
        char ** m_argv;

        const std::string m_ResourcePath;
        const bool m_CheckForBenchmarkOption;

    };

}

