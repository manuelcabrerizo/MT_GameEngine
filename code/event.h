#pragma once

#include "engine.h"

namespace Octane
{
    class IEvent
    {
    protected:
        int id;
    public:
        IEvent();
        virtual ~IEvent() {}
        int get_id() {return id;}
    };

    enum eventtype
    {
        EVENT_TIMER       = 10,
        EVENT_KEYPRESS    = 20,
        EVENT_KEYRELEASE  = 30,
        EVENT_MOUSECLICK  = 40,
        EVENT_MOUSEMOTION = 50,
        EVENT_MOUSEWHEEL  = 60,
        EVENT_MOUSEMOVE   = 70,
    };
    
    class KeyPressEvent : public IEvent
    {
    public:
        int keycode;
        KeyPressEvent(int key);
    };

    class KeyReleaseEvent : public IEvent
    {
    public:
        int keycode;
        KeyReleaseEvent(int key);
    };

    class MouseClickEvent : public IEvent
    {
    public:
        int button;
        MouseClickEvent(int btn);
    };

    class MouseMotionEvent : public IEvent
    {
    public:
        int delta_x, delta_y;
        MouseMotionEvent(int dx, int dy);
    };

    class MouseWheelEvent : public IEvent
    {
    public:
        int wheel;
        MouseWheelEvent(int whl);
    };

    class MouseMoveEvent : public IEvent
    {
    public:
        int pos_x, pos_y;
        MouseMoveEvent(int px, int py);
    };

};
