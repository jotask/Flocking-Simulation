#pragma once

#include "types.hpp"
#include "engine.hpp"

namespace aiko
{

    class Application
    {
    public:

        Application(aiko::Config& cfg);
        virtual ~Application() = default;

        virtual void        init() = 0;

        virtual void        run();

    protected:

        Engine*             getEngine();

    private:

        using EnginePtr     = AikoUPtr<Engine>;
        EnginePtr           m_engine;

    };

}
