#pragma once

#include "module.hpp"

namespace aiko
{

    class Log : public Module
    {
    public:

        Log             (Engine& engine);
        virtual         ~Log() = default;

        void            connect(ModuleConnector& moduleConnector) override;
        bool            init();

    private:

    };

}

