#include "camera_system.hpp"

#include "engine/systems/camera/camera.hpp"
#include "engine/engine.hpp"
#include "engine/modules/renderer_module.hpp"
#include "engine/modules/input_module.hpp"
#include "engine/modules/module_connector.hpp"
#include "engine/systems/system_connector.hpp"
#include "engine/event/engine_events.hpp"
#include "engine/event/event_dispatcher.hpp"
#include "engine/shared/utils.hpp"
#include "engine/systems/entity/entity_system.hpp"

namespace aiko
{

    CameraSystem::CameraSystem()
        : System()
        , m_renderer(nullptr)
        , m_cameras()
    {

    }

    void CameraSystem::connect(SystemConnector& systemConnectar, ModuleConnector& moduleConnector)
    {
        m_renderer = moduleConnector.findModule<Renderer>();
        m_input = moduleConnector.findModule<Input>();
    }

    void CameraSystem::init()
    {

        EventSystem::it().bind<WindowResizeEvent>(this, &CameraSystem::onWindowResize);
        EventSystem::it().bind<OnMouseMoveEvent>(this, &CameraSystem::onMouseMove);

        auto* camera = EntitySystem::createEntity<Camera>(*m_renderer, *m_input);
        m_cameras.push_back(camera);

    }

    void CameraSystem::update(const TimeStep & step)
    {

    }

    void CameraSystem::postUpdate(const TimeStep & step)
    {
        // TODO
        // Think of a better way to do this
        // post update call applyTransform that passed an hd3 node to apply a transform?

        // Set camera parameters
        // m_transform.applyTransform(m_cam);
    }

    const Camera& CameraSystem::getCamera() const
    {
        assert(m_cameras.empty() == false);
        return *m_cameras.back();
    }

    void CameraSystem::onMouseMove(Event& event)
    {
        const auto& msg = static_cast<const OnMouseMoveEvent&>(event);

        // TODO Rotate camera. Improve and investigate following lines

        // float dx = msg.x - msg.prevX;
        // float dy = msg.prevY - msg.y;
        // 
        // m_transform.m_rotation.y += dx;
        // m_transform.m_rotation.x += dy;
        // 
        // if (m_transform.m_rotation.x > 90) m_transform.m_rotation.x = 90;
        // if (m_transform.m_rotation.x < -90) m_transform.m_rotation.x = -90;
    }

    void CameraSystem::onWindowResize(Event & event)
    {
        const auto& msg = static_cast<const WindowResizeEvent&>(event);
        resizeViewport(msg.width, msg.height);
    }

    void CameraSystem::resizeViewport(const int width, const int height)
    {
        for (auto* cam : m_cameras)
        {
            cam->resizeViewport(width, height);
        }
    }

}

