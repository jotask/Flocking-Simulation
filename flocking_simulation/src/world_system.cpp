#include "world_system.hpp"

#include "module_connector.hpp"
#include "system_connector.hpp"

#include "asset_system.hpp"

#include "utils.hpp"

// #define SPEHERE_ON_CENTER_WORLD

namespace aiko
{

    WorldSystem::WorldSystem()
        :   System()
        , m_worldSize()
        , m_resources()
        , m_lights()
    {
        const auto w = 100.0f;

        const auto width = w * 0.5f;
        const auto height = (width * 0.5f) * 0.5f;

        m_worldSize[0] = { -width, -height, -width };
        m_worldSize[1] = {  width,  height,  width };
    }

    void WorldSystem::connect(SystemConnector& systemConnectar, ModuleConnector& moduleConnector)
    {
        m_assetSystem = systemConnectar.findSystem<AssetsSystem>();
    }

    void WorldSystem::spawnRandomPlanets()
    {

        static constexpr const auto numberPlanets = 200;

        for (auto i = 0; i < numberPlanets; i++)
        {
            auto p = getRandomPositionInWorld();
            H3DNode planet = h3dAddNodes(H3DRootNode, m_resources[0]);
            h3dSetNodeTransform(planet, p.x, p.y, p.z, 0, 0, 0, 1, 1, 1);
        }

    }

    void WorldSystem::spawnRandomLights()
    {

        constexpr const auto randomLisghts = 100u;

        for (auto i = 0 ; i < randomLisghts; i++)
        {
            Light light;
            light.getTranform().m_position = getRandomPositionInWorld();
            light.randomise();
            light.updateLight();
            registerLight(light);
        }
    }

    void WorldSystem::init()
    {

        // TODO Improve

#ifdef SPEHERE_ON_CENTER_WORLD

        // Add environment
        H3DNode env = h3dAddNodes(H3DRootNode, m_resources[0]);
        const auto scale = 0.5f;
        h3dSetNodeTransform(env, 0, 0, 0, 0, 0, 0, scale, scale, scale);
#endif

        // spawnRandomPlanets();
        //spawnRandomPlanets();

        // Add light source
        spawnRandomLights();

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

    glm::vec3 WorldSystem::getRandomPositionInWorld()
    {
        return {
            utils::getRandom(m_worldSize[0].x, m_worldSize[1].x),
            utils::getRandom(m_worldSize[0].y, m_worldSize[1].y),
            utils::getRandom(m_worldSize[0].z, m_worldSize[1].z)
        };
    }

}

