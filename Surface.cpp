#include "Surface.h"

void Surface::rotate(const Vec3s& pivot, const Mat4& transformation) {
	Vec3s v1;
	Vec3s v2;
	Vec3s v3;

	Vec3f rotated1;
	Vec3f rotated2;
	Vec3f rotated3;

	for (int i = 0; i < 3; i++) {
		v1[i] = vector1[i] - pivot[i];
		v2[i] = vector2[i] - pivot[i];
		v3[i] = vector3[i] - pivot[i];
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			rotated1[i] += v1[j] * transformation[j][i];
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			rotated2[i] += v2[j] * transformation[j][i];
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			rotated3[i] += v3[j] * transformation[j][i];
		}
	}

	for (int i = 0; i < 3; i++) {
		vector1[i] = static_cast<int16_t>(static_cast<int>(rotated1[i])) + pivot[i];
		vector2[i] = static_cast<int16_t>(static_cast<int>(rotated2[i])) + pivot[i];
		vector3[i] = static_cast<int16_t>(static_cast<int>(rotated3[i])) + pivot[i];
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