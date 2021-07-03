#include "Magic.h"

pair<int16_t, float> calc_intended_yawmag(int8_t stickX, int8_t stickY) {
	int16_t intYaw;
	float intMag;

	float intStickX = 0;
	float intStickY = 0;

	//printf("%d, %d, %d\n", stickX, stickY, camYaw);

	if (stickX <= -8) {
		intStickX = stickX + 6;
	}
	else if (stickX >= 8) {
		intStickX = stickX - 6;
	}

	if (stickY <= -8) {
		intStickY = stickY + 6;
	}
	else if (stickY >= 8) {
		intStickY = stickY - 6;
	}

	float stickMag = sqrtf(powf(intStickX, 2) + powf(intStickY, 2));

	if (stickMag > 64.0) {
		intStickX = float(intStickX * 64.0 / stickMag);
		intStickY = float(intStickY * 64.0 / stickMag);
		stickMag = 64.0;
	}

	stickMag = float(((stickMag / 64.0) * (stickMag / 64.0)) * 64.0);
	intMag = float(stickMag / 2.0);

	intYaw = atan2s(-intStickY, intStickX);
	
	/*
	if (intMag > 0.0) {
		intYaw = atan2s(-intStickY, intStickX);
	}
	else {
		intYaw = yaw;
		//intYaw = *marioFYaw(game);
	}*/

	return { intYaw, intMag };
}

bool check_inbounds(Mario m) {
	float x_mod = fmodf(m.pos[0] + 32768, 65536) - 32768;
	float y_mod = fmodf(m.pos[1] + 32768, 65536) - 32768;
	float z_mod = fmodf(m.pos[2] + 32768, 65536) - 32768;

	if (abs(x_mod) < 8192 && abs(y_mod) < 8192 && abs(z_mod) < 8192) {
		return true;
	}
	else {
		return false;
	}
}

float dist_calc(vector<float> x, vector<float> y) {
	return sqrtf(powf(y[0] - x[0], 2) + powf(y[1] - x[1], 2) + powf(y[2] - x[2], 2));
}

float line_point(vector<float> p1, vector<float> p2, float x, bool followY) {
	if (followY) {
		return (p2[1] - p1[1]) / (p2[0] - p1[0]) * (x - p1[0]) - p1[1];
	}
	else {
		return (p2[2] - p1[2]) / (p2[0] - p1[0]) * (x - p1[0]) - p1[2];
	}
}