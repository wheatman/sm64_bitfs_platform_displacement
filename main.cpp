#include "Mario.h"
#include "Magic.h"
#include "Platform.h"
#include "vmath.h"
#include <cmath>
#include <mutex>
#include <immintrin.h>

#ifdef _OPENMP
#include <omp.h> // This line won't add the library if you don't compile with -fopenmp option.
#ifdef _MSC_VER
// For Microsoft compiler
#define OMP_FOR __pragma(omp parallel for)
#else // assuming "__GNUC__" is defined
// For GCC compiler
#define OMP_FOR _Pragma("omp parallel for")

#endif
#else
#define omp_get_max_threads() 1
#define OMP_FOR

#endif

static std::mutex print_mutex;

using namespace std;

void brute_angles(Platform* plat, const Vec3f& m_pos, const float spd, const Vec3f & normals, const Mat4& trans) {
	//iterate over hau instead of sticks
#ifdef __AVX2__
	const __m256  m_pos_vector = _mm256_set1_ps(m_pos[0]);
	const __m256 normal_vector = _mm256_set1_ps(normals[1]);
	const __m256 speed_vector = _mm256_set1_ps(spd / 4.0f);
	const __m256 speed_x_normal = _mm256_mul_ps(normal_vector, speed_vector);
#endif
	for (int hau1 = 0; hau1 < 65535; hau1 += 128) {
#ifdef __AVX2__
		__m256 sin_vector = _mm256_loadu_ps(gSineTable.data() + (hau1 >> 4));
		__m256 float_check = _mm256_fmadd_ps(speed_x_normal, sin_vector, m_pos_vector);
		__m256i int_check = _mm256_cvttps_epi32(float_check);
		__m256i abs_vector = _mm256_abs_epi32(int_check);
		__m256i cmp_vector = _mm256_cmpgt_epi16(abs_vector, _mm256_set1_epi16(8192));
		uint32_t mask = _mm256_movemask_epi8(cmp_vector);
		// bool skip = false;
		
		if ((mask & 0x33333333U) == 0x33333333U) {
			continue;
			// skip = true;
		}
#endif
		for (int hau = hau1; hau < hau1+128; hau += 16) {
#ifdef __AVX2__
			// bool skip1 = false;
			if ((mask & 0x3) == 0x3) {
				// skip1 = true;
				mask >>= 4;
				continue;
			}
			mask >>= 4;
#else

			if (abs((short)(int)(m_pos[0] + gSineTable[hau >> 4] * normals[1] * (spd / 4.0f))) >= 8192) {
#ifdef __AVX2__
				// there are many times they we don't skip when we could
				// if (!skip) {
				// 		printf("issue skiped, %d\n", abs((short)(int)(m_pos[0] + gSineTable[hau >> 4] * normals[1] * (spd / 4.0f))));
				// }
				// if (!skip1) {
				// 		printf("issue skiped 1, %d\n", abs((short)(int)(m_pos[0] + gSineTable[hau >> 4] * normals[1] * (spd / 4.0f))));
				// }
#endif
				continue;
			}
#endif

#ifdef __AVX2__
			// no times we skip when we shouldn't
			// if (skip) {
			// 		printf("issue didn't skip, %d\n", abs((short)(int)(m_pos[0] + gSineTable[hau >> 4] * normals[1] * (spd / 4.0f))));
			// }
			// if (skip1) {
			// 		printf("issue didn't skip 1, %d\n", abs((short)(int)(m_pos[0] + gSineTable[hau >> 4] * normals[1] * (spd / 4.0f))));
			// }
#endif
			Mario mario(m_pos, spd);

			if (mario.ground_step(hau, normals[1]) == 0) { continue; }

			plat->normal = normals;
		

			if (!plat->find_floor(&mario)) { continue; }

			plat->platform_logic(&mario);
			plat->transform = trans;

			if (!check_inbounds(mario)) { continue; }

			if (mario.pos[1] >= 3521 && mario.pos[1] < 8192) {
				print_mutex.lock();
				if (mario.pos[1] <= 3841) {
					printf("-------------------\nIDEAL SOLN\nBully spd: %f\nHau: %d\nPlatform normals: (%.9f, %.9f, %.9f)\nMario pos: (%.9f, %.9f, %.9f)\nMario start: (%.9f, %.9f, %.9f)\n",
						mario.speed, hau, normals[0], normals[1], normals[2], mario.pos[0], mario.pos[1], mario.pos[2], m_pos[0], m_pos[1], m_pos[2]);
					//printf("Triangle points\n");
					//plat->triangles[0].repr();
					//plat->triangles[1].repr();
				}
				else {
					printf("-------------------\nACCEPTABLE SOLN\nBully spd: %f\nHau: %d\nPlatform normals: (%.9f, %.9f, %.9f)\nMario pos: (%.9f, %.9f, %.9f)\nMario start: (%.9f, %.9f, %.9f)\n",
						mario.speed, hau, normals[0], normals[1], normals[2], mario.pos[0], mario.pos[1], mario.pos[2], m_pos[0], m_pos[1], m_pos[2]);
					//printf("Triangle points\n");
					//plat->triangles[0].repr();
					//plat->triangles[1].repr();
				}
				print_mutex.unlock();
			}
		}
	}

	/*
	for (int16_t x = -128; x < 128; x++) {
		for (int16_t y = -128; y < 128; y++) {
			m->pos = m_pos;
			m->speed = spd;

			plat->normal = normals;

			yawmag = calc_intended_yawmag(x, y);
			int16_t intYaw = yawmag.first - (yawmag.first % 16);

			if (m->ground_step(x, y, plat->normal[1]) == 0) { continue; }

			plat->platform_logic(m);

			if (!check_inbounds(*m)) { continue; }

			if (m->pos[1] >= 3521) {
				if (m->pos[1] <= 3841) {
					printf("-------------------\nIDEAL SOLN\nBully spd: %f\nStick X: %d\nStick Y: %d\nPlatform normals: (%.9f, %.9f, %.9f)\nMario pos: (%.9f, %.9f, %.9f)\nMario start: (%.9f, %.9f, %.9f)\n",
						m->speed, x, y, normals[0], normals[1], normals[2], m->pos[0], m->pos[1], m->pos[2], m_pos[0], m_pos[1], m_pos[2]);
				}
				else if (m->pos[1] < 8192) {
					printf("-------------------\nACCEPTABLE SOLN\nBully spd: %f\nStick X: %d\nStick Y: %d\nPlatform normals: (%.9f, %.9f, %.9f)\nMario pos: (%.9f, %.9f, %.9f)\nMario start: (%.9f, %.9f, %.9f)\n",
						m->speed, x, y, normals[0], normals[1], normals[2], m->pos[0], m->pos[1], m->pos[2], m_pos[0], m_pos[1], m_pos[2]);
				}
			}
		}
	}*/
}

void brute_position(Platform* plat, float spd, const Vec3f& normals) {
	plat->normal[0] = 0;
	plat->normal[1] = 1;
	plat->normal[2] = 0;
	plat->create_transform_from_normals();

	Mat4 old_mat = plat->transform;

	plat->normal = normals;

	plat->create_transform_from_normals();
	plat->triangles[0].rotate(plat->pos, old_mat, plat->transform);
	plat->triangles[1].rotate(plat->pos, old_mat, plat->transform);

	const Mat4& trans = plat->transform;
	const Vec2S& tri = plat->triangles;

	float max_x = max(plat->triangles[1].vector1[0], plat->triangles[1].vector3[0]);
	float min_x = min(plat->triangles[1].vector1[0], plat->triangles[1].vector3[0]);

	for (float x = plat->triangles[1].vector2[0]; x <= min_x; x += 20) {
		float y1 = line_point(plat->triangles[1].vector2, plat->triangles[1].vector1, x, true);
		float z1 = line_point(plat->triangles[1].vector2, plat->triangles[1].vector1, x, false);

		float y2 = line_point(plat->triangles[1].vector2, plat->triangles[1].vector3, x, true);
		float z2 = line_point(plat->triangles[1].vector2, plat->triangles[1].vector3, x, false);

		float min_z = min(z1, z2);
		float max_z = max(z1, z2);

		if (max_z - min_z == 0) {
			if (y1 <= -3071) { continue; }
		}
		/*
		//(-3071 + min_y) / (max_y - min_y) * (max_z - min_z) + min_z;

		float check_min, check_max;

		if (min_z == z1) {
			check_min = max(min_z, (-3071 + y1) / (y2 - y1) * (max_z - min_z) + min_z);
			check_max = min(max_z, (-3071 + y2) / (y1 - y2) * (max_z - min_z) + min_z);
		}
		else {
			check_min = max(min_z, (-3071 + y2) / (y1 - y2) * (max_z - min_z) + min_z);
			check_max = min(max_z, (-3071 + y1) / (y2 - y1) * (max_z - min_z) + min_z);
		}

		float temp1 = min_z;
		float temp2 = max_z;

		if (check_min <= temp2) { min_z = check_min; }
		if (check_max >= temp1) { max_z = check_max; }*/

		for (float z = min_z; z <= max_z; z += 20) {
			float y;

			if (min_z == z1) {
				if (z2 - z1 == 0) {
					y = y1;
				}
				else {
					y = (y2 - y1) / (z2 - z1) * (z - z1) + y1;
				}
			}
			else {
				if (z1 - z2 == 0) {
					y = y2;
				}
				else {
					y = (y1 - y2) / (z1 - z2) * (z - z2) + y2;
				}
			}

			if (y <= -3071) { continue; }

			brute_angles(plat, { x, y, z }, spd, normals, trans);
			//fprintf(stderr, "finished all angles for position %.9f, %.9f, %.9f\n", x, y, z);

			//plat->transform = trans;
			plat->triangles = tri;
			plat->normal = normals;
		}
	}

	Vec3s max_vector;
	Vec3s min_vector;

	if (min_x == plat->triangles[1].vector1[0]) {
		min_vector = plat->triangles[1].vector1;
		max_vector = plat->triangles[1].vector3;
	}
	else {
		min_vector = plat->triangles[1].vector3;
		max_vector = plat->triangles[1].vector1;
	}

	for (float x = min_x; x <= max_x; x += 20) {
		float y1 = line_point(plat->triangles[1].vector2, max_vector, x, true);
		float z1 = line_point(plat->triangles[1].vector2, max_vector, x, false);

		float y2 = line_point(min_vector, max_vector, x, true);
		float z2 = line_point(min_vector, max_vector, x, false);

		float min_z = min(z1, z2);
		float max_z = max(z1, z2);

		if (max_z - min_z == 0) {
			if (y1 <= -3071) { continue; }
		}

		for (float z = min_z; z <= max_z; z += 20) {
			float y;

			if (min_z == z1) {
				if (z2 - z1 == 0) {
					y = y1;
				}
				else {
					y = (y2 - y1) / (z2 - z1) * (z - z1) + y1;
				}
			}
			else {
				if (z1 - z2 == 0) {
					y = y2;
				}
				else {
					y = (y1 - y2) / (z1 - z2) * (z - z2) + y2;
				}
			}

			if (y <= -3071) { continue; }

			brute_angles(plat, { x, y, z }, spd, normals, trans);
			//fprintf(stderr, "finished all angles for position %.9f, %.9f, %.9f\n", x, y, z);

			//plat->transform = trans;
			plat->triangles = tri;
			plat->normal = normals;
		}
	}
}

void brute_normals(float spd) {

    float starting_normal = -0.5f;
    float ending_normal = 0.5f;
    float per_worker = (ending_normal - starting_normal) / omp_get_max_threads();
    vector<float> normals(omp_get_max_threads() + 1);
    for (int i = 0; i < omp_get_max_threads(); i++) {
        normals[i] = starting_normal + i * per_worker;
    }
    normals[omp_get_max_threads()] = ending_normal;

    OMP_FOR
    for (int i = 0; i < omp_get_max_threads(); i++) {
        Platform p;

        Vec2S tri = p.triangles;

	    for (float nx = normals[i]; nx <= normals[i+1]; nx = nextafterf(nx, 2.0f)) {
		    float limit = max(powf(nx, 2) - 1.0f, -0.5f);

   		    for (float nz = nextafterf(limit, 1.0f); nz < limit * -1; nz = nextafterf(nz, 1.0f)) {
			    float ny = sqrtf(1 - powf(nx, 2) - powf(nz, 2));

  			    brute_position(&p, spd, {nx, ny, nz});

			    fprintf(stderr, "Finished all positions for %.9f, %.9f, %.9f\n", nx, ny,
				      	nz);

			    p.triangles = tri;
			}
		}
	}
}

void brute_speed() {
    float spd = 58000000.0f;
    float ending_spd = 1000000000.0;

    while (spd < ending_spd) {
        brute_normals(spd);

        spd = nextafterf(spd, 2000000000.0f);
        fprintf(stderr, "Finished all loops for speed %.9f\n", spd);
    }
}

int main() {
	brute_speed();
}