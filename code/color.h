#pragma once

#include "engine.h"

namespace Octane
{
    class Color
    {
    public:
        float r, g, b, a;
        virtual ~Color() {}
        Color();
        Color(const Color& color);
        Color(int R, int G, int B, int A);
        Color(float R, float G, float B, float A);
        Color& operator=(const Color& c);

        void set(int R, int G, int B, int A);
        void set(float R, float G, float B, float A);

        //D3D compatibility
        D3DCOLOR to_d3d_color();
        //shader compatibility
        D3DXVECTOR4 to_d3d_vec4();
    };
};


