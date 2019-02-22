#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <functional>

#include "config.hpp"
#include "module.hpp"

namespace aiko
{

    class Renderer;

    class Display : public Module
    {
    public:
        Display(Engine& engine);

        void            connect(ModuleConnector& moduleConnector) override;
        bool            init();

        void            release();

        GLFWwindow*     getWindowHandle() const;
        const char*     getTitle() const;
        void            getSize(int &width, int &height) const;
        void            setTitle(const char* title);
        void            setWindowCurost(const bool hasCursor);
        void            toggleFullScreen();
        void            showCursor(bool visible);
        void            swapBuffer();

        // GLFW listeners.
        static void     windowCloseListener(GLFWwindow* win);
        static void     windowResizeListener(GLFWwindow* win, int width, int height);
        static void     keyPressListener(GLFWwindow* win, int key, int scancode, int action, int mods);
        static void     mouseMoveListener(GLFWwindow* win, double x, double y);
        static void     mouseEnterListener(GLFWwindow* win, int entered);

        void            simulateResizeEvent();

        // System
        Renderer*       m_renderer;

        GLFWwindow*     m_winHandle;
        std::string     m_winTitle;
        int             m_initWinWidth;
        int             m_initWinHeight;

        int             m_winSampleCount;
        int             m_sampleCount;
        bool            m_winFullScreen;
        float           m_prevMx, m_prevMy;
        bool            m_winShowCursor;
        bool            m_winHasCursor;



    };

}

