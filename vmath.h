#pragma once

#include <vector>
#include "Trig.h"

using namespace std;

#ifndef VMATH_H
#define VMATH_H

void vec_normalize(vector<float> v);
void vec_cross(vector<float> dest, vector<float> a, vector<float> b);
void vec_set(vector<float> dest, float x, float y, float z);
void align_normal(vector<vector<float>> transform, vector<float> normal, vector<float> pos);
void linear_mtxf_mul_vec3f(vector<vector<float>> m, vector<float> dst, vector<float> v);

#endif