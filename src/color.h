#pragma once

#include <iostream>
#include "vec3.h"

void write_color(std::ostream& out, color pixel_color, int samples_per_pixel)
{
	// Divide the color by the number of samples.
	const auto scale = 1.0 / samples_per_pixel;
	const auto r = sqrt(pixel_color.x() * scale);
	const auto g = sqrt(pixel_color.y() * scale);
	const auto b = sqrt(pixel_color.z() * scale);
	
	out << static_cast<uint8_t>(std::round(255 * clamp(r, 0.0, 1.0)))
		<< static_cast<uint8_t>(std::round(255 * clamp(g, 0.0, 1.0)))
		<< static_cast<uint8_t>(std::round(255 * clamp(b, 0.0, 1.0)));
}
