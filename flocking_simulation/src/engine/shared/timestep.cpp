#include "timestep.hpp"

#include <GLFW/glfw3.h>

namespace aiko
{
    TimeStep::TimeStep()
        : m_delta    (0.0f)
        , m_curFPS(H3D_FPS_REFERENCE)
        , m_startTime(0.0)
    {

    }

    float TimeStep::getStartTime() const
    {
        return static_cast<float>(m_startTime);
    }

    float TimeStep::getFPS() const
    {
        return m_curFPS;
    }

    float TimeStep::getDelta() const
    {
        return m_delta;
    }

    void TimeStep::init()
    {
        m_startTime = glfwGetTime();
    }

    void TimeStep::update()
    {

        ++m_frames;
        if (m_frames >= 3)
        {
            const double t = glfwGetTime();
            m_fps = m_frames / static_cast<float>(t - m_startTime);

            // Handle breakpoints
            if (m_fps < 5)
            {
                m_fps = H3D_FPS_REFERENCE;
            }

            m_frames = 0;
            m_startTime = t;
        }

        // TODO
        // Organise this in a better way.

        m_curFPS = m_fps;

        m_delta = m_curFPS * H3D_FPS_REFERENCE;

        const auto frameTime = m_delta = 1.0f / getFPS();


    }

}

