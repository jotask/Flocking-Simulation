#pragma once

#include "engine.hpp"

namespace aiko
{

    class ModuleConnector
    {
    public:

        ModuleConnector(Engine::Modules& modules)
            : m_modules(modules)
        {
        
        }

        template <class T>
        T* findModule()
        {
            for (auto& m: m_modules)
            {
                if (T* tmp = dynamic_cast<T*>(m.get())) {
                    return tmp;
                }
            }
            return nullptr;
        }

    private:

        Engine::Modules& m_modules;

    };

}
