#ifndef VEC2D_TYPE_H
#define VEC2D_TYPE_H

#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>

template<typename T>
class vec2d
{
protected:
    T x_, y_;
    
public:
    // Constructors
    vec2d(T x = T(0), T y = T(0)) : x_(x), y_(y) {}
    
    vec2d(const vec2d<T> &a) : x_(a.get_x()), y_(a.get_y()) {}
    
    virtual ~vec2d() {}
    
    // Operator
    void operator() (T x, T y) { set_x(x); set_y(y); }
    
    // Get & Set fields
    T get_x() const { return x_; }
    void set_x(T x) { x_ = x; }
    
    T get_y() const { return y_; }
    void set_y(T y) { y_ = y; }
    
    // Vector length
    T get_length() { return sqrt(pow(get_x(), T(2)) + pow(get_y(), T(2))); }
};

// Addition
template<typename T>
vec2d<T> operator+ (vec2d<T> a, T val) { return vec2d<T>(a.get_x() + val, a.get_y() + val); }

template<typename T>
vec2d<T> operator+ (T val, vec2d<T> a) { return vec2d<T>(a.get_x() + val, a.get_y() + val); }

template<typename T>
vec2d<T> operator+ (vec2d<T> a, vec2d<T> b) { return vec2d<T>(a.get_x() + b.get_x(), a.get_y() + b.get_y()); }

// Subtraction
template<typename T>
vec2d<T> operator- (vec2d<T> a, T val) { return vec2d<T>(a.get_x() - val, a.get_y() - val); }

//template<typename T>
//vec2d<T> operator- (T val, vec2d<T> a) { return vec2d<T>(a.get_x() - val, a.get_y() - val); }

template<typename T>
vec2d<T> operator- (vec2d<T> a, vec2d<T> b) { return vec2d<T>(a.get_x() - b.get_x(), a.get_y() - b.get_y()); }

// Multiply
template<typename T>
vec2d<T> operator* (vec2d<T> a, T val) { return vec2d<T>(a.get_x() * val, a.get_y() * val); }

template<typename T>
vec2d<T> operator* (T val, vec2d<T> a) { return vec2d<T>(a.get_x() * val, a.get_y() * val); }

// Scalar product of vectors
template<typename T>
T dot(vec2d<T> a, vec2d<T> b)
{
    return a.get_x() * b.get_x() + a.get_y() * b.get_y();
}

// Normalize vector
template<typename T>
vec2d<T> normalize(vec2d<T> a)
{
    T old_length = a.get_length();
    if (old_length && old_length != T(1))
    {
        a.set_x(a.get_x() / old_length);
        a.set_y(a.get_y() / old_length);
    }
    return vec2d<T>(a.get_x(), a.get_y());
}

// Reflect vector
template<typename T>
vec2d<T> reflect(vec2d<T> a, vec2d<T> normale)
{
    if (normale.get_length() > T(1)) normale = normalize(normale);
    return a - T(2) * dot<T>(a, normale) * normale;
}

// iostream operator
template<typename T>
std::ostream &operator<< (std::ostream &stream, vec2d<T> a) { return stream << "{" << a.get_x() << ";" << a.get_y() << "}"; }

#endif
