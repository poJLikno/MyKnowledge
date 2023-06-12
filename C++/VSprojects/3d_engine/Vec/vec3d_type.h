#ifndef VEC3D_TYPE_H
#define VEC3D_TYPE_H

#include "vec2d_type.h"

template<typename T>
class vec3d : public vec2d<T>
{
private:
    T z_;
    
public:
    // Constructors
    vec3d(T x = T(0), T y = T(0), T z = T(0)) : vec2d<T>(x, y), z_(z) {}
    
    vec3d(const vec3d<T> &a) : z_(a.get_z())
    {
        this->set_x(a.get_x());
        this->set_y(a.get_y());
    }
    
    ~vec3d() {}
    
    // Operator
    void operator() (T x, T y, T z) { this->set_x(x); this->set_y(y); set_z(z); }
    
    // Get & Set fields
    T get_z() const { return z_; }
    void set_z(T z) { z_ = z; }
    
    // Vector length
    T get_length()
    {
        return sqrt(pow(this->get_x(), T(2))
                    + pow(this->get_y(), T(2))
                    + pow(get_z(), T(2)));
    }
};

// Addition
template<typename T>
vec3d<T> operator+ (vec3d<T> a, T val)
{
    return vec3d<T>(a.get_x() + val,
                    a.get_y() + val,
                    a.get_z() + val);
}

template<typename T>
vec3d<T> operator+ (T val, vec3d<T> a)
{
    return vec3d<T>(a.get_x() + val,
                    a.get_y() + val,
                    a.get_z() + val);
}

template<typename T>
vec3d<T> operator+ (vec3d<T> a, vec3d<T> b)
{
    return vec3d<T>(a.get_x() + b.get_x(),
                    a.get_y() + b.get_y(),
                    a.get_z() + b.get_z());
}

// Subtraction
template<typename T>
vec3d<T> operator- (vec3d<T> a, T val)
{
    return vec3d<T>(a.get_x() - val,
                    a.get_y() - val,
                    a.get_z() - val);
}

template<typename T>
vec3d<T> operator- (vec3d<T> a, vec3d<T> b)
{
    return vec3d<T>(a.get_x() - b.get_x(),
                    a.get_y() - b.get_y(),
                    a.get_z() - b.get_z());
}

// Multiply
template<typename T>
vec3d<T> operator* (vec3d<T> a, T val)
{
    return vec3d<T>(a.get_x() * val,
                    a.get_y() * val,
                    a.get_z() * val);
}

template<typename T>
vec3d<T> operator* (T val, vec3d<T> a)
{
    return vec3d<T>(a.get_x() * val,
                    a.get_y() * val,
                    a.get_z() * val);
}

// Normalize vector
template<typename T>
vec3d<T> normalize(vec3d<T> a)
{
    T old_length = a.get_length();
    if (old_length && old_length != T(1))
    {
        a.set_x(a.get_x() / old_length);
        a.set_y(a.get_y() / old_length);
        a.set_z(a.get_z() / old_length);
    }
    return vec3d<T>(a.get_x(), a.get_y(), a.get_z());
}

// iostream operator
template<typename T>
std::ostream &operator<< (std::ostream &stream, vec3d<T> a)
{
    return stream << "{"
    << a.get_x() << ";"
    << a.get_y() << ";"
    << a.get_z() << "}";
}

#endif
