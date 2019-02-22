#pragma once

#include "mesh.hpp"

#include "Horde3D.h"

namespace aiko
{

    class Entity;

    class CustomMesh : public Mesh
    {
    public:
        CustomMesh(Entity& owner);

        virtual void init() override;

    private:

        H3DNode m_mesh;

    };

}