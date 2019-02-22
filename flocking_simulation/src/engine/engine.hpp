#pragma once

#include "Horde3D.h"
#include <GLFW/glfw3.h>

#include "Horde3D.h"
#include <string>
#include <vector>

#include "engine/config/config.hpp"
#include "engine/modules/module.hpp"
#include "engine/systems/system.hpp"
#include "engine/shared/timestep.hpp"

#include "event/engine_events.hpp"

namespace aiko
{

    class ModuleConnector;
    class Display;
    class Renderer;
    class CameraSystem;
    class Input;
    class Application;

    class Engine
    {
    public:
        using Modules   = std::vector<std::shared_ptr<Module>>;
        using Systems   = std::vector<std::shared_ptr<System>>;

        Engine          (Application& app, Config cfg);
        virtual         ~Engine();

        int             run();
        void            requestClosing();

        Config &        getConfig();
        const char*     getResourcePath() const;

    protected:
        virtual void    update(const TimeStep& step);
        virtual void    render();
        virtual void    finalize();

    private:

        // Make this class friend for now
        // This is because we are receving event in stat methogs
        friend class Display;

        Engine()        = delete;

        bool            init();
        bool            initModules();
        bool            initSystems();
        void            releaseResources();
        void            connectModules(ModuleConnector& moduleConnector);
        void            connectSystems(SystemConnector& systemConnector);
        void            release();

        template <class T>
        bool            initResources(T& collection);

        // Events
        void            onWindowClose(Event& ent);
        
        Application&    m_app;
        Config          m_config;

        Modules         m_modules;
        Systems         m_systems;

        bool            m_initialized;
        bool            m_running;
        std::string     m_resourcePath;

        // systems
        Display*        m_display;
        Renderer*       m_renderer;
        CameraSystem*   m_camera;
        Input*          m_input;

    };

}

