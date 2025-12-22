#ifndef RAY_H
#define RAY_H

#include "Vector3.h"

class Ray {
public:
    Vector3 origin;
    Vector3 direction;

    Ray() {}
    Ray(const Vector3& origin, const Vector3& direction)
        : origin(origin), direction(direction.normalized()) {}

    Vector3 at(double t) const {
        return origin + direction * t;
    }
};

#endif // RAY_H
