#pragma once

#include "app.hpp"
#include "timestep.hpp"
#include "config.hpp"

#include "flock.hpp"

#include <sstream>
#include <vector>

namespace flocking
{

    class FlockingSimulation : public aiko::Application
    {
    public:
        FlockingSimulation( aiko::Config& cfg = *aiko::Config::it());

        virtual void        init();

    private:

        std::vector<Flock> m_flocks;

    };

}
