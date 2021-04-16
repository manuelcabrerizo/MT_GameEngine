//#include "stdafx.h"
#include "engine.h"

using namespace std;

// declare global engine object
std::auto_ptr<Octane::Engine> g_engine(new Octane::Engine);

/**
WndProc - message handler (req'd when user closes window with "X" button)
**/
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    if(msg == WM_DESTROY)
        PostQuitMessage(0);
    return DefWindowProc(hwnd, msg, w_param, l_param);
}

/**
WinMain - entry point of the program 
**/
int WINAPI WinMain(HINSTANCE h_instance, HINSTANCE h_prev_instance, LPSTR cmd_line, int cmd_show)
{
    debug << "WinMain running" << endl;
    srand((unsigned int)time(0));

    //check command line
    debug << "Checking parameters" << endl;
    if(strlen(cmd_line) > 0)
    {
        g_engine->set_command_line_params(cmd_line);
        debug << "Params: " << g_engine->get_command_line_params() << endl;
    }

    //let main program set screen dimensions
    debug << "Calling game_preload" << endl;
    if(!game_preload())
    {
        debug << "Error in game_preload" << endl;
        return 0;
    }

    //initialize the engine
    debug << "Initializing engine" << endl;
    bool res = g_engine->init(
            h_instance,
            g_engine->get_screen_width(),  //screen width
            g_engine->get_screen_height(), //screen height
            g_engine->get_color_depth(),   //screen depth
            g_engine->get_full_screen());  //screen mode
    if(!res)
    {
        debug << "Error initializing the engine" << endl;
        return 0;
    }

    MSG msg;
    memset(&msg, 0, sizeof(MSG));
    Octane::Timer timer;
    double start_time = timer.get_elapsed();

    debug << "Core timer started: " << timer.get_elapsed() << endl;
    debug << "Entering while loop" << endl;

    //main message loop
    while(msg.message != WM_QUIT)
    {
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            double t = timer.get_elapsed();
            float delta_time = (t - start_time) * 0.001f;
            g_engine->update(delta_time);
            start_time = t;
        }
    }

    debug << "Exiting while loop" << endl;
    debug << "Total run time: " << timer.get_elapsed() << endl;
    debug << "Freeing game resources" << endl;
    game_end();

    debug << "Shutting down engine" << endl;
    ShowCursor(true);
    return 1;
}
