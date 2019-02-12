#include "flock.hpp"

#include "mesh.hpp"

#include <memory>

namespace flocking
{

    void Flock::init()
    {
        auto mesh = std::make_unique<aiko::Mesh>(*this);
        m_components.push_back(std::move(mesh));

        mesh->init();
    }

}

