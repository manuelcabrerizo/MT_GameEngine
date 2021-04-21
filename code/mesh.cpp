#include "engine.h"

namespace Octane
{
    Mesh::Mesh()
    {
        mesh = 0;
        materials = 0;
        material_count = 0;
        textures = 0;
        position = Vector3(0.0f, 0.0f, 0.0f);
        rotation = Vector3(0.0f, 0.0f, 0.0f);
        scale = Vector3(1.0f, 1.0f, 1.0f);
    }

    Mesh::~Mesh()
    {
        if(materials != NULL) delete[] materials;
        
        //remove textures from memory
        if(textures != NULL)
        {
            for(DWORD i = 0; i < material_count; i++)
            {
                if(textures[i] != NULL)
                {
                    textures[i]->Release();
                }
            }
            delete[] textures;
        }

        if(mesh != NULL) mesh->Release();
    }

    int Mesh::get_face_count()
    {
        return mesh->GetNumFaces();
    }

    int Mesh::get_vertex_count()
    {
        return mesh->GetNumVertices();
    }

    void Mesh::create_torus(float inner_radius, float outer_radius, int sides, int rings)
    {
        D3DXCreateTorus(g_engine->get_device(), inner_radius, outer_radius,
                sides, rings, &mesh, NULL);
    }

    void Mesh::create_cylinder(float radius1, float radius2, float length, int slices, int stacks)
    {
        D3DXCreateCylinder(g_engine->get_device(), radius1, radius2, length, slices, stacks, &mesh, NULL);
    }

    void Mesh::create_cube(double width, double height, double depth)
    {
        D3DXCreateBox(g_engine->get_device(), (float)width, (float)height,
                (float)depth, &mesh, NULL);
    }

    void Mesh::create_teapot()
    {
        D3DXCreateTeapot(g_engine->get_device(), &mesh, NULL);
    }

    void Mesh::split_path(std::string& input_path, std::string* path_only, std::string* filename_only)
    {
        std::string full_path(input_path);
        replace(full_path.begin(), full_path.end(), '\\', '/');
        std::string::size_type last_slash_pos = full_path.find_last_of('/');

        //check for there begin no path element in the input
        if(last_slash_pos == std::string::npos)
        {
            *path_only="";
            *filename_only = full_path;
        }
        else
        {
            if(path_only)
            {
                *path_only = full_path.substr(0, last_slash_pos);
            }
            if(filename_only)
            {
                *filename_only = full_path.substr(
                        last_slash_pos + 1,
                        full_path.size() - last_slash_pos - 1);
            }
        }

    }

    bool Mesh::does_file_exist(std::string& filename)
    {
        return (_access(filename.c_str(), 0) != -1);
    }

    bool Mesh::find_file(std::string* filename)
    {
        if(!filename) return false;

        std::string path_only;
        std::string filename_only;

        split_path(*filename, &path_only, &filename_only);

        //is file found in current folder, without the path?
        if(does_file_exist(filename_only))
        {
            *filename = filename_only;
            return true;
        }
        //not found
        return false;
    }

    bool Mesh::load(char* filename, bool compute_normals)
    {
        HRESULT result;
        LPD3DXBUFFER matbuffer;
        LPD3DXMATERIAL d3dx_materials;

        //load mesh from the specified file
        result = D3DXLoadMeshFromX(
                filename,                   //filename
                D3DXMESH_SYSTEMMEM,         //mesh option
                g_engine->get_device(),     //deriect3d device
                NULL,                       //adjacency buffer
                &matbuffer,                 //material buffer
                NULL,                       //special effects
                &material_count,            //number of materials
                &mesh);                     //resulting mesh

        if(result != D3D_OK)
        {
            return false;
        }

        //extract material properties and texture names from material buffer
        d3dx_materials = (LPD3DXMATERIAL)matbuffer->GetBufferPointer();
        materials = new D3DMATERIAL9[material_count];
        textures = new LPDIRECT3DTEXTURE9[material_count];

        //create the materials and texture
        for(DWORD i = 0; i < material_count; i++)
        {
            //grab the material
            materials[i] = d3dx_materials[i].MatD3D;

            //load texture(s)
            textures[i] = NULL;
            if(d3dx_materials[i].pTextureFilename != NULL)
            {
                std::string filename = d3dx_materials[i].pTextureFilename;
                if(find_file(&filename))
                {
                    //load texture file specified in .x file
                    result = D3DXCreateTextureFromFile(g_engine->get_device(), filename.c_str(), &textures[i]);
                    if(result != D3D_OK)
                    {
                        return false;
                    }
                    if(textures[i]->GetType() != D3DRTYPE_TEXTURE)
                    {
                        return false;
                    }
                }
            }
        }

        //done using material buffer
        matbuffer->Release();

        if(compute_normals)
        {
            HRESULT res = D3DXComputeNormals(mesh, NULL);
            if(res != S_OK)
            {
                debug << "Mesh::CreateSphere: Error computing normals\n";
            }
        }
        return true;
    }

    void Mesh::update(float delta_time)
    {
        transform();
    }

    void Mesh::render()
    {
        render(p_effect, "Texture"); 
    }

    void Mesh::render(Effect* effect, std::string fx_texture_param)
    {
        p_effect = effect;
        p_effect->set_world_matrix(mat_world);
        p_effect->begin();
        
        if(material_count == 0)
        {
            mesh->DrawSubset(0);
        }
        else
        {
            //draw each mesh subset
            for(DWORD i = 0; i < material_count; i++)
            {
                //set the texture used by this face
                if(textures[i])
                {
                    p_effect->set_param(fx_texture_param, (textures[i]));
                }
                //draw the mesh subset
                mesh->DrawSubset(i);
            }
        }

        p_effect->end(); 
    }

    void Mesh::transform()
    {
        //set rotation matrix
        double x = D3DXToRadian(rotation.x);
        double y = D3DXToRadian(rotation.y); 
        double z = D3DXToRadian(rotation.z);
        D3DXMatrixRotationYawPitchRoll(&mat_rotate, (float)x, (float)y, (float)z);

        //set scaling matrix
        D3DXMatrixScaling(&mat_scale, (float)scale.x, (float)scale.y, (float)scale.z);

        //set translation matrix
        D3DXMatrixTranslation(&mat_translate, (float)position.x, (float)position.y, (float)position.z);

        //transform the mesh
        mat_world = mat_rotate * mat_scale * mat_translate;
    }

    void Mesh::set_position(double x, double y, double z)
    {
        position = Vector3((float)x, (float)y, (float)z);
    }

    void Mesh::rotate(Vector3 rot)
    {   
        rotate(rot.x, rot.y, rot.z);
    }

    void Mesh::rotate(double x, double y, double z)
    {
        rotation.x += (float)x;
        rotation.y += (float)y;
        rotation.z += (float)z;
    }

    void Mesh::set_rotation(double x, double y, double z)
    {
        rotation = Vector3((float)x, (float)y, (float)z);
    }

    void Mesh::set_scale(double x, double y, double z)
    {
        scale = Vector3((float)x, (float)y, (float)z);
    }

    void Mesh::set_scale(double value)
    {
        scale.x = scale.y = scale.z = value; 
    }

};
