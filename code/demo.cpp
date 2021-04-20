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

Vector3 light_vector;
Color light_color;
float light_angle = 0;
float light_power = 0.1f;
float object_angle = 0;
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
    Color back_color(0, 0, 30, 255);
    g_engine->set_backdrop_color(back_color);

    //create a camera
    camera = new Camera();
    camera->set_position(0.0, 0.0, 5.0);
    camera->set_target(0.0, 0.0, 0.0);

    //load the ambient.fx effect
    effect = new Effect();
    if(!effect->load("./code/ambient.fx"))
    {
        MessageBox(hwnd, "Error loading ambient.fx", "Error", 0);
        return false;
    }

    mat_world.set_identity();

    light_color.set(255, 0, 0, 0);

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
    effect->set_technique("DirectionalLight");
    effect->set_view_matrix(camera->get_view_matrix(), "View");
    effect->set_projection_matrix(camera->get_proj_matrix(), "Projection");

    //draw the cube
    {
        mat_world.rotate_x(object_angle);
        effect->begin();
        effect->set_world_matrix((D3DXMATRIX)mat_world, "World");

        //calculate combined inverse transpose matrix
        D3DXMATRIX inverse, wit;
        D3DXMatrixInverse(&inverse, 0, &mat_world);
        D3DXMatrixTranspose(&wit, &inverse);
        effect->set_param("WorldInverseTranspose", wit);

        //move the light source
        light_vector.x = cosf(light_angle) * 10.0f;
        light_vector.y = 0.0f;
        light_vector.z = sinf(light_angle) * 10.0f;
        effect->set_param("LightVector", light_vector);

        //set the light intensity
        light_power = Math::limit(light_power, 0.0, 1.0);
        effect->set_param("LightPower", light_power);

        //set the light color
        light_color.r = Math::wrap_value(light_color.r, 0.0, 1.0);
        light_color.g = Math::wrap_value(light_color.g, 0.0, 1.0);
        light_color.b = Math::wrap_value(light_color.b, 0.0, 1.0);
        light_color.a = Math::wrap_value(light_color.a, 0.0, 1.0);
        effect->set_param("LightColor", light_color.to_d3d_vec4());

        //choose which mesh to render here
        //torus->DrawSubset(0);
        //cube->DrawSubset(0);
        //sphere->DrawSubset(0);
        teapot->DrawSubset(0);
        //cylinder->DrawSubset(0);
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

    Color font_color(255, 255, 0, 255);
    font->print(0, 0, out.str(), font_color);
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
