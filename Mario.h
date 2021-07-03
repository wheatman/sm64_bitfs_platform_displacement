#pragma once

#include <vector>
#include "Magic.h"

using namespace std;

#ifndef MARIO_H
#define MARIO_H

class Mario
{
public:
	vector<float> pos = vector<float>(3, 0);
	float speed;

	Mario(vector<float>position, float spd) {
		pos = position;
		speed = spd;
	}

	int ground_step(int8_t x, int8_t y, float normalY);
	//vector<float> qstep(int8_t x, int8_t y);

};

#endif