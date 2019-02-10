#pragma once

#include "../timestep.hpp"

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

    protected:
        Entity& m_owner;
    };

}