#include "simulation.hpp"

#include "Horde3D.h"
#include "Horde3DUtils.h"
#include <iostream>
#include <math.h>
#include <iomanip>

namespace flocking
{

    FlockingSimulation::FlockingSimulation(aiko::Config& cfg)
        : Application(cfg)
    {

    }

    void FlockingSimulation::init()
    {

        static constexpr const auto numberOfFlocks = 1;

        for (auto i = 0u; i < numberOfFlocks ; i++)
        {
            auto flock = Flock();
            flock.init();
            m_flocks.push_back(flock);
        }

    }

}
