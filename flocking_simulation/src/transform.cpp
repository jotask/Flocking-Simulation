#include "transform.hpp"

namespace aiko
{
    Transform::Transform()
        : m_position(0.0f, 0.0f, 0.0f)
        , m_rotation(0.0f, 0.0f, 0.0f)
        , m_scale   (1.0f, 1.0f, 1.0f)
    {

    }

    void Transform::applyTransform(H3DNode node)
    {
        h3dSetNodeTransform(node
                            , m_position.x
                            , m_position.y
                            , m_position.z
                            , m_rotation.x
                            , m_rotation.y
                            , m_rotation.z
                            , m_scale.x
                            , m_scale.y
                            , m_scale.z
                        );
    }

}

