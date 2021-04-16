#include "engine.h"

namespace Octane
{
    Input::Input(HWND window)
    {
        //save window handle
        this->window = window;

        //create directInput object
        DirectInput8Create(GetModuleHandle(NULL),
                DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&di, NULL);

        //initialize keyboard
        di->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
        keyboard->SetDataFormat(&c_dfDIKeyboard);
        keyboard->SetCooperativeLevel(window,
                DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
        keyboard->Acquire();

        //clear key array
        memset(key_state, 0, 256);

        //initialize mouse
        di->CreateDevice(GUID_SysMouse, &mouse, NULL);
        mouse->SetDataFormat(&c_dfDIMouse);
        mouse->SetCooperativeLevel(window, 
                DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
        mouse->Acquire();
    }

    Input::~Input()
    {
        di->Release();
        keyboard->Release();
        mouse->Release();
    }

    void Input::update()
    {
        //poll state of the keyboard
        keyboard->Poll();
        if(!SUCCEEDED(keyboard->GetDeviceState(256, (LPVOID)&key_state)))
        {
            //keyboard device lost try to re-acquire
            keyboard->Acquire();
        }

        //poll state of the mouse
        mouse->Poll();
        if(!SUCCEEDED(mouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouse_state)))
        {
            //mouse device lost, try to re-acquire
            mouse->Acquire();
        }

        //get mouse position on screen (no DirectInput)
        GetCursorPos(&position);
        ScreenToClient(window, &position);
    }

    int Input::get_mouse_button(char button)
    {
        return (mouse_state.rgbButtons[button] & 0x80);
    }
};
