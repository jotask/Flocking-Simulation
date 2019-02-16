#pragma once

#include "module.hpp"

#include "Horde3D.h"

#include <vector>

namespace aiko
{

    class Event;

    class Renderer : public Module
    {
    public:

        Renderer(Engine& engine);

        virtual ~Renderer() = default;

        int getRenderInterface() const;

        const H3DRes getPipelineRes() const;

        bool init();
        bool initResources() final override;

    private:
        void resizeViewport(const int width, const int height);

        void            onWindowResize(Event& );

        int             m_renderInterface;
        int             m_curPipeline;

        using Pipelines = std::vector<H3DRes>;
        Pipelines       m_pipelineRes;

    };

}

