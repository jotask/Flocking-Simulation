#pragma once

#include "../timestep.hpp"

namespace aiko
{

    class Entity;

    class Component
    {
    public:
        Component(Entity& owner);

        void update(const TimeStep& step);
        void render();

    protected:
        Entity& m_owner;
    };

}