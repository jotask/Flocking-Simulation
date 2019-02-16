#pragma once

#include "transform.hpp"
#include "system.hpp"

#include "Horde3D.h"

#include "glm.hpp"

namespace aiko
{

    class Renderer;
    class Display;
    class Input;

    class Event;

    class CameraSystem : public System
    {
    public:

        CameraSystem(float fov = 45.0f, float near_plane = 0.1f, float far_plane = 1000.0f);

        virtual ~CameraSystem() = default;

        void                connect(SystemConnector& systemConnectar, ModuleConnector& moduleConnector) override;
        void                init() override;

        virtual void        update(const TimeStep& step) override;
        virtual void        postUpdate(const TimeStep& step) override;

        float               getFOV() const;
        float               getNearPlane() const;
        float               getFarPlane() const;

        const H3DNode&      getCamera() const;


        Transform           m_transform;

        void                lookAt(const glm::vec3 target = glm::vec3());

    private:

        void                onMouseMove(Event&);
        void                onWindowResize(Event&);
        void                resizeViewport(const int width, const int height);

        // Movement
        void                controlCameraMovement(const TimeStep & step);
        void                orbitCameraMovement(const TimeStep & step);

        H3DNode             m_cam;
        H3DNode             m_anchor;

        // Systems
        Renderer*           m_renderer;
        Input*              m_input;

        float               m_fov;
        float               m_nearPlane;
        float               m_farPlane;

        float               m_velocity; // Velocity for movement. Temporally until better system

    };

}

