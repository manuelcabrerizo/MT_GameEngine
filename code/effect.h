#pragma once

#include "engine.h"

namespace Octane
{
    class Effect
    {
    private:
        LPD3DXEFFECT p_effect;
    public:
        Effect();
        ~Effect();
        LPD3DXEFFECT get_object() {return p_effect;}
        bool load(std::string filename);
        void set_technique(std::string technique);
        void set_view_matrix(D3DXMATRIX matrix, std::string fx_view_param = "View");
        void set_projection_matrix(D3DXMATRIX matrix, std::string fx_projection_param = "Projection");
        void set_world_matrix(D3DXMATRIX matrix, std::string fx_world_param = "World");

        void set_param(std::string name, D3DXMATRIX matrix);
        void set_param(std::string name, LPDIRECT3DTEXTURE9 texture);
        void set_param(std::string name, LPDIRECT3DCUBETEXTURE9 cube_texture);
        void set_param(std::string name, D3DXVECTOR4 vector);
        void set_param(std::string name, D3DXVECTOR3 vector);
        void set_param(std::string name, Vector3 vector);
        void set_param(std::string name, float f);

        bool begin();
        void end();
    };
};
