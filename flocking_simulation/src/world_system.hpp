#pragma once

#include "transform.hpp"
#include "system.hpp"
#include "light.hpp"
#include "types.hpp"

#include "Horde3D.h"

#include <vector>

namespace aiko
{

    class AssetsSystem;

    class WorldSystem : public System
    {
    public:

        WorldSystem();

        virtual ~WorldSystem() = default;

        void                connect(SystemConnector& systemConnectar, ModuleConnector& moduleConnector) override;
        void                init() override;
        bool                initResources() override;

        virtual void        update(const TimeStep& step) override;

        void                registerLight(Light light);

    private:

        using Resources     = std::vector<H3DRes>;
        Resources           m_resources;

        using Lights        = std::vector<Light>;
        Lights              m_lights;

        AssetsSystem* m_assetSystem;

    };

}

