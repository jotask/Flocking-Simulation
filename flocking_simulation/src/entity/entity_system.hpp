#pragma once

#include "../system.hpp"
#include "../types.hpp"

#include "entity.hpp"
#include "../singleton.hpp"

#include <vector>
#include <memory>

namespace aiko
{

    // TODO really basic system
    // This system needs a refactoring and a proper desing.

    class EntitySystem : public System, public SingletonCtr<EntitySystem>
    {
    private:
        using EntityPtr = std::unique_ptr<Entity>;
        using Entities = std::vector<EntityPtr>;
    public:

        EntitySystem();

        virtual ~EntitySystem() = default;

        virtual void        update(const TimeStep& step) override;
        virtual void        render() override;

    private:
        Entities            m_entities;

    public:

        template<class T, class... Args >
        static T* createEntity(Args &&...args)
        {
            static_assert(std::is_base_of<Entity, T>::value, "T is not base class off Entity");
            auto* entitySystem = EntitySystem::it();
            auto it = std::make_unique<T>(std::forward<Args>(args)...);
            entitySystem->m_entities.push_back(std::move(it));
            auto& tmp = EntitySystem::it()->m_entities.back();
            auto* ptr = tmp.get();
            auto* result = dynamic_cast<T*>(ptr);
            return result;
        }
    };

}

