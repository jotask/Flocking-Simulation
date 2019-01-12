#pragma once

#include "transform.hpp"
#include "module.hpp"

#include "Horde3D.h"

namespace aiko
{

    class Renderer;
    class Display;

    class Camera : public Module
    {
    public:

        Camera(Engine& engine, float fov = 45.0f, float near_plane = 0.1f, float far_plane = 1000.0f);

        virtual ~Camera() = default;

        void                connect(ModuleConnector& moduleConnector) override;
        bool                init();
        bool                initResources() override;

        float               getFOV() const;
        float               getNearPlane() const;
        float               getFarPlane() const;

        const H3DNode&      getCamera() const;

        void                resizeViewport(const int width, const int height);

        Transform           m_transform;

    private:

        H3DNode             m_cam;

        // Systems
        Renderer*           m_renderer;

        float               m_fov;
        float               m_nearPlane;
        float               m_farPlane;

    };

}

