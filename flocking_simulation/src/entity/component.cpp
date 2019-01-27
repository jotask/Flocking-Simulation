#include "component.hpp"

#include "entity.hpp"

namespace aiko
{

    Component::Component(Entity& owner)
        : m_owner(owner)
    {

    }

    void Component::update(const TimeStep& step)
    {

    }

    void Component::render()
    {

    }

}
