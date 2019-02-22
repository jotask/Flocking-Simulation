#pragma once

#include "engine/systems/entity/entity.hpp"

#include "Horde3D.h"
#include "glm.hpp"

#include <vector>
#include <memory>

namespace aiko
{

    class Renderer;
    class Input;

    class Camera : public Entity
    {
    public:
        Camera(const Renderer&, const Input&);
        virtual ~Camera() = default;

        virtual void init();
        virtual void update(const TimeStep & step);
        virtual void render() {};

        float               getFOV() const;
        float               getNearPlane() const;
        float               getFarPlane() const;

        void                resizeViewport(const int width, const int height);

        void                lookAt(const glm::vec3 target = glm::vec3());

        const H3DNode       getCameraId() const;

        virtual void    updateTransform();

    private:

        // Movement
        void                controlCameraMovement(const TimeStep & step);
        void                orbitCameraMovement(const TimeStep & step);

        H3DNode             m_cam;
        H3DNode             m_anchor;

        const Renderer&     m_renderer;
        const Input&        m_input;

        float               m_fov;
        float               m_nearPlane;
        float               m_farPlane;

        float               m_velocity; // Velocity for movement. Temporally until better system

    };

}