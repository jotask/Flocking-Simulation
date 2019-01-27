#pragma once

#include "transform.hpp"
#include "system.hpp"

#include "Horde3D.h"

namespace aiko
{

    class Renderer;
    class Display;
    class Input;

    class Event;

    class Camera : public System
    {
    public:

        Camera(float fov = 45.0f, float near_plane = 0.1f, float far_plane = 1000.0f);

        virtual ~Camera() = default;

        void                connect(SystemConnector& systemConnectar, ModuleConnector& moduleConnector) override;
        void                init() override;

        virtual void        update(const TimeStep& step) override;
        virtual void        postUpdate(const TimeStep& step) override;

        float               getFOV() const;
        float               getNearPlane() const;
        float               getFarPlane() const;

        const H3DNode&      getCamera() const;


        Transform           m_transform;

    private:

        void                onMouseMove(Event&);
        void                onWindowResize(Event&);
        void                resizeViewport(const int width, const int height);


        H3DNode             m_cam;

        // Systems
        Renderer*           m_renderer;
        Input*              m_input;

        float               m_fov;
        float               m_nearPlane;
        float               m_farPlane;

        float               m_velocity; // Velocity for movement. Temporally until better system

    };

}

