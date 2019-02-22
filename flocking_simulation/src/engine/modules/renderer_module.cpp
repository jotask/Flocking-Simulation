#include "renderer_module.hpp"

#include "engine/modules/display_module.hpp"
#include "engine/event/engine_events.hpp"
#include "engine/event/event_dispatcher.hpp"

#include <GLFW/glfw3.h>

namespace aiko
{

    Renderer::Renderer(Engine& engine)
        : Module(engine)
        , m_renderInterface(H3DRenderDevice::OpenGL4)
        , m_curPipeline(2) // Default to HDR pipeline
    {

    }

    int Renderer::getRenderInterface() const
    {
        return m_renderInterface;
    }

    const H3DRes Renderer::getPipelineRes() const
    {
        return m_pipelineRes[m_curPipeline];
    }

    void Renderer::resizeViewport(const int width, const int height)
    {
        // Set virtual camera parameters
        for (auto& pipeline : m_pipelineRes)
        {
            h3dResizePipelineBuffers(pipeline, width, height);
        }
    }

    void Renderer::onWindowResize(Event & event)
    {
        const auto& msg = static_cast<const WindowResizeEvent&>(event);
        resizeViewport(msg.width, msg.height);
    }

    bool Renderer::init()
    {
        EventSystem::it().bind<WindowResizeEvent>(this, &Renderer::onWindowResize);
        return true;
    }

    bool Renderer::initResources()
    {
        // TODO add error checking
        // Pipelines
        m_pipelineRes.push_back(h3dAddResource(H3DResTypes::Pipeline, "pipelines/forward.pipeline.xml", 0));
        m_pipelineRes.push_back(h3dAddResource(H3DResTypes::Pipeline, "pipelines/deferred.pipeline.xml", 0));
        m_pipelineRes.push_back(h3dAddResource(H3DResTypes::Pipeline, "pipelines/hdr.pipeline.xml", 0));
        return true;
    }

}

