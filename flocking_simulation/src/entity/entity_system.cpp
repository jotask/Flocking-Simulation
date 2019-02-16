#include "entity_system.hpp"

namespace aiko
{

    EntitySystem::EntitySystem()
        : SingletonCtr()
    {
        SingletonCtr::setPtr(this);
    }

    void EntitySystem::update(const TimeStep & step)
    {
        for (auto& e : m_entities)
        {
            e->update(step);
            e->updateTransform();
        }
    }

    void EntitySystem::render()
    {
        for (auto& e : m_entities)
        {
            e->render();
        }
    }

}
