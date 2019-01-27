#include "camera.hpp"

#include "engine.hpp"
#include "renderer.hpp"
#include "input.hpp"
#include "module_connector.hpp"
#include "system_connector.hpp"
#include "event/engine_events.hpp"
#include "event/event_dispatcher.hpp"

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
        , m_velocity(0.001f)
    {

    }

    void Camera::connect(SystemConnector& systemConnectar, ModuleConnector& moduleConnector)
    {
        m_renderer = moduleConnector.findModule<Renderer>();
        m_input = moduleConnector.findModule<Input>();
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

        EventSystem::it().bind<WindowResizeEvent>(this, &Camera::onWindowResize);

    }

    void Camera::update(const TimeStep & step)
    {

        // TODO temporary code

        #define H3D_RAD2DEG 57.324840764f
        #define H3D_DEG2RAD  0.017453292f

        float curVel = m_velocity / step.getDelta();

        auto& p = m_transform.m_position;
        auto& r = m_transform.m_rotation;
        
        if (m_input->isKeyDown(GLFW_KEY_LEFT_SHIFT)) curVel *= 5;	// LShift
        
        if (m_input->isKeyDown(GLFW_KEY_W))
        {
            // Move forward
            p.x -= sinf(H3D_DEG2RAD * (r.y)) * cosf(-H3D_DEG2RAD * (r.x)) * curVel;
            p.y -= sinf(-H3D_DEG2RAD * (r.x)) * curVel;
            p.z -= cosf(H3D_DEG2RAD * (r.y)) * cosf(-H3D_DEG2RAD * (r.x)) * curVel;
        }
        
        if (m_input->isKeyDown(GLFW_KEY_S))
        {
            // Move backward
            p.x += sinf(H3D_DEG2RAD * (r.y)) * cosf(-H3D_DEG2RAD * (r.x)) * curVel;
            p.y += sinf(-H3D_DEG2RAD * (r.x)) * curVel;
            p.z += cosf(H3D_DEG2RAD * (r.y)) * cosf(-H3D_DEG2RAD * (r.x)) * curVel;
        }
        
        if (m_input->isKeyDown(GLFW_KEY_A))
        {
            // Strafe left
            p.x += sinf(H3D_DEG2RAD * (r.y - 90)) * curVel;
            p.z += cosf(H3D_DEG2RAD * (r.y - 90)) * curVel;
        }
        
        if (m_input->isKeyDown(GLFW_KEY_D))
        {
            // Strafe right
            p.x += sinf(H3D_DEG2RAD * (r.y + 90)) * curVel;
            p.z += cosf(H3D_DEG2RAD * (r.y + 90)) * curVel;
        }
    }

    void Camera::postUpdate(const TimeStep & step)
    {
        // TODO
        // Think of a better way to do this
        // post update call applyTransform that passed an hd3 node to apply a transform?

        // Set camera parameters
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

    const H3DNode& Camera::getCamera() const
    {
        return m_cam;
    }

    void Camera::onWindowResize(Event & event)
    {
        const auto& msg = static_cast<const WindowResizeEvent&>(event);
        resizeViewport(msg.width, msg.height);
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

