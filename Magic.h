#pragma once

#include "Trig.h"
#include "vmath.h"
#include <stdexcept>
#include <utility>

using namespace std;

#ifndef MAGIC_H
#define MAGIC_H
class Mario;

pair<int16_t, float> calc_intended_yawmag(int8_t stick_x, int8_t stick_y);
bool check_inbounds(const Mario &m);
float dist_calc(const Vec3f& x, const Vec3f& y);
float line_point(const Vec3s& p1, const Vec3s& p2, float x, bool yOrZ);

#endif
