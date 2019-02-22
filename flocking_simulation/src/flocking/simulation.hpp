#pragma once

#include "engine/app/app.hpp"
#include "engine/shared/timestep.hpp"
#include "engine/config/config.hpp"

#include "flock.hpp"

#include <sstream>
#include <vector>
#include <memory>
namespace flocking
{

    class FlockingSimulation : public aiko::Application
    {
    public:
        FlockingSimulation( aiko::Config& cfg = *aiko::Config::it());

        virtual void        init();

    private:

        // TODO change to shared ptr
        using Flocks        = std::vector<Flock*>;
        Flocks              m_flocks;
    };

}
