#include <iostream>
#include <fstream>

#include "rtweekend.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"

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
	const auto image_height = 400;
	const auto image_width = static_cast<int>(image_height * aspect_ratio);

	// World

	hittable_list world;
	world.add(make_shared<sphere>(vec3(0, 0, -1), 0.5f));
	world.add(make_shared<sphere>(vec3(0, -100.5f, -1), 100.0f));

	// Camera

	const auto viewport_height = 2.0f;
	const auto viewport_width = aspect_ratio * viewport_height;
	const auto focal_length = 1.0f;

	auto origin = vec3(0, 0, 0);
	auto horizontal = vec3(viewport_width, 0, 0);
	auto vertical = vec3(0, viewport_height, 0);
	auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

	// Render 

	auto ppmfile = std::ofstream(filename);
	ppmfile << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cerr << "\rlines remaining: " << j << ' ' << std::flush;

		for (int i = 0; i < image_width; ++i)
		{
			auto u = float(i) / (image_width - 1);
			auto v = float(j) / (image_height - 1);
			ray r = ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);

			auto pixel_color = ray_color(r, world);
			write_color(ppmfile, pixel_color);
		}
		ppmfile << std::endl;
	}
}
