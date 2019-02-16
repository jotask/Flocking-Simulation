#include "planet.hpp"

#include "utils.hpp"

#include <memory>

namespace aiko
{

    Planet::Planet(H3DRes res)
        : m_id()
    {
        m_id = h3dAddNodes(H3DRootNode, res);
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

