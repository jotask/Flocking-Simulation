#include "mesh.hpp"

#include "entity/entity.hpp"
#include "asset_system.hpp"

#include "Horde3DUtils.h"

#include <array>

namespace aiko
{

    Mesh::Mesh(Entity& owner)
        : Component(owner)
    {

    }

    void Mesh::init()
    {

        static auto posData = std::array<float, 12>({
                                         0,  0, 0,
                                        10,  0, 0,
                                         0, 10, 0,
                                        10, 10, 0
                                        });

        static auto indexData = std::array<unsigned int, 12>({ 0, 1, 2, 2, 1, 3 });

        static auto normalData = std::array<short, 12>({
            0, 0, 1,
            0, 0, 1,
            0, 0, 1,
            0, 0, 1
            });

        static auto uvData = std::array<float, 8>({
            0, 0,
            1, 0,
            0, 1,
            1, 1
            });

        auto* assetsSystem = AssetsSystem::it();
        const auto matRes = assetsSystem->loadResource("materials/testpattern.material.xml", H3DResTypes::Material);

        H3DRes geoRes = h3dutCreateGeometryRes("geoRes", 4, 6, posData.data(), indexData.data(), normalData.data(), 0, 0, uvData.data(), 0);
        H3DNode model = h3dAddModelNode(H3DRootNode, "DynGeoModelNode", geoRes);
        H3DNode cube  = h3dAddMeshNode(model, "DynGeoMesh", matRes, 0, 6, 0, 3);

    }

}
