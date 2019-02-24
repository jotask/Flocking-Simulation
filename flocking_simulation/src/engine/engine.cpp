#include "engine.hpp"

// aiko
#include "engine/engine_helper.hpp"
#include "engine/config/config.hpp"
#include "engine/modules/display_module.hpp"
#include "engine/modules/renderer_module.hpp"
#include "engine/systems/camera/camera_system.hpp"
#include "engine/modules/log_module.hpp"
#include "engine/modules/input_module.hpp"
#include "engine/systems/world_system.hpp"
#include "engine/systems/particles/particle_system.hpp"
#include "engine/modules/module_connector.hpp"
#include "engine/systems/system_connector.hpp"
#include "engine/event/event_dispatcher.hpp"
#include "engine/systems/entity/entity_system.hpp"
#include "engine/systems/assets/asset_system.hpp"
#include "engine/app/app.hpp"

// Horde
#include "Horde3DUtils.h"

// stl
#include <iostream>

namespace aiko
{

    Engine::Engine(Application& app, Config cfg)
        : m_app(app)
        , m_initialized(false)
        , m_running(false)
        , m_resourcePath(cfg.getResourcePath())
        , m_config(cfg)
        , m_display(nullptr)
        , m_renderer(nullptr)
        , m_camera(nullptr)
    {
        // Initialize GLFW
        glfwInit();
    }

    Engine::~Engine()
    {
        release();

        // Terminate GLFW
        glfwTerminate();
    }

    int Engine::run()
    {

        m_running = true;

        TimeStep timestep;

        // Game loop
        while (m_running == true)
        {
            if (m_initialized == false)
            {
                if (init() == false)
                {
                    glfwTerminate();
                    return -1;
                }
                m_initialized = true;
                timestep.init();
            }

            // Calc FPS
            timestep.update();

            // Poll window events...
            glfwPollEvents();

            // update logic
            update(timestep);

            // render and finalize frame.
            render();
            finalize();

        }

        release();

        return 0;
    }

    void Engine::requestClosing()
    {
        m_running = false;
    }

    const char* Engine::getResourcePath() const
    {
        return m_resourcePath.c_str();
    }

    template <class T>
    bool Engine::initResources(T& collection)
    {
        // 1. Add resources
        for (auto& c : collection)
        {
            // TODO error checking
            c->initResources();
        }

        // 2. Load resources
        if (h3dutLoadResourcesFromDisk(m_resourcePath.c_str()) == false)
        {
            std::cout << "Error in loading resources" << std::endl;
            h3dutDumpMessages();
            return false;
        }

        return true;
    }

    void Engine::releaseResources()
    {

    }

    void Engine::update(const TimeStep& step)
    {
        for (auto& sys : m_systems)
        {
            sys->preUpdate(step);
            sys->update(step);
            sys->postUpdate(step);
        }
    }

    void Engine::render()
    {
        // m_renderer->setCamera(m_camera);
        // m_render->begin();
        // blah blah blah
        // m_render.end();

        for (auto& sys : m_systems)
        {
            sys->preRender();
            sys->render();
            sys->postRender();
        }

        // Render scene
        const auto& cam = m_camera->getCamera();
        h3dRender(cam.getCameraId());
    }

    void Engine::finalize()
    {
        // Finish rendering of frame
        h3dFinalizeFrame();

        // Remove all overlays
        h3dClearOverlays();

        // Write all messages to log file
        h3dutDumpMessages();

        // Swap buffers
        m_display->swapBuffer();
    }

    bool Engine::initModules()
    {

        // Register modules
        m_modules.push_back(std::make_shared<Log>(*this));
        m_modules.push_back(std::make_shared<Display>(*this));
        m_modules.push_back(std::make_shared<Renderer>(*this));
        m_modules.push_back(std::make_shared<Input>(*this));

        // call all modules to connect to the other modules required
        ModuleConnector connector(m_modules);

        // connect first the engine
        this->connectModules(connector);

        for (auto& module : m_modules)
        {
            // todo error checking
            module->connect(connector);
        }

        // init all modules
        for (auto& module : m_modules)
        {
            // todo error checking
            if (module->init() == false)
            {
                return false;
            }
        }

        return true;

    }

    bool Engine::initSystems()
    {
        // Register systems
        m_systems.push_back(std::make_shared<EntitySystem>());
        m_systems.push_back(std::make_shared<CameraSystem>());
        m_systems.push_back(std::make_shared<WorldSystem>());
        m_systems.push_back(std::make_shared<AssetsSystem>());
        m_systems.push_back(std::make_shared<ParticleSystem>());

        // call all modules to systems to the other stystems required
        ModuleConnector moduleConnector(m_modules);
        SystemConnector systemConnector(m_systems);

        // connect first the engine
        this->connectSystems(systemConnector);

        for (auto& system : m_systems)
        {
            // todo error checking
            system->connect(systemConnector, moduleConnector);
        }

        // Init systems resources
        if (initResources<Systems>(m_systems) == false)
        {
            std::cout << "Unable to initialize system resources" << std::endl;
            h3dutDumpMessages();
            return false;
        }

        // init all systems
        for (auto& system : m_systems)
        {
            system->preInit();
            system->init();
            system->postInit();
        }


        return true;

    }

    bool Engine::init()
    {

        release();

        // bind to events
        {
            EventSystem::it().bind<WindowCloseEvent>(this, &Engine::onWindowClose);
        }

        initModules();

        // Initialize engine
        const auto renderInterface = m_renderer->getRenderInterface();
        if (h3dInit((H3DRenderDevice::List) renderInterface) == false)
        {
            std::cout << "Unable to initialize engine" << std::endl;
            h3dutDumpMessages();
            return false;
        }

        // Set options
        h3dSetOption(H3DOptions::LoadTextures, 1);
        h3dSetOption(H3DOptions::TexCompression, 0);
        h3dSetOption(H3DOptions::MaxAnisotropy, 4);
        h3dSetOption(H3DOptions::ShadowMapSize, 2048);
        h3dSetOption(H3DOptions::DumpFailedShaders, 1);

        // Init module resources
        if (initResources<Modules>(m_modules) == false)
        {
            std::cout << "Unable to initialize modules resources" << std::endl;
            h3dutDumpMessages();
            return false;
        }

        initSystems();

        // Setup camera and resize buffers
        m_display->simulateResizeEvent();

        h3dutDumpMessages();

        m_app.init();

        return true;
    }

    void Engine::release()
    {
        if (m_display != nullptr && m_display->getWindowHandle() != nullptr)
        {
            // Release loaded resources
            releaseResources();
        
            // Release engine
            h3dRelease();
        
            // Release display
            m_display->release();
        }
    }

    void Engine::onWindowClose(Event & ent)
    {
        requestClosing();
    }

    Config& Engine::getConfig()
    {
        return m_config;
    }

    void Engine::connectModules(ModuleConnector& moduleConnector)
    {
        m_display = moduleConnector.findModule<Display>();
        m_renderer = moduleConnector.findModule<Renderer>();
        m_input = moduleConnector.findModule<Input>();
    }

    void Engine::connectSystems(SystemConnector& systemConnector)
    {
        m_camera = systemConnector.findSystem<CameraSystem>();
    }

}

