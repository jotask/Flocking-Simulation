#include "planet.hpp"

#include "engine/shared/utils.hpp"

#include <memory>

namespace aiko
{

    Planet::Planet()
        : m_id()
    {

    }

    void Planet::init()
    {

    }

    void Planet::update(const TimeStep & step)
    {

    }

    void Planet::moveOnCenter()
    {
        auto& p = m_transform.m_position;
        p.x = 0;
        p.y = 0;
        p.z = 0;
    }

    void Planet::updateTransform()
    {
        m_transform.applyTransform(m_id);
    }

}

