#include "planet_mesh.hpp"

#include "entity.hpp"
#include "../asset_system.hpp"

#include "Horde3DUtils.h"

#include <array>

namespace aiko
{

    PlanetMesh::PlanetMesh(Entity& owner)
        : Mesh(owner)
    {

    }

    void PlanetMesh::init()
    {
        static const auto envRes = AssetsSystem::it()->loadResource("models/sphere/sphere.scene.xml", H3DResTypes::SceneGraph);
        m_mesh = h3dAddNodes(H3DRootNode, envRes);
    }

}