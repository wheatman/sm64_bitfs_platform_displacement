#pragma once

#include <utility>
#include "Mario.h"
#include "Trig.h"

using namespace std;

#ifndef MAGIC_H
#define MAGIC_H

pair<int16_t, float> calc_intended_yawmag(int8_t stick_x, int8_t stick_y);
bool check_inbounds(struct Mario m);
float dist_calc(vector<float> x, vector<float> y);
float line_point(vector<float> p1, vector<float> p2, float x, bool yOrZ);

#endif

