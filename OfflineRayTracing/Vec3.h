#ifndef VEC3_H
#define VEC3_H

#include <DirectXMath.h>
#include "OfflineRayTracing.h"

class vec3 {
public:
    DirectX::XMFLOAT3 vec;

    vec3() : vec{ 0,0,0 } {}
    vec3(float e0, float e1, float e2) : vec{ e0, e1, e2 } {}

    double x() const { return vec.x; }
    double y() const { return vec.y; }
    double z() const { return vec.z; }

    vec3 operator-() const { return vec3(-vec.x, -vec.y, -vec.z); }
    float operator[](int i) const
    {
        if (i == 0)
            return vec.x;
        if (i == 1)
            return vec.y;
        if (i == 2)
            return vec.z; 
    }
    float& operator[](int i) 
    {  
        if (i == 0)
            return vec.x;
        if (i == 1)
            return vec.y;
        if (i == 2)
            return vec.z; 
    }

    vec3& operator+=(const vec3& v) {
        vec.x += v.vec.x;
        vec.y += v.vec.y;
        vec.z += v.vec.z;
        return *this;
    }

    vec3& operator*=(double t) {
        vec.x *= t;
        vec.y *= t;
        vec.z *= t;
        return *this;
    }

    vec3& operator/=(double t) {
        return *this *= 1 / t;
    }

    double length() const {
        return std::sqrt(length_squared());
    }

    double length_squared() const {
        return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
    }

    static vec3 random() {
        return vec3(random_double(), random_double(), random_double());
    }

    static vec3 random(double min, double max) {
        return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }
};

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
using point3 = vec3;


// Vector Utility Functions
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.vec.x << ' ' << v.vec.y << ' ' << v.vec.z;
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.vec.x + v.vec.x, u.vec.y + v.vec.y, u.vec.z + v.vec.z);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.vec.x - v.vec.x, u.vec.y - v.vec.y, u.vec.z - v.vec.z);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.vec.x * v.vec.x, u.vec.y * v.vec.y, u.vec.z * v.vec.z);
}

inline vec3 operator*(double t, const vec3& v) {
    return vec3(t * v.vec.x, t * v.vec.y, t * v.vec.z);
}

inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

inline vec3 operator/(const vec3& v, double t) {
    return (1 / t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
    return u.vec.x * v.vec.x
        + u.vec.y * v.vec.y
        + u.vec.z * v.vec.z;
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.vec.y * v.vec.z - u.vec.z * v.vec.y,
        u.vec.z * v.vec.x - u.vec.x * v.vec.z,
        u.vec.x * v.vec.y - u.vec.y * v.vec.x);
}

inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

inline vec3 random_unit_vector() {
    while (true) {
        auto p = vec3::random(-1, 1);
        auto lensq = p.length_squared();
        if (1e-160 < lensq && lensq <= 1)
            return p / sqrt(lensq);
    }
}

inline vec3 random_on_hemisphere(const vec3& normal) {
    vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return on_unit_sphere;
    else
        return -on_unit_sphere;
}

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
using point3 = vec3;

#endif