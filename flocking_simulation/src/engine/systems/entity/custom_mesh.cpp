#include "custom_mesh.hpp"

#include "engine/systems/entity/entity.hpp"
#include "engine/systems/asset_system.hpp"

#include "Horde3DUtils.h"

#include <array>

namespace aiko
{

    CustomMesh::CustomMesh(Entity& owner)
        : Mesh(owner)
    {

    }

    void CustomMesh::init()
    {

        static auto posData = std::array<float, 12>({
                                        0, 0, 0,
                                        1, 0, 0,
                                        0, 1, 0,
                                        1, 1, 0
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

        /*
        
        // Environment
        const auto envRes = m_assetSystem->loadResource("models/sphere/sphere.scene.xml", H3DResTypes::SceneGraph);

        // Shader for deferred shading
        const auto lightMatRes = m_assetSystem->loadResource("materials/light.material.xml", H3DResTypes::Material);
        
        */

        auto* assetsSystem = AssetsSystem::it();
        const auto lightMatRes = assetsSystem->loadResource("materials/light.material.xml", H3DResTypes::Material);
        const auto matRes = assetsSystem->loadResource("materials/light.material.xml", H3DResTypes::Material);

        H3DRes geoRes = h3dutCreateGeometryRes("geoRes", 4, 6, posData.data(), indexData.data(), normalData.data(), 0, 0, uvData.data(), 0);
        H3DNode model = h3dAddModelNode(H3DRootNode, "DynGeoModelNode", geoRes);
        m_mesh = h3dAddMeshNode(model, "DynGeoMesh", matRes, 0, 6, 0, 3);

    }

}