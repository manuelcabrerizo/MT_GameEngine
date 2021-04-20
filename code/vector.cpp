#include "engine.h"

/**
VECTOR 2
**/
namespace Octane
{

Vector2::Vector2()
{
    x = y = 0;
}

Vector2::Vector2(const Vector2& v)
{
    *this = v;
}

Vector2::Vector2(double x, double y)
{
    set(x, y);
}

Vector2::Vector2(int x, int y)
{
    set((double)x, (double)y);
}

Vector2::Vector2(const D3DXVECTOR2& dv)
{
    x = dv.x;
    y = dv.y;
}

Vector2::Vector2(const D3DXVECTOR3& dv)
{
    x = dv.x;
    y = dv.y;   
}

Vector2& Vector2::operator=(const Vector2& v)
{
    set(v);
    return *this;
}

//manipulation functions
void Vector2::set(double x1, double y1)
{
    x = x1;
    y = y1;
}

void Vector2::set(const Vector2& v)
{
    x = v.x;
    y = v.y;
}

void Vector2::move(double mx, double my)
{
    x += mx;
    y += my;
}

void Vector2::operator+=(const Vector2& v)
{
    x += v.x;
    y += v.y;
}

void Vector2::operator-=(const Vector2& v)
{
    x -= v.x;
    y -= v.y;
}

void Vector2::operator*=(const Vector2& v)
{
    x *= v.x;
    y *= v.y;
}

void Vector2::operator/=(const Vector2& v)
{
    x /= v.x;
    y /= v.y;
}

Vector2 Vector2::operator/(const double& d)
{
    Vector2 v(x/d, y/d);
    return v;
}

bool Vector2::operator==(const Vector2& v) const
{
    return (
            (((v.x - 0.0001f) < x) && (x < (v.x + 0.0001f))) &&
            (((v.y - 0.0001f) < y) && (y < (v.y + 0.0001f))));
}

bool Vector2::operator!=(const Vector2& v) const
{
    return (!(*this == v));
}

//exporters to direct3d vectors
D3DXVECTOR3 Vector2::to_d3d_vector3()
{
    return D3DXVECTOR3((float)x, (float)y, 0.0f);
}

D3DXVECTOR2 Vector2::to_d3d_vector2()
{
    return D3DXVECTOR2((float)x, (float)y);
}

/**
VECTOR 3
**/

Vector3::Vector3()
{
    x = y = z = 0;
}

Vector3::Vector3(const Vector3& v)
{   
    *this = v;
}

Vector3::Vector3(double x, double y, double z)
{
    set(x, y, z);
}

Vector3::Vector3(int x, int y, int z)
{
    set((double)x, (double)y, (double)z);
}

Vector3::Vector3(const D3DXVECTOR2& dv)
{
    x = dv.x;
    y = dv.y;
    z = 0.0;
}

Vector3::Vector3(const D3DXVECTOR3& dv)
{
    x = dv.x;
    y = dv.y;
    z = dv.z;
}

Vector3& Vector3::operator=(const Vector3& v)
{
    set(v);
    return *this;
}

//manipulation functions
void Vector3::set(double x1, double y1, double z1)
{
    x = x1;
    y = y1;
    z = z1;
}

void Vector3::set(const Vector3& v)
{
    x = v.x;
    y = v.y;
    z = v.z;
}

void Vector3::move(double mx, double my, double mz)
{
    x += mx;
    y += my;
    z += mz;
}

void Vector3::operator+=(const Vector3& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
}

void Vector3::operator-=(const Vector3& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
}

void Vector3::operator*=(const Vector3& v)
{
    x *= v.x;
    y *= v.y;
    z *= v.z;
}

void Vector3::operator/=(const Vector3& v)
{
    x /= v.x;
    y /= v.y;
    z /= v.z;
}

Vector3 Vector3::operator/(const double& d)
{
    Vector3 v(x/d, y/d, z/d);
    return v;
}

bool Vector3::operator==(const Vector3& v) const
{
    return (
            (((v.x - 0.0001f) < x) && (x < (v.x + 0.0001f))) &&
            (((v.y - 0.0001f) < y) && (y < (v.y + 0.0001f))) && 
            (((v.z - 0.0001f) < z) && (z < (v.z + 0.0001f))));
}

bool Vector3::operator!=(const Vector3& v) const
{
    return (!(*this == v));
}

//exporters to direct3d vectors
D3DXVECTOR3 Vector3::to_d3d_vector3()
{
    return D3DXVECTOR3((float)x, (float)y, (float)z);
}

D3DXVECTOR2 Vector3::to_d3d_vector2()
{
    return D3DXVECTOR2((float)x, (float)y);
}

};
