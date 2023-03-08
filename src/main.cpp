#include <iostream>
#include <fstream>

#include "rtweekend.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

color ray_color(const ray& r, const hittable& world, int depth)
{
    if (depth <= 0)
    {
        return color(0, 0, 0);
    }

	hit_record rec;

	if (world.hit(r, 0.001, infinity, rec))
	{
		ray scattered;
		color attenuation;
		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * ray_color(scattered, world, depth-1);
		}
		return color(0, 0, 0);
	}
	auto unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main(int argc, char* argv[])
{
	// Image

	const auto filename	= "output.ppm";
	const auto aspect_ratio = 16.0 / 9.0;
	const int  image_height = 360;
	const int  image_width = static_cast<int>(image_height * aspect_ratio);
	const int  samples_per_pixel = 40;
    const int  max_depth = 50;

	// World

	hittable_list world;
	
	auto mat_ground = make_shared<lambertian>(color(32.0/255, 80.0/255, 150.0/255));
	auto mat_center = make_shared<lambertian>(color(235.0/255, 70.0/255, 95.0/255));
	auto mat_left   = make_shared<metal>(color(0.8, 0.8, 0.8));
	auto mat_right  = make_shared<metal>(color(0.8, 0.6, 0.2));

	world.add(make_shared<sphere>(vec3(0.0, -100.5, -1.0), 100.0, mat_ground));
	world.add(make_shared<sphere>(vec3(0.0,	   0.0, -1.0),   0.5, mat_center));
	world.add(make_shared<sphere>(vec3(-1.0,   0.0, -1.0),   0.5, mat_left));
	world.add(make_shared<sphere>(vec3(1.0,    0.0, -1.0),   0.5, mat_right));

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
				auto u = (i + random_double()) / static_cast<double>(image_width - 1);
				auto v = (j + random_double()) / static_cast<double>(image_height - 1);
				auto r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world, max_depth);
			}
			write_color(ppmfile, pixel_color, samples_per_pixel);
		}
		ppmfile << std::endl;
	}
}
