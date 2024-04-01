#include <iostream>
#include <fstream>

#include "vec3.h"
#include "color.h"
#include "ray.h"


color ray_color(const ray& r) {
	return color(0, 0, 0);
}


int main()
{
	// image
	double aspect_ratio = 16.0 / 9.0;
	int image_width = 400;

	// compute image heigth, ensure it is at least 1
	int image_height = static_cast<int>(image_width / aspect_ratio);
	image_height = (image_height < 1) ? 1 : image_height;

	// camera
	double focal_length = 1.0;
	double viewport_height = 2.0;
	double viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);
	point3 camera_center = point3(0, 0, 0);

	// compute the vectors across the horizontal and down the vertical viewport edges.
	vec3 viewport_u = vec3(viewport_width, 0, 0);
	vec3 viewport_v = vec3(0, -viewport_height, 0);

	// compute the horizontal and vertical delta vectors from pixel to pixel.
	vec3 pixel_delta_u = viewport_u / image_width;
	vec3 pixel_delta_v = viewport_v / image_height;

	// compute the location of the upper left pixel.
	vec3 viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
	vec3 pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);


	// open file for writing
	std::ofstream outputFile("output.ppm");

	// check if file opened successfully
	if (!outputFile.is_open()) {
		std::cerr << "Error: Could not open file.\n";
		return 1;
	}

	// rendering
	outputFile << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = 0; j < image_height; j++) {

		std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;

		for (int i = 0; i < image_height; i++) {
			vec3 pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
			vec3 ray_direction = pixel_center - camera_center;
			ray r(camera_center, ray_direction);

			color pixel_color = ray_color(r);
			write_color(outputFile, pixel_color);
		}
	}

	std::clog << "\nDone.\n";
}
