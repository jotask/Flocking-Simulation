#pragma once

#include "../system.hpp"
#include "../types.hpp"

#include "entity.hpp"

#include <vector>

namespace aiko
{

    // TODO really basic system
   // This system needs a refactoring and a proper desing.
    // Looking to implement a ECS

    class EntitySystem : public System
    {
    public:

        EntitySystem();

        virtual ~EntitySystem() = default;

        virtual void        update(const TimeStep& step) override;
        virtual void        render() override;
        
        template <class T>
        T* registerEntity();

    private:

        using Entities      = std::vector<Entity>;
        Entities            m_entities;

    };

    template<class T>
    inline T* EntitySystem::registerEntity()
    {
        auto& it = std::make_unique<T>(this);
        m_entities.emplace_back(std::move(it));
        return m_entities.back();
    }

}

