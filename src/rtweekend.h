#pragma once

#include <cmath>
#include <limits>
#include <memory>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

constexpr float infinity = std::numeric_limits<float>::infinity();
constexpr float pi = 3.14159265358979323846;

constexpr inline float degrees_to_radians(float degrees)
{
	return degrees * pi / 180.0f;
}

#include "ray.h"
#include "vec3.h"
