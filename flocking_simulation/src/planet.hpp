#pragma once

#include <vector>
#include "entity/entity.hpp"

#include "Horde3D.h"

#include <memory>

namespace aiko
{

    class Planet : public aiko::Entity
    {
    public:

        Planet(H3DRes res);
        virtual ~Planet() = default;

        virtual void init();
        virtual void update(const TimeStep & step);
        virtual void render() {};

        H3DNode getId() const;

        void moveOnCenter();

        virtual void    updateTransform();

    private:

        H3DNode m_id;

    };

}