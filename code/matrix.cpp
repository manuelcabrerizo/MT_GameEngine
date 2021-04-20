#include "engine.h"

namespace Octane
{

Matrix::Matrix()
    : D3DXMATRIX()
{

}

Matrix::Matrix(const Matrix& M)
    : D3DXMATRIX(M)
{
    *this = M;
}

Matrix::Matrix(const D3DXMATRIX& M)
    : D3DXMATRIX(M)
{
    *this = M;
}

Matrix& Matrix::operator=(const Matrix& M)
{
    memcpy(m, &M.m, sizeof(float)* 16);
    return *this;
}

Matrix& Matrix::operator=(const D3DXMATRIX& M)
{
    memcpy(m, &M.m, sizeof(float) * 16);
    return *this;
}

void Matrix::set_zero()
{
    fill(0.0f);
}

void Matrix::set_identity()
{
    //set most element to zero
    m[0][1] = m[0][2] = m[0][3] =
    m[1][0] = m[1][2] = m[1][3] =
    m[2][0] = m[2][1] = m[2][3] =
    m[3][0] = m[3][1] = m[3][2] = 0.0f;

    //set diagonals 11, 22, 33, 44 to one
    m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
}

void Matrix::fill(int value)
{
    fill((float)value);
}

void Matrix::fill(float value)
{
    m[0][0] = m[0][1] = m[0][2] = m[0][3] =
    m[1][0] = m[1][1] = m[1][2] = m[1][3] =
    m[2][0] = m[2][1] = m[2][2] = m[2][3] =
    m[3][0] = m[3][1] = m[3][2] = m[3][3] = value;  
}

void Matrix::fill(double value)
{
    fill((float)value);
}

void Matrix::translate(float x, float y, float z)
{
    D3DXMatrixTranslation((D3DXMATRIX*)this, x, y, z);
}

void Matrix::translate(Vector3& v)
{
    translate((float)v.get_x(), (float)v.get_y(), (float)v.get_z());
}

void Matrix::rotate_yaw_pitch_roll(float x, float y, float z)
{
    D3DXMatrixRotationYawPitchRoll((D3DXMATRIX*)this, x, y, z);
}

void Matrix::rotate_yaw_pitch_roll(Vector3& v)
{
    rotate_yaw_pitch_roll((float)v.get_x(), (float)v.get_y(), (float)v.get_z());
}

void Matrix::rotate_x(float angle)
{
    D3DXMatrixRotationX((D3DXMATRIX*)this, angle);
}

void Matrix::rotate_y(float angle)
{
    D3DXMatrixRotationY((D3DXMATRIX*)this, angle);
}

void Matrix::rotate_z(float angle)
{
    D3DXMatrixRotationZ((D3DXMATRIX*)this, angle);
}

void Matrix::scale(float x, float y, float z)
{
    D3DXMatrixScaling((D3DXMATRIX*)this, x, y, z);
}

void Matrix::scale(Vector3& v)
{
    scale((float)v.get_x(), (float)v.get_y(), (float)v.get_z());
}

};
