#include "fps_behaviour.hpp"

#include "engine/modules/renderer_module.hpp"
#include "engine/modules/input_module.hpp"
#include "engine/systems/camera/camera.hpp"

namespace aiko
{

    FpsBehaviour::FpsBehaviour(Camera& cam)
        : Behaviour(cam, BehaviourType::FPS)
        , m_velocity(0.001f)
    {

    }

    FpsBehaviour::~FpsBehaviour()
    {
    }

    void FpsBehaviour::createCamera(H3DNode & camNode)
    {
        // TODO add error checking
        // Add camera
        camNode = h3dAddCameraNode(H3DRootNode, "Camera", m_camera.getRendererSystem()->getPipelineRes());

        auto& transform = m_camera.getTransform();

        transform.m_position.x = 5;
        transform.m_position.y = 3;
        transform.m_position.z = 19;

        transform.m_rotation.x = 7;
        transform.m_rotation.y = 15;
    }

    void FpsBehaviour::update(const TimeStep & step)
    {
#define H3D_RAD2DEG 57.324840764f
#define H3D_DEG2RAD  0.017453292f

        float curVel = m_velocity / step.getDelta();

        auto& transform = m_camera.getTransform();
        auto* input = m_camera.getInputSystem();

        auto& p = transform.m_position;
        auto& r = transform.m_rotation;

        if (input->isKeyDown(GLFW_KEY_LEFT_SHIFT)) curVel *= 5;	// LShift

        if (input->isKeyDown(GLFW_KEY_W))
        {
            // Move forward
            p.x -= sinf(H3D_DEG2RAD * (r.y)) * cosf(-H3D_DEG2RAD * (r.x)) * curVel;
            p.y -= sinf(-H3D_DEG2RAD * (r.x)) * curVel;
            p.z -= cosf(H3D_DEG2RAD * (r.y)) * cosf(-H3D_DEG2RAD * (r.x)) * curVel;
        }

        if (input->isKeyDown(GLFW_KEY_S))
        {
            // Move backward
            p.x += sinf(H3D_DEG2RAD * (r.y)) * cosf(-H3D_DEG2RAD * (r.x)) * curVel;
            p.y += sinf(-H3D_DEG2RAD * (r.x)) * curVel;
            p.z += cosf(H3D_DEG2RAD * (r.y)) * cosf(-H3D_DEG2RAD * (r.x)) * curVel;
        }

        if (input->isKeyDown(GLFW_KEY_A))
        {
            // Strafe left
            p.x += sinf(H3D_DEG2RAD * (r.y - 90)) * curVel;
            p.z += cosf(H3D_DEG2RAD * (r.y - 90)) * curVel;
        }

        if (input->isKeyDown(GLFW_KEY_D))
        {
            // Strafe right
            p.x += sinf(H3D_DEG2RAD * (r.y + 90)) * curVel;
            p.z += cosf(H3D_DEG2RAD * (r.y + 90)) * curVel;
        }
    }

}
