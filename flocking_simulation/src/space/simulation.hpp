#pragma once

#include "engine/app/app.hpp"
#include "engine/shared/timestep.hpp"
#include "engine/config/config.hpp"

#include <sstream>
#include <vector>
#include <memory>

namespace space
{

    class SpaceSimulation : public aiko::Application
    {
    public:
        SpaceSimulation( aiko::Config& cfg = *aiko::Config::it());

        virtual void        init();

    private:

    };

}
