#include "entity_system.hpp"

namespace aiko
{

    EntitySystem::EntitySystem()
    {

    }

    void EntitySystem::update(const TimeStep & step)
    {
        for (auto& e : m_entities)
        {
            e.update(step);
        }
    }

    void EntitySystem::render()
    {
        for (auto& e : m_entities)
        {
            e.render();
        }
    }

}
