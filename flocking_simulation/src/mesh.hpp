#pragma once

#include "entity/component.hpp"

#include "Horde3D.h"

namespace aiko
{

    class Entity;

    class Mesh : public Component
    {
    public:
        Mesh(Entity& owner);

        virtual void init() override;

    };

}
