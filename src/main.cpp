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
    const vec3 unit_direction = unit_vector(r.direction());
    const double t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main(int argc, char* argv[])
{
	// Image

	constexpr auto filename	= "output.ppm";
	constexpr auto aspect_ratio = 16.0 / 9.0;
	constexpr int  image_height = 360;
	constexpr int  image_width = static_cast<int>(image_height * aspect_ratio);
	constexpr int  samples_per_pixel = 50;
    constexpr int  max_depth = 25;

	// World

	hittable_list world;
	
	auto mat_ground = make_shared<lambertian>(color(32.0/255, 80.0/255, 150.0/255));
	auto mat_center = make_shared<lambertian>(color(235.0/255, 70.0/255, 95.0/255));
	auto mat_left   = make_shared<metal>(color(0.7, 0.7, 0.7), 0.96);
	auto mat_right  = make_shared<metal>(color(255.0/255, 215.0/255, 88.0/255), 0.6);

	world.add(make_shared<sphere>(vec3(0.0, -100.5, -1.0), 100.0, mat_ground));
	world.add(make_shared<sphere>(vec3(0.0,	   0.0, -1.0),   0.5, mat_center));
	world.add(make_shared<sphere>(vec3(-1.1,   0.0, -1.0),   0.5, mat_left));
	world.add(make_shared<sphere>(vec3(1.1,    0.0, -1.0),   0.5, mat_right));

	// Camera

	camera cam;

	// Render 

	auto ppmfile = std::ofstream(filename, std::ios_base::out | std::ios_base::binary);
	if (ppmfile.fail())
	{
		std::cerr << "error : failed to open file " << filename << " for writing ";;
		return EXIT_FAILURE;
	}
	
	ppmfile << "P6 " << image_width << " " << image_height << " " << "255 ";
	
	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cerr << "\rlines remaining: " << j << ' ' << std::flush;

		for (int i = 0; i < image_width; ++i)
		{
			auto pixel_color = color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; s++)
			{
				const auto u = (i + random_double()) / static_cast<double>(image_width - 1);
				const auto v = (j + random_double()) / static_cast<double>(image_height - 1);
				const auto r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world, max_depth);
			}
			write_color(ppmfile, pixel_color, samples_per_pixel);
		}
	}
	return EXIT_SUCCESS;
}
