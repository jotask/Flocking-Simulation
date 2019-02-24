#pragma once

#include "engine/shared/transform.hpp"
#include "engine/systems/system.hpp"
#include "engine/systems/entity/light.hpp"
#include "engine/shared/types.hpp"

#include "Horde3D.h"

#include <glm/glm.hpp>

#include <vector>
#include <array>

namespace aiko
{

    class AssetsSystem;

    class ParticleSystem : public System
    {
    public:

        ParticleSystem();

        virtual ~ParticleSystem() = default;

        void                connect(SystemConnector& systemConnectar, ModuleConnector& moduleConnector) override;
        void                init() override;
        bool                initResources() override;

        virtual void        update(const TimeStep& step) override;

    private:

        struct ParticleData
        {
            // Thanks to OpenGL implementations bad support for vec3 in buffers, passed to glsl, padding is required
            float position[ /*3*/ 4];
            float velocity[ /*3*/ 4];
        };

        AssetsSystem* m_assetSystem;

        H3DNode _compNode;
        H3DRes	_computeMatRes;
        float _animTime;
        unsigned int _computeGroupX;
        unsigned int _computeGroupY;

    };

}

