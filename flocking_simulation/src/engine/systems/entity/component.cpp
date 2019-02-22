#include "component.hpp"

#include "engine/systems/entity/entity.hpp"

namespace aiko
{

    Component::Component(Entity& owner)
        : m_owner(owner)
    {

    }

    void Component::init()
    {

    }

    void Component::update(const TimeStep& step)
    {

    }

    void Component::render()
    {

    }

}
