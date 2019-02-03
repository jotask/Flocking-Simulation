#pragma once

#include "Horde3D.h"

namespace aiko
{

    class Asset
    {
    public:
        /*
        Undefined       - An undefined resource, returned by getResourceType in case of error
        SceneGraph      - Scene graph subtree stored in XML format
        Geometry        - Geometrical data containing bones, vertices and triangles
        Animation       - Animation data
        Material        - Material script
        Code            - Text block containing shader source code
        Shader          - Shader program
        Texture         - Texture map
        ParticleEffect  - Particle configuration
        Pipeline        - Rendering pipeline
        ComputeBuffer   - Buffer with arbitrary data that can be accessed and modified by compute shaders
        */

        const enum class Type
        {
            DEFAULT
        };

        Asset(const Type type = Type::DEFAULT);

    private:

        const Type m_type;

    };

}
