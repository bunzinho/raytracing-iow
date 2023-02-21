#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
	auto ppmfile = std::ofstream("output.ppm");
	
	const int image_width = 256;
	const int image_height = 256;

	ppmfile << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cerr << "\rlines remaining: " << j << ' ' << std::flush;

		for (int i = 0; i < image_width; ++i)
		{
			auto r = static_cast<double>(i) / (image_width - 1);
			auto g = static_cast<double>(j) / (image_height - 1);
			auto b = 0.25;

			int ir = static_cast<int>(255.999 * r);
			int ig = static_cast<int>(255.999 * g);
			int ib = static_cast<int>(255.999 * b);

			ppmfile << ir << ' ' << ig << ' ' << ib << ' ';
		}
		ppmfile << std::endl;
	}
}
