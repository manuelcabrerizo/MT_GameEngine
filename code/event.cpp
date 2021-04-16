#include "engine.h"

namespace Octane
{
    IEvent::IEvent()
    {
        id = 0;
    }

    KeyPressEvent::KeyPressEvent(int key)
    {
        id = EVENT_KEYPRESS;
        keycode = key;
    }

    KeyReleaseEvent::KeyReleaseEvent(int key)
    {
        id = EVENT_KEYRELEASE;
        keycode = key;
    }

    MouseClickEvent::MouseClickEvent(int btn)
    {
        id = EVENT_MOUSECLICK;
        button = btn;
    }

    MouseMotionEvent::MouseMotionEvent(int dx, int dy)
    {
        id = EVENT_MOUSEMOTION;
        delta_x = dx;
        delta_y = dy;
    }

    MouseWheelEvent::MouseWheelEvent(int whl)
    {
        id = EVENT_MOUSEWHEEL;
        wheel = whl;
    }

    MouseMoveEvent::MouseMoveEvent(int px, int py)
    {
        id = EVENT_MOUSEMOVE;
        pos_x = px;
        pos_y = py;
    }
};
