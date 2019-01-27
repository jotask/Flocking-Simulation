#pragma once

#include "event.hpp"

namespace aiko
{

    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() = default;
        virtual ~WindowCloseEvent() = default;
        virtual EventId     getId() const { return "WindowCloseEvent"; }
    };

    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent()
            : width(-1)
            , height(-1)
        {

        };

        WindowResizeEvent(const int w, const int h)
            : width(w)
            , height(h)
        {

        };

        virtual ~WindowResizeEvent() = default;
        virtual EventId     getId() const { return "WindowResizeEvent"; }

        const int width;
        const int height;
    };

    class OnMouseEnterEvent : public Event
    {
    public:
        OnMouseEnterEvent() : entered(false) {};
        OnMouseEnterEvent(const bool enter) : entered(enter) {};
        virtual ~OnMouseEnterEvent() = default;
        virtual EventId     getId() const { return "OnMouseEnterEvent"; }
        const bool entered;
    };

}
