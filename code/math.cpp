#include "engine.h"

namespace Octane
{
    double Math::to_degrees(double radian)
    {
        return radian * PI_UNDER_180; 
    }

    double Math::to_radians(double degree)
    {
        return degree * PI_OVER_180;
    }

    double Math::wrap_angle_degs(double degs)
    {
        double result = fmod(degs, 360.0);
        if(result < 0) result += 360.0f;
        return result;
    }

    double Math::wrap_angle_rads(double rads)
    {
        double result = fmod(rads, PI);
        if(result < 0) result += PI;
        return result;
    }

    double Math::wrap_value(double value, double min, double max)
    {
        if(value < min) value = max;
        else if(value > max) value = min;
        return value;
    }

    double Math::limit(double value, double min, double max)
    {
        if(value < min) value = min;
        else if(value > max) value = max;
        return value;
    }

    double Math::linear_velocity_x(double angle)
    {
        angle -= 90;
        if(angle < 0) angle = 360 + angle;
        return cos(to_radians(angle)); 
    }

    double Math::linear_velocity_y(double angle)
    {
        angle -= 90;
        if(angle < 0) angle = 360 + angle;
        return sin(to_radians(angle));
    }

    Vector2 Math::linear_velocity(double angle)
    {
        double vx = linear_velocity_x(angle);
        double vy = linear_velocity_y(angle);
        return Vector2(vx, vy);
    }

    double Math::angle_to_target(double x1, double y1, double x2, double y2)
    {
        double delta_x = (x2 - x1);
        double delta_y = (y2 - y1);
        return atan2(delta_y, delta_x); 
    }

    double Math::angle_to_target(Vector3& source, Vector3& target)
    {
        return angle_to_target(source.x, source.y, target.x, target.y);
    }

    double Math::angle_to_target(Vector2& source, Vector2& target)
    {
        return angle_to_target(source.x, source.y, target.x, target.y);
    }

    double Math::distance(double x1, double y1, double z1, double x2, double y2, double z2)
    {
        double delta_x = (x2 - x1);
        double delta_y = (y2 - y1);
        double delta_z = (z2 - z1);
        return sqrt(delta_x*delta_x + delta_y*delta_y + delta_z*delta_z); 
    }

    double Math::distance(double x1, double y1, double x2, double y2)
    {
        double delta_x = (x2 - x1);
        double delta_y = (y2 - y1);
        return sqrt(delta_x*delta_x + delta_y*delta_y); 
    }

    double Math::distance(Vector3& a, Vector3& b)
    {
        return distance(a.get_x(), a.get_y(), a.get_z(), b.get_x(), b.get_y(), b.get_z()); 
    }

    double Math::distance(Vector2& a, Vector2& b)
    {
        return distance(a.get_x(), a.get_y(), b.get_x(), b.get_y()); 
    }

    double Math::length(double x, double y, double z)
    {
        return sqrt(x*x + y*y + z*z); 
    }

    double Math::length(double x, double y)
    {
        return sqrt(x*x + y*y);
    }

    double Math::length(Vector3& v)
    {
        return length(v.get_x(), v.get_y(), v.get_z());
    }

    double Math::length(Vector2& v)
    { 
        return length(v.get_x(), v.get_y());
    }

    double Math::dot_product(double x1, double y1, double z1, double x2, double y2, double z2)
    {
        return (x1*x2 + y1*y2 + z1*z2); 
    }

    double Math::dot_product(double x1, double y1, double x2, double y2)
    {
        return (x1*x2 + y1*y2);
    }

    double Math::dot_product(Vector3& a, Vector3& b)
    {
        return dot_product(a.get_x(), a.get_y(), a.get_z(), b.get_x(), b.get_y(), b.get_z());
    }

    double Math::dot_product(Vector2& a, Vector2& b)
    { 
        return dot_product(a.get_x(), a.get_y(), b.get_x(), b.get_y());
    }

    Vector3 Math::cross_product(double x1, double y1, double z1, double x2, double y2, double z2)
    {
        double nx = (y1*z2) - (z1*y2);
        double ny = (z1*y2) - (x1*z2);
        double nz = (x1*y2) - (y1*x2);
        return Vector3(nx, ny, nz); 
    }

    Vector3 Math::cross_product(Vector3& a, Vector3& b)
    {
        return cross_product(a.get_x(), a.get_y(), a.get_z(), b.get_x(), b.get_y(), b.get_z());
    }

    Vector3 Math::normal(double x, double y, double z)
    {
        double vec_length = length(x, y, z);
        if(vec_length != 0) vec_length = 1 / vec_length; 
        double nx = x * vec_length;
        double ny = y * vec_length;
        double nz = z * vec_length;
        return Vector3(nx,ny,nz);
    }

    Vector3 Math::normal(Vector3& v)
    {
        return normal(v.get_x(), v.get_y(), v.get_z());
    }
};


