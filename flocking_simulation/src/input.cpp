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
        // Set listeners
        glfwSetWindowCloseCallback(m_display->getWindowHandle(), windowCloseListener);
        glfwSetWindowSizeCallback(m_display->getWindowHandle(), windowResizeListener);
        glfwSetKeyCallback(m_display->getWindowHandle(), keyPressListener);
        glfwSetCursorPosCallback(m_display->getWindowHandle(), mouseMoveListener);
        glfwSetCursorEnterCallback(m_display->getWindowHandle(), mouseEnterListener);
        return true;
    }

    bool Input::isKeyDown(int key) const
    {
        return glfwGetKey(m_display->getWindowHandle(), key) == GLFW_PRESS;
    }

    void Input::windowCloseListener(GLFWwindow* win)
    {
        if (Engine* const app = static_cast<Engine*>(glfwGetWindowUserPointer(win)))
        {
            app->requestClosing();
        }
    }

    void Input::windowResizeListener(GLFWwindow* win, int width, int height)
    {
        if (Engine* const app = static_cast<Engine*>(glfwGetWindowUserPointer(win)))
        {
            app->resizeViewport();
        }
    }

    void Input::keyPressListener(GLFWwindow* win, int key, int scancode, int action, int mods)
    {
        if (Engine* const app = static_cast<Engine*>(glfwGetWindowUserPointer(win)))
        {
            if (auto* input = app->m_input)
            {
                input->keyEventHandler(key, scancode, action, mods);
            }
        }
    }

    void Input::mouseMoveListener(GLFWwindow* win, double x, double y)
    {
        static auto prev = glm::vec2(x, y);
        if (Engine* const app = static_cast<Engine*>(glfwGetWindowUserPointer(win)))
        {
            if (auto* input = app->m_input)
            {
                input->mouseMoveHandler(static_cast<float>(x), static_cast<float>(y), prev.x, prev.y);
            }
            prev = { x, y };
        }
    }

    void Input::mouseEnterListener(GLFWwindow* win, int entered)
    {
        if (Engine* const app = static_cast<Engine*>(glfwGetWindowUserPointer(win)))
        {
            if (auto* display = app->m_display)
            {
                display->setWindowCurost(entered != 0);
            }
        }
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

