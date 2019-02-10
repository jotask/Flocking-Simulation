#pragma once

#include "system.hpp"
#include "types.hpp"
#include "asset.hpp"

#include "Horde3D.h"

#include <map>

namespace aiko
{

    class AssetsSystem : public System
    {
    private:

        static AssetsSystem * s_instance;

    public:

        static AssetsSystem* it() { return s_instance; }

        AssetsSystem();

        virtual ~AssetsSystem() = default;

        void            connect(SystemConnector& systemConnectar, ModuleConnector& moduleConnector) override;
        void            init() override;
        bool            initResources() override;

        void            update(const TimeStep& step) override;

        Asset::AssetId  loadResource(const char* path, const Asset::Types type);

    private:

        using Assets    = std::map<Asset::AssetId,AikoUPtr<Asset>>;

        Assets          m_assets;

    };

}

