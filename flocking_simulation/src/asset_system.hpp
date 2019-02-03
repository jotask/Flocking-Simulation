#pragma once

#include "system.hpp"
#include "types.hpp"

#include "Horde3D.h"

namespace aiko
{

    class AssetsSystem : public System
    {
    public:

        AssetsSystem();

        virtual ~AssetsSystem() = default;

        void    connect(SystemConnector& systemConnectar, ModuleConnector& moduleConnector) override;
        void    init() override;
        bool    initResources() override;

        void    update(const TimeStep& step) override;

    private:

    };

}

