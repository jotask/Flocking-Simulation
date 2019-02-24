#pragma once

#include "engine/shared/transform.hpp"
#include "engine/systems/system.hpp"
#include "engine/systems/camera/camera.hpp"

#include <vector>

namespace aiko
{

    class Renderer;
    class Display;
    class Input;

    class Event;

    class CameraSystem : public System
    {
    public:

        CameraSystem();

        virtual ~CameraSystem() = default;

        void                connect(SystemConnector& systemConnectar, ModuleConnector& moduleConnector) override;
        void                init() override;

        virtual void        update(const TimeStep& step) override;
        virtual void        postUpdate(const TimeStep& step) override;

        const Camera&      getCamera() const;

    private:

        void                onMouseMove(Event&);
        void                onWindowResize(Event&);
        void                resizeViewport(const int width, const int height);

        // Systems
        Renderer*           m_renderer;
        Input*              m_input;

        using Cameras       = std::vector<Camera*>;
        Cameras             m_cameras;

    };

}

