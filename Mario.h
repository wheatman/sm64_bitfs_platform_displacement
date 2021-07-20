#pragma once

#include <vector>
#include "Magic.h"
#include "vmath.h"

using namespace std;

#ifndef MARIO_H
#define MARIO_H

class Mario
{
public:
	Vec3f pos = { 0,0,0 };
	float speed;

	Mario() {}

	Mario(const Vec3f& position, float spd) {
		set_pos(position);
		speed = spd;
	}

	void set_pos(const Vec3f& position);
	int ground_step(int yaw, float normalY);
	//vector<float> qstep(int8_t x, int8_t y);

};

#endif