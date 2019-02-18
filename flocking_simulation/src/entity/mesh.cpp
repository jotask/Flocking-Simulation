#include "mesh.hpp"

#include "entity.hpp"
#include "../asset_system.hpp"

#include "Horde3DUtils.h"

#include <array>

namespace aiko
{

    Mesh::Mesh(Entity& owner)
        : Component(owner)
    {

    }

    void Mesh::updateTransform()
    {
        const auto p = m_owner.m_transform.m_position;
        const auto r = m_owner.m_transform.m_rotation;
        const auto s = m_owner.m_transform.m_scale;
        h3dSetNodeTransform(m_mesh, p.x, p.y, p.z, r.x, r.y, r.z, s.x, s.y, s.z);
    }

    void Mesh::init()
    {

    }

    H3DNode Mesh::getId()
    {
        return m_mesh;
    }

}