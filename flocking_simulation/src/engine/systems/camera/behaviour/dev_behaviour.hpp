#pragma once

#include "engine/systems/camera/behaviour/behaviour.hpp"

namespace aiko
{

    class DevBehaviour : public Behaviour
    {
    public:
        DevBehaviour(Camera& camera);
        virtual ~DevBehaviour() = default;

        virtual void createCamera(H3DNode& camNode);
        virtual void update(const TimeStep & step);

    private:

    };

}
