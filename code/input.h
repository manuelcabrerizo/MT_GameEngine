#pragma once

#include "engine.h"

namespace Octane
{
    class Input
    {
    private:
        HWND window;
        IDirectInput8* di;
        IDirectInputDevice8* keyboard;
        char key_state[256];
        IDirectInputDevice8* mouse;
        DIMOUSESTATE mouse_state;
        POINT position;
    public: 
        Input(HWND window);
        virtual ~Input();
        void update();
        char get_key_state(int key) {return key_state[key];}
        long get_mouse_pos_x() {return position.x;}
        long get_mouse_pos_y() {return position.y;}
        int get_mouse_button(char button);
        long get_mouse_delta_x() {return (long)mouse_state.lX;}
        long get_mouse_delta_y() {return (long)mouse_state.lY;}
        long get_mouse_wheel() {return (long)mouse_state.lZ;}
    };
};
