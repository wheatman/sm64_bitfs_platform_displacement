#pragma once

#include <vector>
#include "Trig.h"

using namespace std;

#ifndef VMATH_H
#define VMATH_H

vector<float> vec_normalize(vector<float> v);
vector<float> vec_cross(vector<float> a, vector<float> b);
vector<float> vec_set(float x, float y, float z);
vector<vector<float>> align_normal(vector<float> normal, vector<float> pos);
vector<float> linear_mtxf_mul_vec3f(vector<vector<float>> m, vector<float> v);

#endif