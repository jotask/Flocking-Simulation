#include "app.hpp"

#include <iostream>

namespace aiko
{
    Application::Application(aiko::Config& cfg)
        : m_engine(std::make_unique<Engine>(*this, cfg))
    {

    }

    void Application::run()
    {

        const auto exitStatus = m_engine->run();

        std::cout << exitStatus << std::endl;

    }

    Engine* Application::getEngine()
    {
        return m_engine.get();
    }

}
