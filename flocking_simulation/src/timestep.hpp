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

        void        init();
        void        update();

        int         m_frames = 0;
        float       m_fps   = H3D_FPS_REFERENCE;

        float        m_delta;
        float        m_curFPS;
        double       m_startTime;

    };

}
