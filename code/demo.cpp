#include "engine.h"
#include "math.h"
using namespace std;
using namespace Octane;

Font* font = NULL;
float elapsed = 0.0f;
int keypresscode = 0;
int keyreleasecode = 0;
int mousebutton = 0;
int movex = 0, movey = 0;
int posx = 0, posy = 0;
int wheel = 0;
float delta = 0;

//these function are not used at this time
void game_render3d() {}

void game_end() 
{
    if(font) delete font;
}

bool game_preload()
{
    g_engine->set_app_title("First Engine Demo");
    g_engine->set_screen(800, 600, 32, false);
    return true;
}

bool game_init(HWND hwnd)
{
    debug << "Init Game Code" << endl;
    font = new Font("Arial Bold", 20);
    if(!font)
    {
        debug << "Error creating font" << endl;
        return false;
    }
    return true;
}

void game_update(float delta_time)
{
    delta = delta_time;
}

void game_render2d()
{
    ostringstream out;
    out.setf(ios::fixed);
    out << setprecision(2);
    out << "VECTORS" << endl;
    Vector3 A(5, 5, 1);
    out << "VECTOR A: " << A.get_x() << ", " << A.get_y() << ", " << A.get_z() << endl;
    Vector3 B(90, 80, 1);
    out << "VECTOR B: " << B.get_x() << ", " << B.get_y() << ", " << B.get_z() << endl;
    out << "DISTANCE" << endl;
    out << "distance A to B: " << Math::distance(A, B) << endl;
    out << "LENGTH" << endl;
    out << "length of A : " << Math::length(A) << endl;
    out << "length of B : " << Math::length(B) << endl;
    out << endl << "COPYING" << endl;
    A.move(5, 0, 0);
    out << "A moved: " << A.get_x() << ", " << A.get_y() << ", " << A.get_z() << endl;
    Vector3 C = A;
    out << "VECTOR B: " << C.get_x() << ", " << C.get_y() << ", " << C.get_z() << endl;
    out << endl << "DOT PRODUCT" << endl;
    out << "dot product A,B: " << Math::dot_product(A, B) << endl;
    out << endl << "CROSS PRODUCT" << endl;
    Vector3 D = Math::cross_product(A, B);
    out << "cross product A,B: " << D.get_x() << ", " << D.get_y() << ", " << D.get_z()  << endl;
    out << endl << "NORMAL" << endl;
    D = Math::normal(A);
    out << "normal A: " << D.get_x() << ", " << D.get_y() << ", " << D.get_z()  << endl;
    font->print(0, 0, out.str(), 0xffff00ff); 

    ostringstream os;
    os.imbue(std::locale("english-us"));
    os << "DELTA: " << Octane::to_string(delta, 4) << endl;
    os << "CORE FPS: " << g_engine->get_core_frame_rate() << endl;
    os << "SCREEN FPS: " << g_engine->get_screen_frame_rate() << endl;
    os << "KEY PRESS: " << keypresscode << endl;
    os << "KEY RELEASE: " << keyreleasecode << endl;
    os << "MOUSE MOVE: " << posx << "," << posy << endl;
    os << "MOUSE CLICK: " << mousebutton << endl;
    os << "MOUSE MOTION: " << movex << "," << movey << endl;
    os << "MOUSE WHEEL: " << wheel << endl;
    font->print(300, 0, os.str(), 0xff00ff00);
    mousebutton = 0;
    wheel = 0; 
}

void game_event(IEvent* e)
{
    switch(e->get_id())
    {
        case EVENT_KEYPRESS:
        {
            KeyPressEvent* kpe = (KeyPressEvent*)e;
            keypresscode = kpe->keycode;
            if(keypresscode == DIK_ESCAPE)
            {
                g_engine->shut_down();
            }
        }break;

        case EVENT_KEYRELEASE:
        {
            KeyReleaseEvent* kre = (KeyReleaseEvent*)e;
            keyreleasecode = kre->keycode;
        }break;

        case EVENT_MOUSEMOVE:
        {
            MouseMoveEvent* mme = (MouseMoveEvent*)e;
            posx = mme->pos_x;
            posy = mme->pos_y;
        }break;

        case EVENT_MOUSECLICK:
        {
            MouseClickEvent* mce = (MouseClickEvent*)e;
            mousebutton = mce->button + 1;
        }break;

        case EVENT_MOUSEMOTION:
        {
            MouseMotionEvent* mme = (MouseMotionEvent*)e;
            movex = mme->delta_x;
            movey = mme->delta_y;
        }break;

        case EVENT_MOUSEWHEEL:
        {
            MouseWheelEvent* mwe = (MouseWheelEvent*)e;
            wheel = mwe->wheel;
        }break;
    }
}
