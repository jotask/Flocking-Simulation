#include "log.hpp"

#include "module_connector.hpp"

namespace aiko
{

    Log::Log(Engine& engine)
        : Module(engine)
    {

    }


    void Log::connect(ModuleConnector& moduleConnector)
    {

    }

    bool Log::init()
    {
        return true;
    }

}

