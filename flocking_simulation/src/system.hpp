#pragma once

#include "timestep.hpp"

namespace aiko
{

    class Engine;
    class ModuleConnector;
    class SystemConnector;

    class System
    {
    public:
        System() = default;
        virtual ~System() = default;

        virtual void        connect(SystemConnector& systemConnectar, ModuleConnector& moduleConnector) {  };

        virtual bool        initResources() { return true; };

        virtual void        preInit() {  };
        virtual void        init() {  };
        virtual void        postInit() {  };

        virtual void        preUpdate(const TimeStep& step) {  };
        virtual void        update(const TimeStep& step) {  };
        virtual void        postUpdate(const TimeStep& step) {  };

        virtual void        preRender() {  };
        virtual void        render() {  };
        virtual void        postRender() {  };

    };

}
