#pragma once

#include "engine/shared/timestep.hpp"
#include "engine/systems/camera/behaviour/behaviour_types.hpp"

#include <Horde3D.h>

namespace aiko
{
    class Camera;
    class Behaviour
    {
    public:
        Behaviour(Camera&, BehaviourType);
        virtual ~Behaviour() = default;

        virtual void createCamera(H3DNode& camNode) = 0;
        virtual void update(const TimeStep & step) = 0;

        const BehaviourType getType() const;

    protected:

        const BehaviourType m_type;

        Camera & m_camera;

    };

}
