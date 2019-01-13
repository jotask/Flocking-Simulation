#pragma once

#include "engine.hpp"
#include "timestep.hpp"
#include "config.hpp"

#include <sstream>

namespace flocking
{

    class FlockingSimulation : public aiko::Engine
    {
    public:
        FlockingSimulation( aiko::Config cfg );
    };

}
