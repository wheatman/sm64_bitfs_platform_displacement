#pragma once

#include <vector>
#include <cstdio>
#include <cstdint>

#include "vmath.h"

using namespace std;

#ifndef SURFACE_H
#define SURFACE_H

class Surface
{
public:
	Vec3s vector1;
	Vec3s vector2;
	Vec3s vector3;
	bool top;

	Surface(bool top) {
		vector1[0] = -1638;
		vector1[1] = -2918;
		vector1[2] = -1021;

		if (top) {
			vector2[0] = -2251;
			vector2[1] = -2918;
			vector2[2] = -1021;
			vector3[0] = -2251;
			vector3[1] = -2918;
			vector3[2] = -408;
		}
		else {
			vector2[0] = -2251;
			vector2[1] = -2918;
			vector2[2] = -408;
			vector3[0] = -1638;
			vector3[1] = -2918;
			vector3[2] = -408;
		}

		this->top = top;
	}

	void rotate(const Vec3s& pivot, const Mat4& transformation);
	void repr();
};

typedef Surface Vec2S[2];

#endif
