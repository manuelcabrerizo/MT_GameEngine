#pragma once

#include "engine.h"

namespace Octane
{
    class Mesh
    {
    private:
        LPD3DXMESH mesh;
        D3DMATERIAL9* materials;
        DWORD material_count;
        LPDIRECT3DTEXTURE9* textures;

        Vector3 position;
        Vector3 rotation;
        Vector3 scale;

        Matrix mat_world;
        Matrix mat_translate;
        Matrix mat_rotate;
        Matrix mat_scale;

        Effect* p_effect;
    public:
        Mesh();
        virtual ~Mesh();

        bool load(char* filename, bool compute_normals = false);
        bool find_file(std::string* filename);
        bool does_file_exist(std::string& filename);
        void split_path(std::string& input_path, std::string* path_only, std::string* filename_only);

        void update(float delta_time);
        void render();
        void render(Effect* effect, std::string fx_texture_param = "Texture");
        void set_effect(Effect* effect) {p_effect = effect;}

        Matrix get_matrix() {return mat_world;}
        void set_matrix(Matrix matrix) {mat_world = matrix;}
        void set_matrix(D3DXMATRIX matrix) {mat_world = (Matrix)matrix;}
        LPD3DXMESH get_mesh() {return mesh;}
        virtual int get_face_count();
        virtual int get_vertex_count();

        void create_torus(float inner_radius = 0.5f, float outer_radius = 1.0f,
                int sides = 20, int rings = 20);
        void create_cylinder(float radius1, float radius2, float length,
                int slices, int stacks);
        void create_sphere(double radius = 0.1f, int slices = 10, int stacks = 10);
        void create_cube(double width = 1.0f, double height = 1.0f,
                double depth = 1.0f);
        void create_teapot();

        void transform();
        void rotate(Vector3 rot);
        void rotate(double x, double y, double z);
        void set_position(Vector3 pos) {position = pos;}
        void set_position(double x, double y, double z);
        Vector3 get_position() {return position;}
        void set_rotation(Vector3 rot) {rotation = rot;}
        void set_rotation(double x, double y, double z);
        Vector3 get_rotation() {return rotation;}
        void set_scale(Vector3 value) {scale = value;}
        void set_scale(double x, double y, double z);
        void set_scale(double value);
        Vector3 get_scale() {return scale;}
    };
};
