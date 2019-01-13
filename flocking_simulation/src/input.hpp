#pragma once

#include "module.hpp"

#include <GLFW/glfw3.h>

namespace aiko
{

    // Forward declaration
    class Display;

    class Input : public Module
    {
    public:

        Input           (Engine& engine);
        virtual         ~Input() = default;

        void            connect(ModuleConnector& moduleConnector) override;
        bool            init();

        bool            isKeyDown(int key) const;

    private:

        // GLFW listeners.
        static void     windowCloseListener(GLFWwindow* win);
        static void     windowResizeListener(GLFWwindow* win, int width, int height);
        static void     keyPressListener(GLFWwindow* win, int key, int scancode, int action, int mods);
        static void     mouseMoveListener(GLFWwindow* win, double x, double y);
        static void     mouseEnterListener(GLFWwindow* win, int entered);

        void            keyEventHandler(int key, int scancode, int action, int mods);
        void            mouseMoveHandler(float x, float y, float prev_x, float prev_y);

        Display*        m_display;

    };

}

