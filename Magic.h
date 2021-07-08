#pragma once

#include <stdexcept>
#include <utility>
#include "Mario.h"
#include "Trig.h"

using namespace std;

#ifndef MAGIC_H
#define MAGIC_H

pair<int16_t, float> calc_intended_yawmag(int8_t stick_x, int8_t stick_y);
bool check_inbounds(struct Mario m);
float dist_calc(vector<float> x, vector<float> y);
float line_point(vector<int32_t> p1, vector<int32_t> p2, float x, bool yOrZ);

#endif

