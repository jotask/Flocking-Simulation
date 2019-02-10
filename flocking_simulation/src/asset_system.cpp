#include "asset_system.hpp"

#include <memory>

namespace aiko
{

    AssetsSystem * AssetsSystem::s_instance = nullptr;

    AssetsSystem::AssetsSystem()
    {
        s_instance = this;
    }

    void AssetsSystem::connect(SystemConnector & systemConnectar, ModuleConnector & moduleConnector)
    {
    }

    void AssetsSystem::init()
    {
    }

    bool AssetsSystem::initResources()
    {
        return false;
    }

    void AssetsSystem::update(const TimeStep & step)
    {
    }

    Asset::AssetId AssetsSystem::loadResource(const char * path, const Asset::Types type)
    {

        auto asset = std::make_unique<Asset>(path, type);
        asset->load();

        const auto key = asset->getId();
        m_assets.insert(std::make_pair(key, std::move(asset)));

        return key;
    }

}

