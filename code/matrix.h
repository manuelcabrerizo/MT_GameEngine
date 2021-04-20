#pragma once

#include "engine.h"
#include "vector.h"

namespace Octane
{

struct Matrix : public D3DXMATRIX
{
public:
    Matrix();
    Matrix(const Matrix& M);
    Matrix(const D3DXMATRIX& M);
    Matrix& operator=(const Matrix& M);
    Matrix& operator=(const D3DXMATRIX& M);
    void set_zero();
    void set_identity();
    void fill(int value);
    void fill(float value);
    void fill(double value);
    void translate(float x, float y, float z);
    void translate(Vector3& v);
    void rotate_yaw_pitch_roll(float x, float y, float z);
    void rotate_yaw_pitch_roll(Vector3& v);
    void rotate_x(float angle);
    void rotate_y(float angle);
    void rotate_z(float angle);
    void scale(float x, float y, float z);
    void scale(Vector3& v);
};

};
