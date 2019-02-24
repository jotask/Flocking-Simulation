#include "camera.hpp"

#include "engine/systems/entity/mesh.hpp"
#include "engine/shared/utils.hpp"
#include "engine/engine.hpp"
#include "engine/modules/renderer_module.hpp"
#include "engine/modules/input_module.hpp"
#include "engine/modules/module_connector.hpp"
#include "engine/systems/system_connector.hpp"
#include "engine/event/engine_events.hpp"
#include "engine/event/event_dispatcher.hpp"
#include "engine/shared/utils.hpp"

// behaviour
#include "engine/systems/camera/behaviour/fps_behaviour.hpp"
#include "engine/systems/camera/behaviour/orbital_behaviour.hpp"
#include "engine/systems/camera/behaviour/dev_behaviour.hpp"

#include "GLFW/glfw3.h"

#include <memory>

namespace aiko
{

    Camera::Camera(const Renderer& renderer, const Input& input)
        : m_cam(0)
        , m_renderer(renderer)
        , m_input(input)
        , m_fov(45.0f)
        , m_nearPlane(0.1f)
        , m_farPlane(1000.0f)
        , m_type(BehaviourType::ORBITAL)
        , m_behaviour(std::nullopt)
    {

        switch (m_type)
        {
        case BehaviourType::DEV:
            createCameraBehaviour<DevBehaviour>();
            break;
        case BehaviourType::FPS:
            createCameraBehaviour<FpsBehaviour>();
            break;
        case BehaviourType::ORBITAL:
            createCameraBehaviour<OrbitalBehaviour>();
            break;
        case BehaviourType::NONE:
            assert(false);
            break;
        }

        assert(m_behaviour != std::nullopt);
        m_behaviour->get()->createCamera(m_cam);

        h3dSetNodeParamI(m_cam, H3DCamera::OccCullingI, 1);
    }

    template<class T>
    void Camera::createCameraBehaviour()
    {
        assert(m_behaviour == std::nullopt);
        auto& ptr = std::make_unique<T>(*this);
        m_behaviour = std::move(ptr);
    }

    void Camera::resizeViewport(const int width, const int height)
    {
        // Resize viewport
        h3dSetNodeParamI(m_cam, H3DCamera::ViewportXI, 0);
        h3dSetNodeParamI(m_cam, H3DCamera::ViewportYI, 0);
        h3dSetNodeParamI(m_cam, H3DCamera::ViewportWidthI, width);
        h3dSetNodeParamI(m_cam, H3DCamera::ViewportHeightI, height);

        // Set virtual camera parameters
        h3dSetupCameraView(m_cam, m_fov, (float)width / height, m_nearPlane, m_farPlane);

    }

    void Camera::init()
    {
    }

    void Camera::update(const TimeStep & step)
    {
        // orbitCameraMovement(step);
        m_transform.applyTransform(m_cam);
    }

    float Camera::getFOV() const
    {
        return m_fov;
    }

    float Camera::getNearPlane() const
    {
        return m_nearPlane;
    }

    float Camera::getFarPlane() const
    {
        return m_farPlane;
    }

    void Camera::lookAt(const glm::vec3 target)
    {

        auto& position = m_transform.m_position;
        auto& rotation = m_transform.m_rotation;

        const auto vXPos = target.x - position.x;
        const auto vYPos = target.y - position.y;
        const auto vZPos = target.z - position.z;

        rotation.x = utils::radToDeg(atan2(vYPos, sqrtf(vXPos * vXPos + vZPos * vZPos)));
        rotation.y = utils::radToDeg(atan2(-vXPos, -vZPos));

    }

    const H3DNode Camera::getCameraId() const
    {
        return m_cam;
    }

    void Camera::updateTransform()
    {
        m_transform.applyTransform(m_cam);
    }

    const Renderer * Camera::getRendererSystem() const
    {
        return &m_renderer;
    }

    const Input * Camera::getInputSystem() const
    {
        return &m_input;
    }

}

