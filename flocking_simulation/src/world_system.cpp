#include "world_system.hpp"

#include "module_connector.hpp"
#include "system_connector.hpp"

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
        H3DRes envRes = h3dAddResource(H3DResTypes::SceneGraph, "models/sphere/sphere.scene.xml", 0);

        // Shader for deferred shading
        H3DRes lightMatRes = h3dAddResource(H3DResTypes::Material, "materials/light.material.xml", 0);

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

