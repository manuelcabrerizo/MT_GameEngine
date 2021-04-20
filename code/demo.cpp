#include "engine.h"

using namespace std;
using namespace Octane;

LPD3DXMESH torus;
LPD3DXMESH sphere;
LPD3DXMESH cube;
LPD3DXMESH teapot;
LPD3DXMESH cylinder;
Matrix mat_world;
Font* font = NULL;
Camera* camera = NULL;
Effect* effect = NULL;
float delta = 0;

//these function are not used at this time


void game_end() 
{
    if(font) delete font;
    if(effect) delete effect;
    if(camera) delete camera;
    torus->Release();
    teapot->Release();
    cube->Release();
    sphere->Release();
    cylinder->Release();
}

bool game_preload()
{
    g_engine->set_app_title("Ambient Wireframe Shader Demo");
    g_engine->set_screen(800, 600, 32, false);
    return true;
}

bool game_init(HWND hwnd)
{
    font = new Font("Arial Bold", 18);
    if(!font)
    {
        debug << "Error creating font" << endl;
        return false;
    }

    g_engine->set_backdrop_color(D3DCOLOR_XRGB(0, 30, 30));

    //create a camera
    camera = new Camera();
    camera->set_position(0.0, 0.0, 10.0);
    camera->set_target(0.0, 0.0, 0.0);

    //load the ambient.fx effect
    effect = new Effect();
    if(!effect->load("./code/ambient.fx"))
    {
        MessageBox(hwnd, "Error loading ambient.fx", "Error", 0);
        return false;
    }

    mat_world.set_identity();

    //crate stock meshes
    D3DXCreateTorus(g_engine->get_device(), 2.0f, 4.0f, 20, 20, &torus, NULL);
    D3DXCreateTeapot(g_engine->get_device(), &teapot, NULL);
    D3DXCreateSphere(g_engine->get_device(), 2.0f, 10, 10, &sphere, NULL);
    D3DXCreateBox(g_engine->get_device(), 2.0f, 2.0f, 2.0f, &cube, NULL);
    D3DXCreateCylinder(g_engine->get_device(), 2.0f, 2.0f, 3.0f, 10, 10, &cylinder, NULL);

    return true;
}

void game_render3d()
{
    effect->set_technique("Ambient");
    effect->set_view_matrix(camera->get_view_matrix(), "View");
    effect->set_projection_matrix(camera->get_proj_matrix(), "Projection");

    //draw the cube
    {
        static float rot = 0;
        rot += 0.01f;
        mat_world.rotate_x(rot);
        effect->begin();
        effect->set_world_matrix((D3DXMATRIX)mat_world, "World");

        //choose which mesh to render here
        //torus->DrawSubset(0);
        //cube->DrawSubset(0);
        //sphere->DrawSubset(0);
        //teapot->DrawSubset(0);
        cylinder->DrawSubset(0);
        effect->end();
    }
}

void game_update(float delta_time)
{
    delta = delta_time;

    camera->update();

    //move the torus mesh in a circular pattern
    static float x = 0.0f;
    static float y = 0.0f;
    static float z = 0.0f;
    static float angle = 0.0f;
}

void game_render2d()
{
    ostringstream out;
    out.setf(ios::fixed);
    out << setprecision(4);
    out << "Delta Time = " << delta << endl;
    out << "Update = " << g_engine->get_core_frame_rate() << "fps" << endl;
    out << "Draw = " << g_engine->get_screen_frame_rate() << "fps";

    font->print(0, 0, out.str());
}

void game_event(IEvent* e)
{
    switch(e->get_id())
    {
        case EVENT_KEYPRESS:
        {
            KeyPressEvent* kpe = (KeyPressEvent*)e;
            if(kpe->keycode == DIK_ESCAPE)
            {
                g_engine->shut_down();
            }
        }break;

        case EVENT_MOUSEMOTION:
        {
            MouseMotionEvent* mme = (MouseMotionEvent*)e;
            camera->look(mme->delta_x/100.0f, mme->delta_y/100.0f, 0);
        }break;

        case EVENT_MOUSEWHEEL:
        {
            MouseWheelEvent* mwe = (MouseWheelEvent*)e;
            camera->move(0, 0, (float)(-mwe->wheel/200.0f));
        }break;
    }
}
