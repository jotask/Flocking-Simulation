#include "behaviour.hpp"

namespace aiko
{
    Behaviour::Behaviour(Camera& cam, BehaviourType type)
        : m_camera(cam)
        , m_type(type)
    {

    }

    const BehaviourType Behaviour::getType() const
    {
        return m_type;
    }

}
