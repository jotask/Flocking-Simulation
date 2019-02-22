#pragma once

#include "transform.hpp"

#include "Horde3D.h"

#include "glm/glm.hpp"

namespace aiko
{

    class Light
    {
    public:

        using Color = glm::vec3;

        Light();
        virtual ~Light() = default;

        Transform&  getTranform();

        void randomise();

        Color& getColor();

        void updateLight();

    private:

        // TODO
        // not happy about it. Need to think a way of handle this better
        friend class WorldSystem;

        void        createLight(const H3DRes res);

        Transform   m_transform;
        H3DNode     m_lightId;

        float       m_radius;
        float       m_fov;
        Color       m_color;

    };

}
