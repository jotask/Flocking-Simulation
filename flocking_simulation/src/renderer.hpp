#pragma once

#include "module.hpp"

#include "Horde3D.h"

#include <vector>

namespace aiko
{

    class Renderer : public Module
    {
    public:

        Renderer(Engine& engine);

        virtual ~Renderer() = default;

        int getRenderInterface() const;

        H3DRes getPipelineRes();

        void resizeViewport(const int width, const int height);

        bool init();
        bool initResources() final override;

    private:

        int             m_renderInterface;
        int             m_curPipeline;

        using Pipelines = std::vector<H3DRes>;
        Pipelines       m_pipelineRes;

    };

}

