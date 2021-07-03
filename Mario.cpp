#include "Mario.h"

int Mario::ground_step(int8_t x, int8_t y, float normalY) {
    int steps = 0;

    pair<int16_t, float> yawmag = calc_intended_yawmag(x, y);
    int yaw = yawmag.first - (yawmag.first % 16);

    for (int i = 0; i < 4; i++) {
        this->pos[0] = this->pos[0] + gSineTable[uint16_t(yaw) >> 4] * yawmag.second * normalY * (this->speed / 4.0f);
        this->pos[2] = this->pos[2] + gCosineTable[uint16_t(yaw) >> 4] * yawmag.second * normalY * (this->speed / 4.0f);

        if (!check_inbounds(*this)) { break; }

        steps++;
    }

    return steps;
}