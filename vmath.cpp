#include "vmath.h"

/**
 * Multiply a vector by a matrix of the form
 * | ? ? ? 0 |
 * | ? ? ? 0 |
 * | ? ? ? 0 |
 * | 0 0 0 1 |
 * i.e. a matrix representing a linear transformation over 3 space.
 */
void linear_mtxf_mul_vec3f(vector<vector<float>> m, vector<float> dst, vector<float> v) {
    int32_t i;
    for (i = 0; i < 3; i++) {
        dst[i] = m[0][i] * v[0] + m[1][i] * v[1] + m[2][i] * v[2];
    }
}

/// Set vector 'dest' to (x, y, z)
void vec_set(vector<float> dest, float x, float y, float z) {
    dest[0] = x;
    dest[1] = y;
    dest[2] = z;
}

/// Make vector 'dest' the cross product of vectors a and b.
void vec_cross(vector<float> dest, vector<float> a, vector<float> b) {
    dest[0] = a[1] * b[2] - b[1] * a[2];
    dest[1] = a[2] * b[0] - b[2] * a[0];
    dest[2] = a[0] * b[1] - b[0] * a[1];
}

/// Scale vector 'dest' so it has length 1
void vec_normalize(vector<float> dest) {
    //! Possible division by zero
    float invsqrt = 1.0f / sqrtf(dest[0] * dest[0] + dest[1] * dest[1] + dest[2] * dest[2]);

    dest[0] *= invsqrt;
    dest[1] *= invsqrt;
    dest[2] *= invsqrt;
}

/**
 * Set 'dest' to a transformation matrix that aligns an object with the terrain
 * based on the normal. Used for enemies.
 * 'upDir' is the terrain normal
 * 'yaw' is the angle which it should face
 * 'pos' is the object's position in the world
 */
void align_normal(vector<vector<float>> dest, vector<float> upDir, vector<float> pos) {
    vector<float> lateralDir(3, 0);
    vector<float> leftDir(3, 0);
    vector<float> forwardDir(3, 0);

    vec_set(lateralDir, gSineTable[0], 0, gCosineTable[0]);
    vec_normalize(upDir);

    vec_cross(leftDir, upDir, lateralDir);
    vec_normalize(leftDir);

    vec_cross(forwardDir, leftDir, upDir);
    vec_normalize(forwardDir);

    dest[0][0] = leftDir[0];
    dest[0][1] = leftDir[1];
    dest[0][2] = leftDir[2];
    dest[3][0] = pos[0];

    dest[1][0] = upDir[0];
    dest[1][1] = upDir[1];
    dest[1][2] = upDir[2];
    dest[3][1] = pos[1];

    dest[2][0] = forwardDir[0];
    dest[2][1] = forwardDir[1];
    dest[2][2] = forwardDir[2];
    dest[3][2] = pos[2];

    dest[0][3] = 0.0f;
    dest[1][3] = 0.0f;
    dest[2][3] = 0.0f;
    dest[3][3] = 1.0f;
}