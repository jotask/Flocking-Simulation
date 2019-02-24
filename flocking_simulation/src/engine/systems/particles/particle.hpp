#pragma once

#include "Horde3D.h"

#include <string>

namespace aiko
{

    class Particle
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
        using Types = H3DResTypes::List;
        using AssetId = H3DRes;

        Particle(const char* path, const Types type);

        void                load();

        const H3DRes        getId() const;

    private:
        const Types             m_type;
        const std::string       m_path;

        AssetId                 m_resource;

    };

}
