#include "engine.h"

namespace Octane
{
    Color::Color()
    {
        r = g = b = a = 1.0f;
    }

    Color::Color(const Color& color)
    {
        *this = color;
    }

    Color::Color(int R, int G, int B, int A)
    {
        set(R, G, B, A);
    }

    Color::Color(float R, float G, float B, float A)
    {
        set(R, G, B, A);
    }

    Color& Color::operator=(const Color& c)
    {
        set(c.r, c.g, c.b, c.a);
        return *this;
    }

    void Color::set(int R, int G, int B, int A)
    {
        r = (float)R/256.0f;
        g = (float)G/256.0f;
        b = (float)B/256.0f;
        a = (float)A/256.0f;
    }

    void Color::set(float R, float G, float B, float A)
    {
        r = R;
        g = G;
        b = B;
        a = A;
    }

    //D3D compatibility
    D3DCOLOR Color::to_d3d_color()
    {
        D3DCOLOR color = D3DCOLOR_COLORVALUE(r, g, b, a);
        return color; 
    }

    //shader compatibility
    D3DXVECTOR4 Color::to_d3d_vec4()
    {
        D3DXVECTOR4 v4(r, g, b, a);
        return v4;
    }
};
