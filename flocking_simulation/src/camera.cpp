#include "camera.hpp"

#include "entity/mesh.hpp"
#include "utils.hpp"


#include "engine.hpp"
#include "renderer.hpp"
#include "input.hpp"
#include "module_connector.hpp"
#include "system_connector.hpp"
#include "event/engine_events.hpp"
#include "event/event_dispatcher.hpp"
#include "utils.hpp"

#include <memory>

namespace aiko
{

    Camera::Camera(const Renderer& renderer, const Input& input)
        : m_cam(0)
        , m_anchor(0)
        , m_renderer(renderer)
        , m_input(input)
        , m_fov(45.0f)
        , m_nearPlane(0.1f)
        , m_farPlane(1000.0f)
        , m_velocity(0.001f)
    {

        if (true)
        {
            // setup: create an anchor node, so that the camera can always rotate around a relative(0, 0, 0) point
            m_anchor = h3dAddGroupNode(H3DRootNode, "camera-anchor");
            m_cam = h3dAddCameraNode(m_anchor, "camera-orbiter", m_renderer.getPipelineRes());

            m_transform.m_position.x = 5;
            m_transform.m_position.y = 3;
            m_transform.m_position.z = 19;

        }

        if (false)
        {

            // TODO add error checking
            // Add camera
            m_cam = h3dAddCameraNode(H3DRootNode, "Camera", m_renderer.getPipelineRes());


            m_transform.m_position.x = 5;
            m_transform.m_position.y = 3;
            m_transform.m_position.z = 19;

            m_transform.m_rotation.x = 7;
            m_transform.m_rotation.y = 15;
        }

        h3dSetNodeParamI(m_cam, H3DCamera::OccCullingI, 1);
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
        orbitCameraMovement(step);
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


    void Camera::controlCameraMovement(const TimeStep & step)
    {
#define H3D_RAD2DEG 57.324840764f
#define H3D_DEG2RAD  0.017453292f

        float curVel = m_velocity / step.getDelta();

        auto& p = m_transform.m_position;
        auto& r = m_transform.m_rotation;

        if (m_input.isKeyDown(GLFW_KEY_LEFT_SHIFT)) curVel *= 5;	// LShift

        if (m_input.isKeyDown(GLFW_KEY_W))
        {
            // Move forward
            p.x -= sinf(H3D_DEG2RAD * (r.y)) * cosf(-H3D_DEG2RAD * (r.x)) * curVel;
            p.y -= sinf(-H3D_DEG2RAD * (r.x)) * curVel;
            p.z -= cosf(H3D_DEG2RAD * (r.y)) * cosf(-H3D_DEG2RAD * (r.x)) * curVel;
        }

        if (m_input.isKeyDown(GLFW_KEY_S))
        {
            // Move backward
            p.x += sinf(H3D_DEG2RAD * (r.y)) * cosf(-H3D_DEG2RAD * (r.x)) * curVel;
            p.y += sinf(-H3D_DEG2RAD * (r.x)) * curVel;
            p.z += cosf(H3D_DEG2RAD * (r.y)) * cosf(-H3D_DEG2RAD * (r.x)) * curVel;
        }

        if (m_input.isKeyDown(GLFW_KEY_A))
        {
            // Strafe left
            p.x += sinf(H3D_DEG2RAD * (r.y - 90)) * curVel;
            p.z += cosf(H3D_DEG2RAD * (r.y - 90)) * curVel;
        }

        if (m_input.isKeyDown(GLFW_KEY_D))
        {
            // Strafe right
            p.x += sinf(H3D_DEG2RAD * (r.y + 90)) * curVel;
            p.z += cosf(H3D_DEG2RAD * (r.y + 90)) * curVel;
        }
    }

    void Camera::orbitCameraMovement(const TimeStep & step)
    {

        static auto dt = 0.0f;
        dt += step.getDelta();

        static const auto radius = 20.0f;

        auto& p = m_transform.m_position;

        p.x = radius * cos(dt);
        p.z = radius * sin(dt);

        lookAt();

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

}

