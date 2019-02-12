#include <iostream>

#include "config.hpp"
#include "simulation.hpp"

int main(int argc, char** argv)
{

    aiko::Config::initGlobalConfig(argc, argv);

    flocking::FlockingSimulation simulation;

    simulation.run();

    return EXIT_SUCCESS;

}
