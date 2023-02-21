#include <iostream>
#include <fstream>

#include "color.h"
#include "vec3.h"

int main(int argc, char *argv[])
{
	auto ppmfile = std::ofstream("output.ppm");
	
	const auto aspect_ratio = 16.0 / 9.0;
	const auto image_height = 400;
	const int image_width = static_cast<int>(image_height * aspect_ratio);

	ppmfile << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cerr << "\rlines remaining: " << j << ' ' << std::flush;

		for (int i = 0; i < image_width; ++i)
		{
			auto r = static_cast<float>(i) / (image_width);
			auto g = static_cast<float>(j) / (image_height);
			auto b = 0.25f;

			auto pixel_color = color(r, g, b);
			write_color(ppmfile, pixel_color);
		}
		ppmfile << std::endl;
	}
}
