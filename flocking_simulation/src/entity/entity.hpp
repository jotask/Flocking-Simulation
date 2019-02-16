#pragma once

#include <vector>

#include "../transform.hpp"
#include "../timestep.hpp"
#include "component.hpp"
#include <memory>

namespace aiko
{

    class Entity
    {
    public:

        Entity();
        virtual ~Entity() = default;

        virtual void update(const TimeStep & step);
        virtual void render();

        Transform m_transform;

        using Components = std::vector<std::shared_ptr<Component>>;
        Components m_components;
    };

}