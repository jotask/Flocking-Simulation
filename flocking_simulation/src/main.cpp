#include <iostream>

#include "config.hpp"
#include "simulation.hpp"

int main(int argc, char** argv)
{

    aiko::Config::initGlobalConfig(argc, argv);

    flocking::FlockingSimulation app(*aiko::Config::it());

    const auto exitStatus = app.run();

    std::cout << exitStatus << std::endl;

    return EXIT_SUCCESS;

}
