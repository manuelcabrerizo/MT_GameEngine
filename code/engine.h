#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <timeapi.h>
#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <io.h>
#include <algorithm>

//DirectX headers
#define DIRECTINPUT_VERSION 0x0800
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

//engine class header
#include "timer.h"
#include "input.h"
#include "event.h"
#include "font.h"
#include "logfile.h"
#include "vector.h"
#include "matrix.h"
#include "math.h"
#include "camera.h"
#include "effect.h"
#include "color.h"
#include "mesh.h"


//required libraries
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xinput.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"gdi32.lib")

#define VERSION_MAJOR 1
#define VERSION_MINOR 0
#define REVISION 0

//end-user functions
extern bool game_preload();
extern bool game_init(HWND hwnd);
extern void game_update(float delta_time);
extern void game_render3d();
extern void game_render2d();
extern void game_event(Octane::IEvent* e);
extern void game_end();

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);

namespace Octane
{
    //helper function to convert values to string format
    template<class T>std::string static to_string(const T & t, int places = 2)
    {
        std::ostringstream oss;
        oss.precision(places);
        oss.setf(std::ios_base::fixed);
        oss << t;
        return oss.str();
    }

    class Engine
    {
    private:
        std::string p_command_line_params;
        int p_version_major, p_version_minor, p_revision;
        HWND p_window_handle;
        LPDIRECT3D9 p_d3d;
        LPDIRECT3DDEVICE9 p_device;
        LPD3DXSPRITE p_sprite_obj;
        std::string p_apptitle;
        bool p_fullscreen;
        int p_screen_width;
        int p_screen_height;
        int p_color_depth;
        bool p_pause_mode;
        Timer p_core_timer;
        long p_core_frame_count;
        long p_core_frame_rate;
        Timer p_screen_timer;
        long p_screen_frame_count;
        long p_screen_frame_rate;
        Timer timed_update;
        D3DCOLOR p_backdrop_color;

        //primary surface pointers used when restoring render target
        LPDIRECT3DSURFACE9 p_main_surface;
        LPDIRECT3DSURFACE9 p_main_depth_stencil_surface; 

        Input* p_input;
        void update_keyboard();
        void update_mouse();
    public:
        Engine();
        virtual ~Engine();
        bool init(HINSTANCE h_instance, int width, int height, int colordepth, bool fullscreen);
        void update(float delta_time);
        void message(std::string message, std::string title = "Engine");
        void fatal_error(std::string message, std::string = "FATAL ERROR");
        void shut_down();

        void clear_scene(D3DCOLOR color);
        void set_identity();
        void set_sprite_identity();
        int release();
        void save_primary_render_target();
        void restor_primary_render_target();

        //accessor/mutator functions expose the private variables
        bool is_paused() {return p_pause_mode;}
        void set_paused(bool value) {p_pause_mode = value;}

        LPDIRECT3D9 get_object() {return p_d3d;}
        LPDIRECT3DDEVICE9 get_device() {return p_device;}
        LPD3DXSPRITE get_sprite_obj() {return p_sprite_obj;}

        void set_window_handle(HWND hwnd) {p_window_handle = hwnd;}
        HWND get_window_handle() {return p_window_handle;}

        std::string get_app_title() {return p_apptitle;}
        void set_app_title(std::string value) {p_apptitle = value;}

        int get_version_major() {return p_version_major;}
        int get_version_minor() {return p_version_minor;}
        int get_revision() {return p_revision;}
        std::string get_version_text();

        long get_core_frame_rate() {return p_core_frame_rate;}
        long get_screen_frame_rate() {return p_screen_frame_rate;}

        void set_screen(int w, int h, int d, bool full);
        int get_screen_width() {return p_screen_width;}
        void set_screen_width(int value) {p_screen_width = value;}
        int get_screen_height() {return p_screen_height;}
        void set_screen_height(int value) {p_screen_height = value;}
        int get_color_depth() {return p_color_depth;}
        void set_color_depth(int value) {p_color_depth = value;}
        bool get_full_screen() {return p_fullscreen;}
        void set_full_screen(bool value) {p_fullscreen = value;}

        D3DCOLOR get_backdrop_color() {return p_backdrop_color;}
        void set_backdrop_color(Color value) {p_backdrop_color = value.to_d3d_color();}

        //command line params
        std::string get_command_line_params() {return p_command_line_params;}
        void set_command_line_params(std::string value) {p_command_line_params = value;}

        //event system
        void raise_event(IEvent* e);
    };
};

//define the global engine object (visible everywhere!)
extern std::auto_ptr<Octane::Engine> g_engine;
