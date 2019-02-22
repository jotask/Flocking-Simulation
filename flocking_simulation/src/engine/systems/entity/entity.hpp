#pragma once

#include "engine/shared/transform.hpp"
#include "engine/shared/timestep.hpp"
#include "engine/systems/entity/component.hpp"

#include <memory>
#include <vector>

namespace aiko
{

    class Entity
    {
    public:

        Entity();
        virtual ~Entity() = default;

        virtual void    update(const TimeStep & step);
        virtual void    render();

        virtual void    updateTransform() = 0;

        Transform       m_transform;

        using Components = std::vector<std::shared_ptr<Component>>;
        Components      m_components;

    };

}