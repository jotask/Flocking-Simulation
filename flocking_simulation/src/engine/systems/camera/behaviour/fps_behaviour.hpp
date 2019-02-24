#pragma once

#include "engine/systems/camera/behaviour/behaviour.hpp"

namespace aiko
{

    class FpsBehaviour : public Behaviour
    {
    public:
        FpsBehaviour(Camera& camera);
        virtual ~FpsBehaviour();

        virtual void createCamera(H3DNode& camNode);
        virtual void update(const TimeStep & step);

    private:

        float               m_velocity; // Velocity for movement. Temporally until better system

    };

}
