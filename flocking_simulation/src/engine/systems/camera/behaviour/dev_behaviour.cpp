#include "dev_behaviour.hpp"

#include "engine/modules/renderer_module.hpp"
#include "engine/modules/input_module.hpp"
#include "engine/systems/camera/camera.hpp"

namespace aiko
{

    DevBehaviour::DevBehaviour(Camera& cam)
        : Behaviour(cam, BehaviourType::FPS)
    {

    }

    void DevBehaviour::createCamera(H3DNode & camNode)
    {
        // TODO add error checking
        // Add camera
        // camNode = h3dAddCameraNode(H3DRootNode, "Camera", m_camera.getRendererSystem()->getPipelineRes());

        auto& transform = m_camera.getTransform();

        transform.m_position.x = 5;
        transform.m_position.y = 3;
        transform.m_position.z = 19;

        transform.m_rotation.x = 7;
        transform.m_rotation.y = 15;
    }

    void DevBehaviour::update(const TimeStep & step)
    {

    }

}
