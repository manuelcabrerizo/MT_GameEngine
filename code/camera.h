#pragma once

#include "engine.h"

namespace Octane
{
    class Camera
    {
    private:
        Matrix matrix_proj;
        Matrix matrix_view;
        Matrix matrix_rot;
        D3DXVECTOR3 up_dir;

        Vector3 position;
        Vector3 rotation;
        Vector3 target;

        double near_range;
        double far_range;
        double aspect_ratio;
        double fov;
    public:
        Camera();
        ~Camera();
        void set_perspective(double fov, double aspect_ratio, double near_range, double far_range);
        Matrix get_proj_matrix() {return matrix_proj;}
        Matrix get_view_matrix() {return matrix_view;}

        //camera position helpers
        Vector3 get_position() {return position;}
        void set_position(double x, double y, double z);
        void set_position(Vector3 vector) {position = vector;}

        void set_rotation(double x, double y, double z);
        void set_rotation(Vector3 vector) {rotation = vector;}
    
        Vector3 get_target() {return target;}
        void set_target(double x, double y, double z)
        {
            target.x = (float)x;
            target.y = (float)y;
            target.z = (float)z;
        }
        void set_target(Vector3 vector) {target = vector;}

        void update();
        void rotate(double x, double y, double z);
        void look(double x, double y, double z); 
        void move(double x, double y, double z); 
    };
};
