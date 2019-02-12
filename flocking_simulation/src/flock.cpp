#include "flock.hpp"

#include "mesh.hpp"

#include <memory>

namespace flocking
{

    void Flock::init()
    {
        auto mesh = std::make_shared<aiko::Mesh>(*this);
        mesh->init();
        m_components.push_back(std::move(mesh));
    }

}

