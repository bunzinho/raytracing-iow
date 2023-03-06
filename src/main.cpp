#include <iostream>
#include <fstream>

#include "color.h"
#include "ray.h"
#include "vec3.h"

bool hit_sphere(const vec3& center, const float radius, const ray& r)
{
	auto oc = r.origin() - center;
	auto a = dot(r.direction(), r.direction());
	auto b = 2 * dot(oc, r.direction());
	auto c = dot(oc, oc) - radius * radius;
	auto discriminant = b*b - 4*a*c;
	return (discriminant > 0);
}

color ray_color(const ray& r)
{
	if (hit_sphere(vec3(0, 0, -1), 0.5, r))
	{
		return color(1, 0, 0);
	}
	auto unit_direction = unit_vector(r.direction());
	auto t = 0.5f * (unit_direction.y() + 1.0f);
	return (1.0f - t) * color(1.0f, 1.0f, 1.0f) + t * color(0.5f, 0.7f, 1.0f);
}

int main(int argc, char *argv[])
{
	// Image

	const auto filename = "output.ppm";
	const auto aspect_ratio = 16.0f / 9.0f;
	const auto image_height = 400;
	const auto image_width = static_cast<int>(image_height * aspect_ratio);

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

			auto pixel_color = ray_color(r);
			write_color(ppmfile, pixel_color);
		}
		ppmfile << std::endl;
	}
}
