#pragma once

#include <vector>
#include "entity/entity.hpp"

#include <memory>

namespace flocking
{

    class Flock : public aiko::Entity
    {
    public:

        Flock() = default;
        virtual ~Flock() = default;

        virtual void init();
        virtual void update(const aiko::TimeStep & step) {};
        virtual void render() {};

    };

}