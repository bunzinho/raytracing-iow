#include <iostream>
#include <fstream>

#include "rtweekend.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

color ray_color(const ray& r, const hittable& world, int max_depth)
{
    if (max_depth <= 0)
    {
        return color(0,0,0);
    }

	hit_record rec;

	if (world.hit(r, 0.001, infinity, rec))
	{
        vec3 target = rec.p + rec.normal + random_unit_vector();
		return 0.5 * ray_color(ray(rec.p, target - rec.p), world, max_depth-1);
	}
	auto unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main(int argc, char* argv[])
{
	// Image

	const auto filename = "output.ppm";
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_height = 720;
	const int image_width = static_cast<int>(image_height * aspect_ratio);
	const int samples_per_pixel = 100;
    const int max_depth = 50;

	// World

	hittable_list world;
	world.add(make_shared<sphere>(vec3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(vec3(0, -100.5, -1), 100.0));

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
				auto u = (i + random_double()) / (image_width - 1);
				auto v = (j + random_double()) / (image_height - 1);
				auto r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world, max_depth);
			}
			write_color(ppmfile, pixel_color, samples_per_pixel);
		}
		ppmfile << std::endl;
	}
}
