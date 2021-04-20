#include "engine.h"
#include <d3d9.h>
#include <d3dx9.h>

namespace Octane
{
    Effect::Effect()
    {
        p_effect = NULL; 
    }

    Effect::~Effect()
    {
        if(p_effect) p_effect->Release();
    }

    bool Effect::load(std::string filename)
    {
        ID3DXBuffer* errors = 0;
        D3DXCreateEffectFromFile(g_engine->get_device(), filename.c_str(),
                0, 0, D3DXSHADER_DEBUG, 0, &p_effect, &errors);

        if(errors)
        {
            MessageBox(0, (char*)errors->GetBufferPointer(), 0, 0);
            return false;
        }
        return true;
    }

    void Effect::set_technique(std::string technique)
    {
        p_effect->SetTechnique(technique.c_str()); 
    }

    void Effect::set_view_matrix(D3DXMATRIX matrix, std::string fx_view_param)
    {
        p_effect->SetMatrix(fx_view_param.c_str(), &matrix);
    }

    void Effect::set_projection_matrix(D3DXMATRIX matrix, std::string fx_projection_param)
    {
        p_effect->SetMatrix(fx_projection_param.c_str(), &matrix);
    }

    void Effect::set_world_matrix(D3DXMATRIX matrix, std::string fx_world_param)
    { 
        p_effect->SetMatrix(fx_world_param.c_str(), &matrix);
    }

    void Effect::set_param(std::string name, D3DXMATRIX matrix)
    {
        p_effect->SetMatrix(name.c_str(), &matrix); 
    }

    void Effect::set_param(std::string name, LPDIRECT3DTEXTURE9 texture)
    {
        p_effect->SetTexture(name.c_str(), texture);
    }

    void Effect::set_param(std::string name, LPDIRECT3DCUBETEXTURE9 cube_texture)
    {
        p_effect->SetTexture(name.c_str(), cube_texture);
    }

    void Effect::set_param(std::string name, D3DXVECTOR4 vector)
    {
        p_effect->SetVector(name.c_str(), &vector);
    }

    void Effect::set_param(std::string name, D3DXVECTOR3 vector)
    {
        D3DXVECTOR4 v;
        v.x = vector.x;
        v.y = vector.y;
        v.z = vector.z;
        v.w = 0;

        p_effect->SetVector(name.c_str(), &v);
    }

    void Effect::set_param(std::string name, Vector3 vector)
    {
        D3DXVECTOR4 v;
        v.x = (float)vector.x;
        v.y = (float)vector.y;
        v.z = (float)vector.z;
        v.w = 0;

        p_effect->SetVector(name.c_str(), &v);

    }

    void Effect::set_param(std::string name, float f)
    {
        p_effect->SetFloat(name.c_str(), f);
    }

    bool Effect::begin()
    {
        if(!p_effect) return false;

        UINT passes;
        p_effect->Begin(&passes, 0);
        if(passes == 0) return false;
        p_effect->BeginPass(0);
        return true;
    }

    void Effect::end()
    {
        if(!p_effect) return;
        p_effect->EndPass();
        p_effect->End();
    } 
};
