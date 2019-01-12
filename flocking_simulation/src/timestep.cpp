#include "timestep.hpp"

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

}

