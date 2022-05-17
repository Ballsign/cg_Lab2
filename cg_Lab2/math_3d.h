#ifndef MATH_3D_H
#define MATH_3D_H

#define _USE_MATH_DEFINES

#include <cmath>
#include <math.h>
#include <stdio.h>
#include <glm/glm.hpp>

#define ToDegree(x) ((x) * 180.0f / M_PI)
#define ToRadian(x) ((x) * M_PI / 180.0f)

struct Quaternion
{
    float x, y, z, w;

    Quaternion(float _x, float _y, float _z, float _w);

    void Normalize();

    Quaternion Conjugate();
};

Quaternion operator*(const Quaternion& l, const Quaternion& r);

Quaternion operator*(const Quaternion& q, const glm::vec3& v);

#endif