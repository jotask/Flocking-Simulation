#include "world_system.hpp"

#include "module_connector.hpp"
#include "system_connector.hpp"

#include "asset_system.hpp"

namespace aiko
{

    WorldSystem::WorldSystem()
        :   System()
        , m_resources()
        , m_lights()
    {

    }

    void WorldSystem::connect(SystemConnector& systemConnectar, ModuleConnector& moduleConnector)
    {
        m_assetSystem = systemConnectar.findSystem<AssetsSystem>();
    }

    void WorldSystem::init()
    {

        // TODO Improve

        // Add environment
        H3DNode env = h3dAddNodes(H3DRootNode, m_resources[0]);
        h3dSetNodeTransform(env, 0, -20, 0, 0, 0, 0, 20, 20, 20);

        // Add light source
        Light light;
        this->registerLight(light);

    }

    bool WorldSystem::initResources()
    {

        // TODO Improve

        // Environment
        const auto envRes = m_assetSystem->loadResource("models/sphere/sphere.scene.xml", H3DResTypes::SceneGraph);

        // Shader for deferred shading
        const auto lightMatRes = m_assetSystem->loadResource("materials/light.material.xml", H3DResTypes::Material);

        m_resources.push_back(envRes);
        m_resources.push_back(lightMatRes);

        return true;

    }

    void WorldSystem::update(const TimeStep & step)
    {

    }

    void WorldSystem::registerLight(Light light)
    {
        light.createLight(m_resources[1]);
        m_lights.push_back(light);
    }

}

