#include "engine/engine_helper.hpp"

namespace aiko
{

    namespace utils
    {

        std::string extractResourcePath(const char* fullPath)
        {
            std::string s(fullPath);

            static constexpr const char delim = '\\';
            static constexpr const unsigned int nbRfind = 1;

            // Remove the token of path until the executable parent folder is reached
            for (auto i = 0u; i < nbRfind; i++)
            {
                s = s.substr(0, s.rfind(delim));
            }

            // Add the 'Content' folder
            return s + delim + ".." + delim + ".." + delim + "Content";

        }

        bool checkForBenchmarkOption(int argc, char** argv)
        {
            // Check if benchmark mode is requested
            return (argc > 1 && strcmp(argv[1], "-bm") == 0);
        }

    }

}
