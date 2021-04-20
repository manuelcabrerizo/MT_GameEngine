#include "engine.h"

using namespace std;

namespace Octane
{
    Camera::Camera()
    {
        //create default perspective matrix
        position = Vector3(0.0f, 0.0f, 10.0f);
        up_dir = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
        double ratio = 640 / 480;
        set_perspective(Octane::PI / 4.0f, ratio, 1.0f, 1000.0f);

        this->update();
    }

    Camera::~Camera() {}

    void Camera::set_perspective(double fov, double aspect_ratio, double near_range, double far_range)
    {
        this->fov = fov;
        this->aspect_ratio = aspect_ratio;
        this->near_range = near_range;
        this->far_range = far_range;

        //set the camera perspective matrix
        D3DXMatrixPerspectiveFovLH(&this->matrix_proj, (float)this->fov, 
                (float)this->aspect_ratio, (float)this->near_range, (float)this->far_range);
    }

    void Camera::update()
    {
        D3DXVECTOR3 pos = this->position.to_d3d_vector3();
        D3DXVECTOR3 targ = this->target.to_d3d_vector3();

        D3DXMatrixLookAtLH(&this->matrix_view, &pos, &targ, &this->up_dir);
    }

    void Camera::set_position(double x, double y, double z)
    {
        this->position.x = (float)x;
        this->position.y = (float)y; 
        this->position.z = (float)z;
    }

    void Camera::set_rotation(double x, double y, double z)
    {
        this->rotation.x = (float)x;
        this->rotation.y = (float)y; 
        this->rotation.z = (float)z;

        D3DXMatrixRotationYawPitchRoll(&this->matrix_rot, (float)rotation.x,
                (float)rotation.y, (float)rotation.z);
    }

    //adjust rotation relative to current rotation values
    void Camera::rotate(double x, double y, double z)
    {
        this->rotation.x += (float)x;
        this->rotation.y += (float)y;
        this->rotation.z += (float)z;
    }

    void Camera::look(double x, double y, double z)
    {
        this->target.x += (float)x;
        this->target.y += (float)y;
        this->target.z += (float)z;
    }

    void Camera::move(double x, double y, double z)
    {
        this->position.x += (float)x;
        this->position.y += (float)y;
        this->position.z += (float)z;

        this->target.x += (float)x;
        this->target.y += (float)y;
        this->target.z += (float)z;
    }

};
