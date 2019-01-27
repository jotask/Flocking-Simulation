#include "entity.hpp"

namespace aiko
{

    void Entity::update(const TimeStep & step)
    {
        for (auto& c : m_components)
        {
            c->update(step);
        }
    }

    void Entity::render()
    {
        for (auto& c : m_components)
        {
            c->render();
        }
    }

}