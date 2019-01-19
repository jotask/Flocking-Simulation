#pragma once

#include "types.hpp"

namespace aiko
{

    template <class T>
    class Singleton
    {
    public:

        static T& it()
        {
            static auto instance = std::make_unique<T>();
            return *instance;
        }

        Singleton(const Singleton&) = delete;
        Singleton& operator= (const Singleton) = delete;

    protected:
        Singleton() = default;
        virtual ~Singleton() = default;

    };

}

