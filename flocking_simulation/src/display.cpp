#include "display.hpp"

#include "engine.hpp"
#include "config.hpp"
#include "renderer.hpp"
#include "module_connector.hpp"

#include "Horde3D.h"
#include "Horde3DUtils.h"

#include <string>
#include <iostream>

namespace aiko
{

    Display::Display(Engine& eng)
        : Module(eng)
        , m_renderer(nullptr)
        , m_winHandle(0)
        , m_winTitle(eng.getConfig().getWindowTitle())
        , m_initWinWidth(eng.getConfig().getWindowWidth())
        , m_initWinHeight(eng.getConfig().getWindowHeight())
        , m_winSampleCount(0)
        , m_sampleCount(0)
        , m_winFullScreen(false)
        , m_prevMx(0)
        , m_prevMy(0)
        , m_winShowCursor(true)
        , m_winHasCursor(false)
    {

    }

    void Display::connect(ModuleConnector& moduleConnector)
    {
        m_renderer = moduleConnector.findModule<Renderer>();
    }

    bool Display::init()
    {

        // Create OpenGL window
        glfwWindowHint(GLFW_RED_BITS, 8);
        glfwWindowHint(GLFW_GREEN_BITS, 8);
        glfwWindowHint(GLFW_BLUE_BITS, 8);
        glfwWindowHint(GLFW_ALPHA_BITS, 8);
        glfwWindowHint(GLFW_DEPTH_BITS, 24);
        glfwWindowHint(GLFW_SAMPLES, m_winSampleCount);
        
        const auto renderInterface = m_renderer->getRenderInterface();
        
        if (renderInterface == H3DRenderDevice::OpenGL4)
        {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        }
        
        if (m_winFullScreen) {
            const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
            m_winHandle = glfwCreateWindow(mode->width, mode->height, m_winTitle.c_str(), glfwGetPrimaryMonitor(), NULL);
        }
        else {
            m_winHandle = glfwCreateWindow(m_initWinWidth, m_initWinHeight, m_winTitle.c_str(), NULL, NULL);
        }
        
        if (m_winHandle == NULL)
        {
            // Fake message box
            glfwDestroyWindow(m_winHandle);
        
            m_winHandle = glfwCreateWindow(800, 50, "Unable to initialize engine - Make sure you have an OpenGL 2.0 compatible graphics card", NULL, NULL);
            double startTime = glfwGetTime();
            while (glfwGetTime() - startTime < 5.0) { /* Sleep */ }
        
            const auto renderInterface = aiko::Config::it()->getRenderInterface();
        
            std::cout << "Unable to initialize window" << std::endl;
            std::cout << "Make sure you have an OpenGL " << ((renderInterface == H3DRenderDevice::OpenGL2) ? "2.0" : "4.3") << " compatible graphics card" << std::endl;
        
            return false;
        }
        
        glfwSetWindowUserPointer(m_winHandle, &m_engine);
        glfwMakeContextCurrent(m_winHandle);
        glfwSetInputMode(m_winHandle, GLFW_STICKY_KEYS, GL_TRUE);
        
        
        // Init cursor
        showCursor(m_winShowCursor);

        // Disable vertical synchronization
        glfwSwapInterval(0);

        return true;
    }

    GLFWwindow* Display::getWindowHandle() const
    {
        return m_winHandle;
    }

    const char* Display::getTitle() const
    {
        return m_winTitle.c_str();
    }

    void Display::getSize(int &width, int &height) const
    {
        if (m_winHandle) {
            glfwGetWindowSize(m_winHandle, &width, &height);
        }
        else {
            width = -1;
            height = -1;
        }
    }

    void Display::setTitle(const char* title)
    {
        glfwSetWindowTitle(m_winHandle, title);

        m_winTitle = title;
    }

    void Display::setWindowCurost(const bool hasCursor)
    {
        m_winHasCursor = hasCursor;
    }

    void Display::toggleFullScreen()
    {
        if (m_winFullScreen == false)
            getSize(m_initWinWidth, m_initWinHeight);

        // Toggle fullscreen mode
        m_winFullScreen = !m_winFullScreen;

    }

    void Display::showCursor(bool visible)
    {
        glfwSetInputMode(m_winHandle, GLFW_CURSOR, visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);

        m_winShowCursor = visible;
    }


    void Display::swapBuffer()
    {
        // Swap buffers
        glfwSwapBuffers(m_winHandle);
    }

    void Display::release()
    {
        if (m_winHandle)
        {
            // Destroy window
            glfwDestroyWindow(m_winHandle);
            m_winHandle = 0;
        }
    }


}

