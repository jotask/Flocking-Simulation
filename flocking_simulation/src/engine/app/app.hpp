#pragma once

#include "engine/shared/types.hpp"
#include "engine/engine.hpp"

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
