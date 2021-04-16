#pragma once

#include "engine.h"

namespace Octane
{
    class Font
    {
    private:
        LPD3DXFONT font_obj;
    public:
        Font(std::string name, int size);
        ~Font();
        void print(int x, int y, std::string text, D3DCOLOR color = 0xffffffff);
        int get_text_width(std::string text);
        int get_text_height(std::string text);
    }; 
};
