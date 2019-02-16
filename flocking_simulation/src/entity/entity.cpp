#include "entity.hpp"

namespace aiko
{
    Entity::Entity()
    {

    }

    void Entity::update(const TimeStep & step)
    {
        for (auto& c : m_components)
        {
            c->update(step);
            c->updateHordes();
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