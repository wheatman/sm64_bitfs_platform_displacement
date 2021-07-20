#pragma once

#include "Trig.h"
#include <vector>

using namespace std;

#ifndef VMATH_H
#define VMATH_H

typedef float Vec2f[2];
typedef float Vec3f[3]; // X, Y, Z, where Y is up
typedef int16_t Vec3s[3];
typedef int32_t Vec3i[3];
typedef float Vec4f[4];
typedef int16_t Vec4s[4];

typedef float Mat4[4][4];

void vec3f_normalize(Vec3f &v);
void vec3f_cross(Vec3f &dst, const Vec3f &a, const Vec3f &b);
void vec3f_set(Vec3f &dst, float x, float y, float z);
void mtxf_align_terrain_normal(Mat4 &dest, Vec3f &upDir, const Vec3s &pos);
void linear_mtxf_mul_vec3f(Vec3f &dst, const Mat4 &m, const Vec3f &v);

#endif