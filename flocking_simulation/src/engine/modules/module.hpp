#pragma once

namespace aiko
{

    class Engine;
    class ModuleConnector;

    class Module
    {
    public:
        Module(Engine& engine)
            : m_engine(engine)
        {

        }

        virtual ~Module() = default;

        virtual bool init() = 0;

        virtual void connect(ModuleConnector& moduleConnector) {  };
        virtual bool initResources() { return true; };

    protected:

        Engine& m_engine;

    };

}
