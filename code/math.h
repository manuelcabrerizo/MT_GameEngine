#pragma once

#include "vector.h"

namespace Octane
{
    const double PI    = 3.1415926535;
    const double PI_OVER_180  = PI / 180.0f;
    const double PI_UNDER_180 = 180.0f / PI;

    class Math
    {
    public:
        static double to_degrees(double radian);
        static double to_radians(double degree);
        static double wrap_angle_degs(double degs);
        static double wrap_angle_rads(double rads);
        static double wrap_value(double value, double min, double max);
        static double limit(double value, double min, double max); //***addition
        static Vector2 linear_velocity(double angle);
        static double linear_velocity_x(double angle);
        static double linear_velocity_y(double angle); 
        static double angle_to_target(double x1, double y1, double x2, double y2);
        static double angle_to_target(Vector3& source, Vector3& target);
        static double angle_to_target(Vector2& source, Vector2& target);
        static double distance(double x1, double y1, double z1, double x2, double y2, double z2);
        static double distance(double x1, double y1, double x2, double y2);
        static double distance(Vector3& a, Vector3& b);
        static double distance(Vector2& a, Vector2& b);
        static double length(double x, double y, double z);
        static double length(double x, double y);
        static double length(Vector3& v);
        static double length(Vector2& v);
        static double dot_product(double x1, double y1, double z1, double x2, double y2, double z2);
        static double dot_product(double x1, double y1, double x2, double y2);
        static double dot_product(Vector3& a, Vector3& b);
        static double dot_product(Vector2& a, Vector2& b);
        static Vector3 cross_product(double x1, double y1, double z1, double x2, double y2, double z2);
        static Vector3 cross_product(Vector3& a, Vector3& b);
        static Vector3 normal(double x, double y, double z);
        static Vector3 normal(Vector3& v);
    };
};


