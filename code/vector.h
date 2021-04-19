#pragma once

#include "engine.h"

class Vector2
{
public:
    double x, y;
    virtual ~Vector2() {}
    Vector2();
    Vector2(const Vector2& v);
    Vector2(double x, double y);
    Vector2(int x, int y);
    Vector2(const D3DXVECTOR2& dv);
    Vector2(const D3DXVECTOR3& dv);
    Vector2& operator=(const Vector2& v);

    //manipulation functions
    void set(double x1, double y1);
    void set(const Vector2& v);
    double get_x() {return x;}
    void set_x(double value) {x = value;}
    double get_y() {return y;}
    void set_y(double value) {y = value;}
    void move(double mx, double my);
    void operator+=(const Vector2& v);
    void operator-=(const Vector2& v);
    void operator*=(const Vector2& v);
    void operator/=(const Vector2& v);
    Vector2 operator/(const double& d);
    bool operator==(const Vector2& v) const;
    bool operator!=(const Vector2& v) const;

    //exporters to direct3d vectors
    D3DXVECTOR3 to_d3d_vector3();
    D3DXVECTOR2 to_d3d_vector2();
};

class Vector3
{
public:
    double x, y, z;
    virtual ~Vector3() {}
    Vector3();
    Vector3(const Vector3& v);
    Vector3(double x, double y, double z);
    Vector3(int x, int y, int z);
    Vector3(const D3DXVECTOR2& dv);
    Vector3(const D3DXVECTOR3& dv);
    Vector3& operator=(const Vector3& v);

    //manipulation functions
    void set(double x1, double y1, double z1);
    void set(const Vector3& v);
    double get_x() {return x;}
    void set_x(double value) {x = value;}
    double get_y() {return y;}
    void set_y(double value) {y = value;}
    double get_z() {return z;}
    void set_z(double value) {z = value;}
    void move(double mx, double my, double mz);
    void operator+=(const Vector3& v);
    void operator-=(const Vector3& v);
    void operator*=(const Vector3& v);
    void operator/=(const Vector3& v);
    Vector3 operator/(const double& d);
    bool operator==(const Vector3& v) const;
    bool operator!=(const Vector3& v) const;

    //exporters to direct3d vectors
    D3DXVECTOR3 to_d3d_vector3();
    D3DXVECTOR2 to_d3d_vector2();

};
