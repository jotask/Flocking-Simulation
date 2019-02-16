#include "flock.hpp"

#include "entity/mesh.hpp"
#include "utils.hpp"

#include <memory>

namespace flocking
{

    Flock::Flock()
    {

    }

    void Flock::init()
    {
        auto mesh = std::make_shared<aiko::Mesh>(*this);
        mesh->init();
        m_components.push_back(std::move(mesh));
    }

    void Flock::updateTransform()
    {

    }

    void Flock::randomise()
    {
        // m_transform.m_position = aiko::utils::getRandom();
        m_transform.m_scale = {5.f, 5.f, 5.f};
    }

}

