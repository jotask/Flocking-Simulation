#include "simulation.hpp"

#include "entity/entity_system.hpp"

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

        static constexpr const auto numberOfFlocks = 10;

        for (auto i = 0u; i < numberOfFlocks ; i++)
        {
            auto* flock = aiko::EntitySystem::it()->createEntity<Flock>();
            flock->init();
            m_flocks.push_back(flock);
        }

    }

}
