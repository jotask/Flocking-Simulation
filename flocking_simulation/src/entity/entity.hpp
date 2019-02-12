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

        Entity() = default;
        ~Entity() = default;

        void update(const TimeStep & step);
        void render();

        Transform m_transform;
        using Components = std::vector<std::shared_ptr<Component>>;
        Components m_components;
    };

}