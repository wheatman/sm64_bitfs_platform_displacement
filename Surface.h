#pragma once

#include <vector>
#include <cstdio>
#include <cstdint>

using namespace std;

#ifndef SURFACE_H
#define SURFACE_H

#define SIDE_LENGTH 613

class Surface
{
public:
	vector<int32_t> vector1;
	vector<int32_t> vector2;
	vector<int32_t> vector3;
	bool top;

	Surface(bool top) {
		vector1 = { -1638, -2918, -1021 };

		if (top) {
			vector2 = { -2251, -2918, -1021 };
			vector3 = { -2251, -2918, -408 };
		}
		else {
			vector2 = { -2251, -2918, -408 };
			vector3 = { -1638, -2918, -408 };
		}

		this->top = top;
	}

	void rotate(vector<int32_t> pivot, vector<vector<float>> transformation);
	void repr();
};

#endif
