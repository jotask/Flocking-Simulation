#pragma once

#include "engine/systems/entity/entity.hpp"

namespace flocking
{

    class Flock : public aiko::Entity
    {
    public:

        Flock();
        virtual ~Flock() = default;

        virtual void init();
        virtual void update(const aiko::TimeStep & step);

        virtual void    updateTransform();

        void randomise();

    };

}