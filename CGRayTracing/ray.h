/*
 * Here, we represent the idea of a ray as a class, and represent the function P(t)
 * as a function that we'll call ray::at(t)
 * 
 * P(t)=A+tb
 * 
 * Where:
 * - P: 3D position along a line in 3D
 * - A: ray origin
 * - b: ray direction
 * - t: ray parameter (real number)
 *
 */


#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
public:
    ray() {}

    ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

    point3 origin() const { return orig; }
    vec3 direction() const { return dir; }

    point3 at(double t) const {
        return orig + t * dir;
    }

private:
    point3 orig;
    vec3 dir;
};

#endif