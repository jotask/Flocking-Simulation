#include "camera.hpp"

#include "engine.hpp"
#include "renderer.hpp"
#include "module_connector.hpp"
#include "system_connector.hpp"

namespace aiko
{

    Camera::Camera(float fov, float nearPlane, float farPlane)
        :   System()
        , m_transform()
        , m_cam(0)
        , m_renderer(nullptr)
        , m_fov(fov)
        , m_nearPlane(nearPlane)
        , m_farPlane(farPlane)
        , m_velocity(0.1f)
    {

    }

    void Camera::connect(SystemConnector& systemConnectar, ModuleConnector& moduleConnector)
    {
        m_renderer = moduleConnector.findModule<Renderer>();
    }

    void Camera::init()
    {
        // TODO add error checking
        // Add camera
        m_cam = h3dAddCameraNode(H3DRootNode, "Camera", m_renderer->getPipelineRes());
        h3dSetNodeParamI(m_cam, H3DCamera::OccCullingI, 1);

        m_transform.m_position.x =  5;
        m_transform.m_position.y =  3;
        m_transform.m_position.z = 19;

        m_transform.m_rotation.x =  7;
        m_transform.m_rotation.y = 15;
    }

    void Camera::update(const TimeStep & step)
    {

        // TODO temporally code

        // #define H3D_RAD2DEG 57.324840764f
        // #define H3D_DEG2RAD  0.017453292f

        // float curVel = _velocity / delta;
        // 
        // if (isKeyDown(GLFW_KEY_LEFT_SHIFT)) curVel *= 5;	// LShift
        // 
        // if (isKeyDown(GLFW_KEY_W))
        // {
        //     // Move forward
        //     _x -= sinf(H3D_DEG2RAD * (_ry)) * cosf(-H3D_DEG2RAD * (_rx)) * curVel;
        //     _y -= sinf(-H3D_DEG2RAD * (_rx)) * curVel;
        //     _z -= cosf(H3D_DEG2RAD * (_ry)) * cosf(-H3D_DEG2RAD * (_rx)) * curVel;
        // }
        // 
        // if (isKeyDown(GLFW_KEY_S))
        // {
        //     // Move backward
        //     _x += sinf(H3D_DEG2RAD * (_ry)) * cosf(-H3D_DEG2RAD * (_rx)) * curVel;
        //     _y += sinf(-H3D_DEG2RAD * (_rx)) * curVel;
        //     _z += cosf(H3D_DEG2RAD * (_ry)) * cosf(-H3D_DEG2RAD * (_rx)) * curVel;
        // }
        // 
        // if (isKeyDown(GLFW_KEY_A))
        // {
        //     // Strafe left
        //     _x += sinf(H3D_DEG2RAD * (_ry - 90)) * curVel;
        //     _z += cosf(H3D_DEG2RAD * (_ry - 90)) * curVel;
        // }
        // 
        // if (isKeyDown(GLFW_KEY_D))
        // {
        //     // Strafe right
        //     _x += sinf(H3D_DEG2RAD * (_ry + 90)) * curVel;
        //     _z += cosf(H3D_DEG2RAD * (_ry + 90)) * curVel;
        // }
    }

    void Camera::postUpdate(const TimeStep & step)
    {
        // TODO
        // Think a better way to do this
        // post update call applyTransform that passed an hd3 node to apply a transform?

        // Set camera parameters
        const auto p = m_transform.m_position;
        const auto r = m_transform.m_rotation;
        h3dSetNodeTransform(m_cam, p.x, p.y, p.z, r.x, r.y, r.z, 1, 1, 1);
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

    const H3DNode& Camera::getCamera() const
    {
        return m_cam;
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

}

