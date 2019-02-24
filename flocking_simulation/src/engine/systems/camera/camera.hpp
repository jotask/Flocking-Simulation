#pragma once

#include "engine/shared/types.hpp"
#include "engine/systems/entity/entity.hpp"
#include "engine/systems/camera/behaviour/behaviour.hpp"

#include "Horde3D.h"
#include "glm/glm.hpp"

#include <vector>
#include <memory>
#include <optional>

namespace aiko
{

    class Renderer;
    class Input;

    class Camera : public Entity
    {
    public:
        Camera(const Renderer&, const Input&);
        virtual ~Camera() = default;

        virtual void        init();
        virtual void        update(const TimeStep & step);
        virtual void        render() {};

        float               getFOV() const;
        float               getNearPlane() const;
        float               getFarPlane() const;

        void                resizeViewport(const int width, const int height);

        void                lookAt(const glm::vec3 target = glm::vec3());

        const H3DNode       getCameraId() const;

        virtual void        updateTransform();

        const Renderer*     getRendererSystem() const;
        const Input*        getInputSystem() const;

    private:

        H3DNode             m_cam;

        const Renderer&     m_renderer;
        const Input&        m_input;

        float               m_fov;
        float               m_nearPlane;
        float               m_farPlane;

        BehaviourType       m_type;

        using CameraBehaviourPtr = AikoUPtr<Behaviour >;
        using CameraBehaviour = std::optional<CameraBehaviourPtr>;
        CameraBehaviour      m_behaviour;

        template<class T>
        void createCameraBehaviour();

    };

}
