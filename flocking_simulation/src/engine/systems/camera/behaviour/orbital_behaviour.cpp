#include "orbital_behaviour.hpp"

#include "engine/modules/renderer_module.hpp"
#include "engine/systems/camera/camera.hpp"

namespace aiko
{

    OrbitalBehaviour::OrbitalBehaviour(Camera& cam)
        : Behaviour(cam, BehaviourType::ORBITAL)
        , m_anchor(0)
    {
        auto& transform = m_camera.getTransform();
        transform.m_position.x = 5;
        transform.m_position.y = 3;
        transform.m_position.z = 19;
    }

    OrbitalBehaviour::~OrbitalBehaviour()
    {
    }

    void OrbitalBehaviour::createCamera(H3DNode & camNode)
    {
        // setup: create an anchor node, so that the camera can always rotate around a relative(0, 0, 0) point
        m_anchor = h3dAddGroupNode(H3DRootNode, "camera-anchor");
        camNode = h3dAddCameraNode(m_anchor, "camera-orbiter", m_camera.getRendererSystem()->getPipelineRes());

    }

    void OrbitalBehaviour::update(const TimeStep & step)
    {

        static auto dt = 0.0f;
        dt += step.getDelta();

        static const auto radius = 5.0f;

        auto& p = m_camera.getTransform().m_position;

        p.x = radius * cos(dt);
        p.z = radius * sin(dt);

        m_camera.lookAt();

    }

}
