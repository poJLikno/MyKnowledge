#include "Rect.h"

bool Rect::FindIntersection(vec3d<float> facing, float x, float y, float z)
{
    vec3d<float> facing_2d = normalize(facing);

    auto func_x = [&](float param) -> float { return facing_2d.get_y() / facing_2d.get_x() * (param - x) + y; };
    auto func_y = [&](float param) -> float { return facing_2d.get_x() / facing_2d.get_y() * (param - y) + x; };

    float dis = sqrtf(powf(x_ - x, 2.f) + powf(y_ - y, 2.f));
    float alfa = atanf(facing.get_z() / sqrtf(powf(facing.get_x(), 2.f) + powf(facing.get_y(), 2.f)) * 180.f / (float)M_PI);

    // X
    if (func_x(x_) <= y_ && func_x(x_) >= y_ - a_ && dot(normalize(vec2d<float>(x_ - x, func_x(x_) - y)), facing_2d) >= 0.f)
    {
        float zh = facing.get_z()
            * vec2d<float>(x_ - x, func_x(x_) - y).get_length()
            / vec2d<float>(facing.get_x(), facing.get_y()).get_length();

        // Z
        if (zh + z <= z_ && zh + z >= z_ - a_) return true;
    }
    if (func_x(x_ + a_) <= y_ && func_x(x_ + a_) >= y_ - a_ && dot(normalize(vec2d<float>(x_ + a_ - x, func_x(x_ + a_) - y)), facing_2d) >= 0.f)
    {
        float zh = facing.get_z()
            * vec2d<float>(x_ + a_ - x, func_x(x_ + a_) - y).get_length()
            / vec2d<float>(facing.get_x(), facing.get_y()).get_length();

        // Z
        if (zh + z <= z_ && zh + z >= z_ - a_) return true;
    }

    // Y
    if (func_y(y_) >= x_ && func_y(y_) <= x_ + a_ && dot(normalize(vec2d<float>(func_y(y_) - x, y_ - y)), facing_2d) >= 0.f)
    {
        float zh = facing.get_z()
            * vec2d<float>(func_y(y_) - x, y_ - y).get_length()
            / vec2d<float>(facing.get_x(), facing.get_y()).get_length();

        // Z
        if (zh + z <= z_ && zh + z >= z_ - a_) return true;
    }
    if (func_y(y_ - a_) >= x_ && func_y(y_ - a_) <= x_ + a_ && dot(normalize(vec2d<float>(func_y(y_ - a_) - x, y_ - a_ - y)), facing_2d) >= 0.f)
    {
        float zh = facing.get_z()
            * vec2d<float>(func_y(y_ - a_) - x, y_ - a_ - y).get_length()
            / vec2d<float>(facing.get_x(), facing.get_y()).get_length();

        // Z
        if (zh + z <= z_ && zh + z >= z_ - a_) return true;
    }

    return false;
}