#include <iostream>

#include "engine/config/config.hpp"
#include "flocking/simulation.hpp"

int main(int argc, char** argv)
{

    aiko::Config::initGlobalConfig(argc, argv);

    flocking::FlockingSimulation simulation;

    simulation.run();

    return EXIT_SUCCESS;

}
