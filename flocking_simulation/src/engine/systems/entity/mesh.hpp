#pragma once

#include "engine/systems/entity/component.hpp"

#include "Horde3D.h"

namespace aiko
{

    class Entity;

    class Mesh : public Component
    {
    public:
        Mesh(Entity& owner);

        virtual void updateTransform() override;
        virtual void init() override;

        H3DNode getId();

    protected:

        H3DNode m_mesh;

    };

}