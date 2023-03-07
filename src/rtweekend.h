#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

constexpr float infinity = std::numeric_limits<float>::infinity();
constexpr float pi = 3.14159265358979323846f;

constexpr inline float degrees_to_radians(float degrees)
{
	return degrees * pi / 180.0f;
}

inline float random_float()
{
	return rand() / (RAND_MAX + 1.0f);
}

inline float random_float(float min, float max)
{
	return min + (max - min) * random_float();
}

#include "ray.h"
#include "vec3.h"
