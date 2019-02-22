#pragma once

#include "engine/engine.hpp"

namespace aiko
{

    class SystemConnector
    {
    public:

        SystemConnector(Engine::Systems& systems)
            : m_systems(systems)
        {
        
        }

        template <class T>
        T* findSystem()
        {
            for (auto& m: m_systems)
            {
                if (T* tmp = dynamic_cast<T*>(m.get())) {
                    return tmp;
                }
            }
            return nullptr;
        }

    private:

        Engine::Systems& m_systems;

    };

}
