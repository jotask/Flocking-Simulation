#include "input_module.hpp"

#include "engine/modules/display_module.hpp"
#include "engine/modules/module_connector.hpp"
#include "engine/event/engine_events.hpp"
#include "engine/event/event_dispatcher.hpp"

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
        EventSystem::it().bind<OnKeyPressedEvent>(this, &Input::onKeyEventHandler);
        EventSystem::it().bind<OnMouseMoveEvent>(this, &Input::onMouseMoveHandler);
        return true;
    }

    bool Input::isKeyDown(int key) const
    {
        return glfwGetKey(m_display->getWindowHandle(), key) == GLFW_PRESS;
    }

    void Input::onKeyEventHandler(Event& event)
    {
        const auto& msg = static_cast<const OnKeyPressedEvent&>(event);

        if (msg.action != GLFW_PRESS)
            return;

        switch (msg.key)
        {
        case GLFW_KEY_ESCAPE:
        {
            WindowCloseEvent event;
            EventSystem::it().sendEvent(event);
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

    void Input::onMouseMoveHandler(Event& event)
    {
        const auto& msg = static_cast<const OnMouseMoveEvent&>(event);
        const auto dx = msg.x - msg.prevX;
        const auto dy = msg.prevY - msg.y;
    }

}

