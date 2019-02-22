#pragma once

// stl
#include <string>

namespace aiko
{

    namespace utils
    {

        // Extracts an absolute path to the resources directory given the executable path.
        // It assumes that the ressources can be found in "[app path]/../../Content".
        // This function implements the platform specific differences.
        std::string extractResourcePath(const char *fullPath);

        // Look for -bm (benchmark) option.
        bool checkForBenchmarkOption(int argc, char** argv);

    }

}
