#pragma once

#include "component.hpp"

#include "Horde3D.h"

namespace aiko
{

    class Entity;

    class Mesh : public Component
    {
    public:
        Mesh(Entity& owner);

        virtual void updateHordes() override;
        virtual void init() override;

    private:

        H3DNode m_mesh;

    };

}