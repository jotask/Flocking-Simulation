#pragma once

namespace aiko
{

#define H3D_FPS_REFERENCE 60.0f

    class TimeStep
    {
    public:
        TimeStep();
        ~TimeStep() = default;

        float       getStartTime() const;
        float       getFPS() const;
        float       getDelta() const;

    private:

        // Let the Engine class have full access to this class
        friend class Engine;

        float        m_delta;
        float        m_curFPS;
        double       m_startTime;

    };

}
