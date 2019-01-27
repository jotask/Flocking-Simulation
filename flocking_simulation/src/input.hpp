#pragma once

#include "module.hpp"

#include <GLFW/glfw3.h>

namespace aiko
{

    // Forward declaration
    class Display;

    class Input : public Module
    {
    public:

        Input           (Engine& engine);
        virtual         ~Input() = default;

        void            connect(ModuleConnector& moduleConnector) override;
        bool            init();

        bool            isKeyDown(int key) const;

    private:

        void            keyEventHandler(int key, int scancode, int action, int mods);
        void            mouseMoveHandler(float x, float y, float prev_x, float prev_y);

        Display*        m_display;

    };

}

