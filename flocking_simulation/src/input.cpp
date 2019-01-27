#include "input.hpp"

#include "display.hpp"
#include "module_connector.hpp"

#include  "glm.hpp"

namespace aiko
{

    Input::Input(Engine& engine)
        : Module(engine)
        , m_display(nullptr)
    {

    }

    void Input::connect(ModuleConnector & moduleConnector)
    {
        m_display = moduleConnector.findModule<Display>();
    }

    bool Input::init()
    {
        return true;
    }

    bool Input::isKeyDown(int key) const
    {
        return glfwGetKey(m_display->getWindowHandle(), key) == GLFW_PRESS;
    }

    void Input::keyEventHandler(int key, int scancode, int action, int mods)
    {
        if (action != GLFW_PRESS)
            return;

        switch (key)
        {
        case GLFW_KEY_ESCAPE:
        {
            m_engine.requestClosing();
        }
        break;
        
        case GLFW_KEY_F11:
        {
            // TODO Disabled
            // m_display->toggleFullScreen();
            // m_engine.m_initialized = false;
        }
        break;
        }
    }

    void Input::mouseMoveHandler(float x, float y, float prev_x, float prev_y)
    {
        const auto dx = x - prev_x;
        const auto dy = prev_y - y;
    }

}

