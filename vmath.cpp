#include "vmath.h"
#include <cmath>

/**
 * Multiply a vector by a matrix of the form
 * | ? ? ? 0 |
 * | ? ? ? 0 |
 * | ? ? ? 0 |
 * | 0 0 0 1 |
 * i.e. a matrix representing a linear transformation over 3 space.
 */
vector<float> linear_mtxf_mul_vec3f(vector<vector<float>> m, vector<float> v) {
    vector<float> dst(3, 0);

    int32_t i;
    for (i = 0; i < 3; i++) {
        dst[i] = m[0][i] * v[0] + m[1][i] * v[1] + m[2][i] * v[2];
    }

    return dst;
}

/// Set vector 'dest' to (x, y, z)
vector<float> vec_set(float x, float y, float z) {
    vector<float> dest(3, 0);

    dest[0] = x;
    dest[1] = y;
    dest[2] = z;

    return dest;
}

/// Make vector 'dest' the cross product of vectors a and b.
vector<float> vec_cross(vector<float> a, vector<float> b) {
    vector<float> dest(3, 0);

    dest[0] = a[1] * b[2] - b[1] * a[2];
    dest[1] = a[2] * b[0] - b[2] * a[0];
    dest[2] = a[0] * b[1] - b[0] * a[1];

    return dest;
}

/// Scale vector 'dest' so it has length 1
vector<float> vec_normalize(vector<float> dest) {
    vector<float> out(3, 0);
    //! Possible division by zero
    float invsqrt = 1.0f / sqrtf(dest[0] * dest[0] + dest[1] * dest[1] + dest[2] * dest[2]);

    out[0] = dest[0] * invsqrt;
    out[1] = dest[1] * invsqrt;
    out[2] = dest[2] * invsqrt;

    return out;
}

/**
 * Set 'dest' to a transformation matrix that aligns an object with the terrain
 * based on the normal. Used for enemies.
 * 'upDir' is the terrain normal
 * 'yaw' is the angle which it should face
 * 'pos' is the object's position in the world
 */
vector<vector<float>> align_normal(vector<float> upDir, vector<float> pos) {
    vector<vector<float>> dest = { {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0} };

    vector<float> lateralDir(3, 0);
    vector<float> leftDir(3, 0);
    vector<float> forwardDir(3, 0);
    vector<float> normal(3, 0);

    lateralDir = vec_set(gSineTable[0], 0, gCosineTable[0]);
    normal = vec_normalize(upDir);

    leftDir = vec_cross(normal, lateralDir);
    leftDir = vec_normalize(leftDir);

    forwardDir = vec_cross(leftDir, normal);
    forwardDir = vec_normalize(forwardDir);

    dest[0][0] = leftDir[0];
    dest[0][1] = leftDir[1];
    dest[0][2] = leftDir[2];
    dest[3][0] = pos[0];

    dest[1][0] = normal[0];
    dest[1][1] = normal[1];
    dest[1][2] = normal[2];
    dest[3][1] = pos[1];

    dest[2][0] = forwardDir[0];
    dest[2][1] = forwardDir[1];
    dest[2][2] = forwardDir[2];
    dest[3][2] = pos[2];

    dest[0][3] = 0.0f;
    dest[1][3] = 0.0f;
    dest[2][3] = 0.0f;
    dest[3][3] = 1.0f;

    return dest;
}