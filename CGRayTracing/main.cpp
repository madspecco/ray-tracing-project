#include <iostream>
#include <fstream>


int main()
{
	// image
	int image_width = 256;
	int image_height = 256;

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
			double r = double(i) / (image_width - 1);
			double g = double(j) / (image_height - 1);
			double b = 0;

			int ir = static_cast<int>(255.99 * r);
			int ig = static_cast<int>(255.99 * g);
			int ib = static_cast<int>(255.99 * b);

			outputFile << ir << ' ' << ig << ' ' << ib << '\n';
		}
	}

	std::clog << "\nDone.\n";
}
