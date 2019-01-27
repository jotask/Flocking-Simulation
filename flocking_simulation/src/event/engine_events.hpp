#pragma once

#include "event.hpp"

namespace aiko
{

#define DEFINE_EVENT(MSG)                                       \
    class MSG : public Event                                    \
    {                                                           \
    public:                                                     \
        MSG() = default;                                        \
        virtual ~MSG() = default;                               \
        virtual EventId     getId() const { return "MSG"; };    \
    };                                                          \

    DEFINE_EVENT(WindowCloseEvent);
    DEFINE_EVENT(WindowResizeEvent);

}
