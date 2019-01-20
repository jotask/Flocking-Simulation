#pragma once

#include "Horde3D.h"
#include "glm.hpp"

namespace aiko
{

    class Transform
    {
    public:
        Transform();
        ~Transform() = default;

        void applyTransform(H3DNode node);

        glm::vec3 m_position;
        glm::vec3 m_rotation;
        glm::vec3 m_scale;

    };

}
