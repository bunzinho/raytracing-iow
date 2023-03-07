#pragma once

#include <iostream>
#include "vec3.h"

void write_color(std::ostream& out, color pixel_color, int samples_per_pixel)
{
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	// Divide the color by the number of samples.
	auto scale = 1.0 / samples_per_pixel;
	r = sqrt(r * scale);
	g = sqrt(g * scale);
	b = sqrt(b * scale);

	out << static_cast<int>(std::round(255.0 * clamp(r, 0.0, 1.0))) << ' '
		<< static_cast<int>(std::round(255.0 * clamp(g, 0.0, 1.0))) << ' '
		<< static_cast<int>(std::round(255.0 * clamp(b, 0.0, 1.0))) << ' ';
}
