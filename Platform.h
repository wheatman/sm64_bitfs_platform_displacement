#pragma once

#include <vector>
#include "Mario.h"
#include "Surface.h"
#include "vmath.h"

using namespace std;

#ifndef PLATFORM_H
#define PLATFORM_H

class Platform
{
public:
	vector<float> pos = { -1945.0f, -3225.0f, -715.0f };
	vector<float> normal = { 0, 1, 0 };
	vector<vector<float>> transform = { {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0} };
	vector<Surface> triangles = { Surface(true), Surface(false) };

	Platform() {
		create_transform_from_normals();
	}

	void create_transform_from_normals();
	Surface* find_floor(Mario* m);
	void platform_logic(Mario* m);
};

float approach_by_increment(float goal, float src, float inc);

#endif