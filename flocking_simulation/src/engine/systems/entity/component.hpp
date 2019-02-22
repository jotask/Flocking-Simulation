#pragma once

#include "engine/shared/timestep.hpp"

#include "Horde3D.h"

#include <vector>

namespace aiko
{

    class Entity;

    class Component
    {
    public:
        Component(Entity& owner);

        virtual ~Component() = default;

        virtual void init();
        virtual void update(const TimeStep& step);
        virtual void render();

        virtual void updateTransform() {};

    protected:


        Entity& m_owner;

        using Hordes    = std::vector<H3DNode>;
        Hordes          m_ordes;

    };

}