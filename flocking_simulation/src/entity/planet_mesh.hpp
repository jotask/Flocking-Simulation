#pragma once

#include "mesh.hpp"

#include "Horde3D.h"

namespace aiko
{

    class Entity;

    class PlanetMesh : public Mesh
    {
    public:
        PlanetMesh(Entity& owner);

        virtual void init() override;

    private:

    };

}