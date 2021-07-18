#include "Surface.h"

void Surface::rotate(vector<int32_t> pivot, vector<vector<float>> transformation) {
	vector<int32_t> v1 = vector1;
	vector<int32_t> v2 = vector2;
	vector<int32_t> v3 = vector3;

	for (int i = 0; i < 3; i++) {
		v1[i] = v1[i] - pivot[i];
		v2[i] = v2[i] - pivot[i];
		v3[i] = v3[i] - pivot[i];
	}

	v1.push_back(1);
	v2.push_back(1);
	v3.push_back(1);

	vector<float> rotated1 = vector<float>(4, 0);
	vector<float> rotated2 = vector<float>(4, 0);
	vector<float> rotated3 = vector<float>(4, 0);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			rotated1[i] += v1[i] * transformation[i][j];
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			rotated2[i] += v2[i] * transformation[i][j];
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			rotated3[i] += v3[i] * transformation[i][j];
		}
	}

	for (int i = 0; i < 3; i++) {
		vector1[i] = static_cast<int32_t>(rotated1[i]) + pivot[0];
		vector2[i] = static_cast<int32_t>(rotated2[i]) + pivot[1];
		vector3[i] = static_cast<int32_t>(rotated3[i]) + pivot[2];
	}
}

void Surface::repr() {
	printf("vector1: (");

	for (int i = 0; i < 3; i++) {
		printf("%d", vector1[i]);

		if (i != 2) {
			printf(", ");
		}
		else {
			printf(")\n");
		}
	}

	printf("vector2: (");

	for (int i = 0; i < 3; i++) {
		printf("%d", vector2[i]);

		if (i != 2) {
			printf(", ");
		}
		else {
			printf(")\n");
		}
	}

	printf("vector3: (");

	for (int i = 0; i < 3; i++) {
		printf("%d", vector3[i]);

		if (i != 2) {
			printf(", ");
		}
		else {
			printf(")\n");
		}
	}
}