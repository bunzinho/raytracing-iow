#include <iostream>
#include <fstream>

#include "rtweekend.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

color ray_color(const ray& r, const hittable& world)
{
	hit_record rec;
	if (world.hit(r, 0, infinity, rec))
	{
		return 0.5f * (rec.normal + color(1, 1, 1));
	}
	auto unit_direction = unit_vector(r.direction());
	auto t = 0.5f * (unit_direction.y() + 1.0f);
	return (1.0f - t) * color(1.0f, 1.0f, 1.0f) + t * color(0.5f, 0.7f, 1.0f);
}

int main(int argc, char* argv[])
{
	// Image

	const auto filename = "output.ppm";
	const auto aspect_ratio = 16.0f / 9.0f;
	const auto image_height = 360;
	const auto image_width = static_cast<int>(image_height * aspect_ratio);
	const int samples_per_pixel = 100;

	// World

	hittable_list world;
	world.add(make_shared<sphere>(vec3(0, 0, -1), 0.5f));
	world.add(make_shared<sphere>(vec3(0, -100.5f, -1), 100.0f));

	// Camera

	camera cam;

	// Render 

	auto ppmfile = std::ofstream(filename);
	ppmfile << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cerr << "\rlines remaining: " << j << ' ' << std::flush;

		for (int i = 0; i < image_width; ++i)
		{
			auto pixel_color = color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; s++)
			{
				auto u = (i + random_float()) / (image_width - 1);
				auto v = (j + random_float()) / (image_height - 1);
				auto r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world);
			}
			write_color(ppmfile, pixel_color, samples_per_pixel);
		}
		ppmfile << std::endl;
	}
}
