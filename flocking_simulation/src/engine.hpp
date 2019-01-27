#pragma once

#include "Horde3D.h"
#include <GLFW/glfw3.h>

#include "Horde3D.h"
#include <string>
#include <vector>

#include "config.hpp"
#include "module.hpp"
#include "system.hpp"
#include "timestep.hpp" // Added in header to avoid include this file in any inheritance.

#include "event/engine_events.hpp"

namespace aiko
{

    class ModuleConnector;
    class Display;
    class Renderer;
    class Camera;
    class Input;

    class Engine
    {
    public:
        using Modules   = std::vector<std::shared_ptr<Module>>;
        using Systems   = std::vector<std::shared_ptr<System>>;

        Engine          (Config cfg);
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

        Config          m_config;

        Modules         m_modules;
        Systems         m_systems;

        bool            m_initialized;
        bool            m_running;
        std::string     m_resourcePath;

        // systems
        Display*        m_display;
        Renderer*       m_renderer;
        Camera*         m_camera;
        Input*          m_input;

    };

}

