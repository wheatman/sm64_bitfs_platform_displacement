#include "Mario.hpp"

void Mario::set_pos(const Vec3f& position) {
    for (int i = 0; i < 4; i++) {
        this->pos[i] = position[i];
    }
}

int Mario::ground_step(int yaw, float normalY) {
    int steps = 0;

    for (int i = 0; i < 4; i++) {
        this->pos[0] = this->pos[0] + gSineTable[uint16_t(yaw) >> 4] * normalY * (this->speed / 4.0f);
        this->pos[2] = this->pos[2] + gCosineTable[uint16_t(yaw) >> 4] * normalY * (this->speed / 4.0f);

        if (!check_inbounds(*this)) { break; }

        steps++;
    }

    return steps;
}