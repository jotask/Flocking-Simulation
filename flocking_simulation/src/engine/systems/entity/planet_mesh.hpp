#pragma once

#include "engine/systems/entity/mesh.hpp"

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