//#include "stdafx.h"
#include "engine.h"
using namespace std;

namespace Octane
{
    Engine::Engine()
    {
        p_apptitle = "Octane Engine";
        p_screen_width = 640;
        p_screen_height = 480;
        p_color_depth = 32;
        p_fullscreen = false;
        p_device = NULL;
        p_core_frame_count = 0;
        p_core_frame_rate = 0;
        p_screen_frame_count = 0;
        p_screen_frame_rate = 0;
        p_backdrop_color = D3DCOLOR_XRGB(0, 0, 0);
        p_window_handle = 0;
        p_pause_mode = false;
        p_version_major = VERSION_MAJOR;
        p_version_minor = VERSION_MINOR;
        p_revision = REVISION;
        p_command_line_params = "";

        //null render target variables
        p_main_surface = 0;
        p_main_depth_stencil_surface = 0;

        //window handle must be set later for directX
        p_window_handle = 0;
    }

    Engine::~Engine()
    {
        delete p_input;
        if(p_device) p_device->Release();
        if(p_d3d) p_d3d->Release();
    }

    std::string Engine::get_version_text()
    {
        std::ostringstream s;
        s << "Octane Engine v" << p_version_major << "." << p_version_minor << "." << p_revision;
        return s.str();
    }

    void Engine::message(std::string message, std::string title)
    {
        MessageBox(0, message.c_str(), title.c_str(), 0);
    }

    void Engine::set_screen(int w, int h, int d, bool full)
    {
        set_screen_width(w);
        set_screen_height(h);
        set_color_depth(d);
        set_full_screen(full);
    }

    bool Engine::init(HINSTANCE h_instance, int width, int height, int colordepth, bool fullscreen)
    {
        //get window caption string from engine
        string title;
        title = g_engine->get_app_title();

        //set window dimensions
        RECT window_rect;
        window_rect.left = 0;
        window_rect.right = g_engine->get_screen_width();
        window_rect.top = 0;
        window_rect.bottom = g_engine->get_screen_height();

        //create the window class structure
        WNDCLASSEX wc;
        memset(&wc, 0, sizeof(WNDCLASSEX));
        wc.cbSize        = sizeof(WNDCLASSEX);
        wc.style         = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc   = (WNDPROC)WndProc;
        wc.hInstance     = h_instance;
        wc.lpszClassName = title.c_str();
        wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
        wc.cbClsExtra    = 0;
        wc.cbWndExtra    = 0;
        wc.hIcon         = 0;
        wc.hIconSm       = 0;
        wc.hbrBackground = 0;
        wc.lpszMenuName  = 0;

        //set up the window whit the wndclassex info
        RegisterClassEx(&wc);

        //set up the screen in windowed or full screen mode?
        DWORD dwStyle, dwExStyle;
        if(g_engine->get_full_screen())
        {
            DEVMODE dm;
            memset(&dm, 0, sizeof(dm));
            dm.dmSize = sizeof(dm);
            dm.dmPelsWidth = g_engine->get_screen_width();
            dm.dmPelsHeight = g_engine->get_screen_height();
            dm.dmBitsPerPel = g_engine->get_color_depth();
            dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

            if(ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
            {
                debug << "Display change failed" << endl;
                g_engine->set_full_screen(false);
            }
            dwStyle = WS_POPUP;
            dwExStyle = WS_EX_APPWINDOW;
        }
        else
        {
            dwStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
            dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
        }

        //adjust window to true requested size
        AdjustWindowRectEx(&window_rect, dwStyle, FALSE, dwExStyle);

        //create the program window
        int wwidth = window_rect.right - window_rect.left;
        int wheight = window_rect.bottom - window_rect.top;

        debug << "Screen size: " << width << ", " << height << endl;
        debug << "Creating program window" << endl;

        HWND hwnd = CreateWindowEx(0,
                title.c_str(), //window class
                title.c_str(), //title bar
                dwStyle |
                WS_CLIPCHILDREN |
                WS_CLIPSIBLINGS, //window styles
                0, 0, //x, y coordinate
                wwidth, //width of the window
                wheight, //height of the window
                0, //parent window
                0, //menu
                h_instance, //application instance
                0); //window parameters

        //was there am error creating the window?
        if(!hwnd)
        {
            debug << "Error creating program window" << endl;
            return 0;
        }

        //display the window
        ShowWindow(hwnd, SW_SHOW);
        UpdateWindow(hwnd);

        //save window handle
        g_engine->set_window_handle(hwnd);

        debug << "Creating Direct3D object" << endl;

        //initialize Direct3D
        p_d3d = Direct3DCreate9(D3D_SDK_VERSION);
        if(p_d3d == NULL)
        {
            return 0;
        }

        //get system destop color depth
        D3DDISPLAYMODE dm;
        p_d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dm);

        //set configuration option for Direct3D
        D3DPRESENT_PARAMETERS d3dpp;
        ZeroMemory(&d3dpp, sizeof(d3dpp));
        d3dpp.Windowed               = (!fullscreen);
        d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD;
        d3dpp.EnableAutoDepthStencil = 1;
        d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
        d3dpp.Flags                  = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
        d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_IMMEDIATE;
        d3dpp.BackBufferFormat       = dm.Format;
        d3dpp.BackBufferCount        = 1;
        d3dpp.BackBufferWidth        = width;
        d3dpp.BackBufferHeight       = height;
        d3dpp.hDeviceWindow          = p_window_handle;
        d3dpp.MultiSampleType        = D3DMULTISAMPLE_NONE;

        debug << "Creating Direct3D device" << endl;
        
        //create Direct3D device (hardware T&L)
        p_d3d->CreateDevice(
                D3DADAPTER_DEFAULT,
                D3DDEVTYPE_HAL,
                p_window_handle,
                D3DCREATE_HARDWARE_VERTEXPROCESSING,
                &d3dpp,
                &p_device);

        //if hardware T&L failed try software
        if(p_device == NULL)
        {
            debug << "Hardware vertex option failed! Trying software..." << endl;
            p_d3d->CreateDevice(
                D3DADAPTER_DEFAULT,
                D3DDEVTYPE_HAL,
                p_window_handle,
                D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                &d3dpp,
                &p_device);
            if(p_device == NULL)
            {
                debug << "Software vertex option failed; shutting down." << endl;
                return 0;
            }
            else
            {
                debug << "Software vertex processing" << endl;
            }
        }
        else
        {
            debug << "Hardware vertex processing" << endl;
        }

        debug << "Creating 2D renderer" << endl;
        
        //initialize 2D renderer
        HRESULT result = D3DXCreateSprite(p_device, &p_sprite_obj);
        if(result != D3D_OK)
        {
            debug << "D3DXCreateSprite failed" << endl;
            return 0;
        }

        //initialize directinput
        debug << "Init input system" << endl;
        p_input = new Input(get_window_handle());

        debug << "Calling game_init(" << get_window_handle() << ")" << endl;

        //call game initialization extern function
        if(!game_init(get_window_handle())) return 0;
        debug << "Engine init succeeded" << endl;
        return 1;
    }

    /**
    Reset 3D transforms by setting the identity matrix
    **/
    void Engine::set_identity()
    {
        D3DXMATRIX identity;
        D3DXMatrixIdentity(&identity);
        g_engine->get_device()->SetTransform(D3DTS_WORLD, &identity);
    }

    /**
    Reset sprite transforms by setting the identity matrix
    **/
    void Engine::set_sprite_identity()
    {
        D3DXMATRIX identity;
        D3DXMatrixIdentity(&identity);
        g_engine->get_sprite_obj()->SetTransform(&identity);
    }

    /**
    Saving and restoring the renderer target is used when rendering to a texture 
    **/
    void Engine::save_primary_render_target()
    {
        //save primary rendering & depth stencil surface
        p_device->GetRenderTarget(0, &p_main_surface);
        p_device->GetDepthStencilSurface(&p_main_depth_stencil_surface);
    }
    void Engine::restor_primary_render_target()
    {
        //restore normal render traget
        p_device->SetRenderTarget(0, p_main_surface);
        p_device->SetDepthStencilSurface(p_main_depth_stencil_surface);
    }

    void Engine::clear_scene(D3DCOLOR color)
    {
        p_device->Clear(0, NULL,
                D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
                color, 1.0f, 0);
    }

    void Engine::update(float delta_time)
    {
        static float accum_time = 0;

        //calculate core framerate
        p_core_frame_count++;
        if(p_core_timer.stopwatch(1000))
        {
            p_core_frame_rate = p_core_frame_count;
            p_core_frame_count = 0;
        }

        //fast update
        game_update(delta_time);

        //60fps = ~16ms per frame
        if(!timed_update.stopwatch(16))
        {
            //free the CPU for 1 ms
            timed_update.rest(1);
        }
        else
        {
            //calculate real framerate
            p_screen_frame_count++;
            if(p_screen_timer.stopwatch(1000))
            {
                p_screen_frame_rate = p_screen_frame_count;
                p_screen_frame_count = 0;
            }

            //update input devices
            p_input->update();
            update_keyboard();
            update_mouse();

            //begin rendering
            if(p_device->BeginScene() == D3D_OK)
            {
                g_engine->clear_scene(p_backdrop_color);

                game_render3d();

                //2d rendering
                p_sprite_obj->Begin(D3DXSPRITE_ALPHABLEND);

                game_render2d();

                p_sprite_obj->End();

                p_device->EndScene();
                p_device->Present(0, 0, 0, 0);
            }
        }
    }

    void Engine::update_mouse()
    {
        static int old_pos_x = 0;
        static int old_pos_y = 0;

        //check mouse buttons
        for(int n = 0; n < 4; n++)
        {
            if(p_input->get_mouse_button(n))
            {
                //launch event
                raise_event(new MouseClickEvent(n));
            }
        }

        //check mouse position
        int pos_x = p_input->get_mouse_pos_x();
        int pos_y = p_input->get_mouse_pos_y();
        if(pos_x != old_pos_x || pos_y != old_pos_y)
        {
            old_pos_x = p_input->get_mouse_pos_x();
            old_pos_y = p_input->get_mouse_pos_y();
            //launch event
            raise_event(new MouseMoveEvent(pos_x, pos_y));
        }

        //check mouse motion
        int delta_x = p_input->get_mouse_delta_x();
        int delta_y = p_input->get_mouse_delta_y();
        if(delta_x != 0 || delta_y != 0)
        {
            //launch event
            raise_event(new MouseMotionEvent(delta_x, delta_y));
        }

        //check mouse wheel
        int wheel = p_input->get_mouse_wheel();
        if(wheel != 0)
        {
            //launch event
            raise_event(new MouseWheelEvent(wheel));
        }
    }

    void Engine::update_keyboard()
    {
        static char old_keys[256];

        for(int n = 0; n < 255; n++)
        {
            //check for key press
            if(p_input->get_key_state(n) & 0x80)
            {
                old_keys[n] = p_input->get_key_state(n);
                //launch event
                raise_event(new KeyPressEvent(n));
            }
            //check for release
            else if(old_keys[n] & 0x80)
            {
                old_keys[n] = p_input->get_key_state(n);
                //launch event
                raise_event(new KeyReleaseEvent(n));
            }
        }
    }

    void Engine::shut_down()
    {
        PostQuitMessage(0);
    }

    void Engine::raise_event(IEvent* e)
    {
        game_event(e);
        delete e;
    }
    
}; //namespace



 
