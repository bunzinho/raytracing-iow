#pragma once

#include <iostream>
#include "vec3.h"

void write_color(std::ostream& out, color pixel_color, int samples_per_pixel)
{
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	// Divide the color by the number of samples.
	auto scale = 1.0f / samples_per_pixel;
	r *= scale;
	g *= scale;
	b *= scale;

	out << static_cast<int>(std::round(255.0f * clamp(r, 0.0f, 1.0f))) << ' '
		<< static_cast<int>(std::round(255.0f * clamp(g, 0.0f, 1.0f))) << ' '
		<< static_cast<int>(std::round(255.0f * clamp(b, 0.0f, 1.0f))) << ' ';
}
