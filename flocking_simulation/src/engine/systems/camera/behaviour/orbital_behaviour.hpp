#pragma once

#include "engine/systems/camera/behaviour/behaviour.hpp"

namespace aiko
{

    class OrbitalBehaviour : public Behaviour
    {
    public:

        OrbitalBehaviour(Camera& camera);
        virtual ~OrbitalBehaviour();

        virtual void createCamera(H3DNode& camNode);
        virtual void update(const TimeStep & step);

    private:

        H3DNode             m_anchor;

    };

}
