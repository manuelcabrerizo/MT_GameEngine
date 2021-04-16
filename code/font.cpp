//#include "stdafx.h"
#include "engine.h"

using namespace std;

namespace Octane
{
    Font::Font(string name, int size)
    {
        font_obj = NULL;
        D3DXFONT_DESC font_desc = {
            size,                      //height
            0,                         //width
            0,                         //weight
            0,                         //miplevels
            false,                     //italic
            DEFAULT_CHARSET,           //charset
            OUT_TT_PRECIS,             //output precision
            CLIP_DEFAULT_PRECIS,       //quality
            DEFAULT_PITCH,             //pitch and family
            ""
        };
        strcpy(font_desc.FaceName, name.c_str());
        
        D3DXCreateFontIndirect(g_engine->get_device(), &font_desc, &font_obj);
    }

    Font::~Font()
    {
        font_obj->Release();
    }

    void Font::print(int x, int y, std::string text, D3DCOLOR color)
    {
        //figure out the text boundary
        RECT rect = {x, y, 0, 0};
        font_obj->DrawText(NULL, text.c_str(), text.length(),
                &rect, DT_CALCRECT, color);

        //print the text
        font_obj->DrawText(g_engine->get_sprite_obj(), text.c_str(),
                text.length(), &rect, DT_LEFT, color);
    }

    int Font::get_text_width(string text)
    {
        RECT rect = {0, 0, 0, 0};
        font_obj->DrawText(NULL, text.c_str(), text.length(), &rect,
                DT_CALCRECT, 0xffffffff);
        return rect.right;
    }

    int Font::get_text_height(string text)
    {
        RECT rect = {0, 0, 0, 0};
        font_obj->DrawText(NULL, text.c_str(), text.length(), &rect,
                DT_CALCRECT, 0xffffffff);
        return rect.bottom;
    }

};
