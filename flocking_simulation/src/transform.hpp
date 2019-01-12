#pragma once

#include "glm/glm.hpp"

namespace aiko
{

    class Transform
    {
    public:
        Transform();
        ~Transform() = default;

        glm::vec3 m_position;
        glm::vec3 m_rotation;

    };

}
