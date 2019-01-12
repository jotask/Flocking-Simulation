#include "camera.hpp"

#include "engine.hpp"
#include "renderer.hpp"
#include "module_connector.hpp"

namespace aiko
{

    Camera::Camera(Engine& engine, float fov, float nearPlane, float farPlane)
        :   Module(engine)
        , m_transform()
        , m_cam(0)
        , m_renderer(nullptr)
        , m_fov(fov)
        , m_nearPlane(nearPlane)
        , m_farPlane(farPlane)
    {

    }

    void Camera::connect(ModuleConnector & moduleConnector)
    {
        m_renderer = moduleConnector.findModule<Renderer>();
    }

    bool Camera::init()
    {
        return true;
    }

    bool Camera::initResources()
    {
        // TODO add error checking
        // TODO this ideally should exist in init, but because is dependent of resource of the renderer, lives here at the moment
        // Add camera
        m_cam = h3dAddCameraNode(H3DRootNode, "Camera", m_renderer->getPipelineRes());
        h3dSetNodeParamI(m_cam, H3DCamera::OccCullingI, 1);
        return true;
    }
    ;

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

