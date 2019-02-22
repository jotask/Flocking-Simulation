#pragma once

#include "engine/systems/entity/entity.hpp"

#include "Horde3D.h"

namespace aiko
{

    class Planet : public aiko::Entity
    {
    public:

        Planet();
        virtual ~Planet() = default;

        virtual void init();
        virtual void update(const TimeStep & step);
        virtual void render() {};

        void moveOnCenter();

        virtual void    updateTransform();

    private:

        H3DNode m_id;

    };

}