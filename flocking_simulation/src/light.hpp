#pragma once

#include "transform.hpp"

#include "Horde3D.h"

namespace aiko
{

    class Light
    {
    public:
        Light();
        virtual ~Light() = default;

        Transform&  getTranform();

    private:

        // TODO
        // not happy about it. Need to think a way of handle this better
        friend class WorldSystem;

        void        createLight(const H3DRes res);

        Transform   m_transform;
        H3DNode     m_lightId;

    };

}
