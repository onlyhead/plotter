#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <plotter.hpp>

int main() {
    // Create a plotter instance
    plotter::Plotter plt;

    // Prepare data using Concord Points
    int n = 50; // Reduced for cleaner output
    std::vector<concord::Point> sine_points, square_points, log_points;

    for (int i = 1; i < n; ++i) { // Start from 1 to avoid log(0)
        double x = i * i;
        double y = sin(2 * M_PI * i / 360.0);
        double z = log(i);

        sine_points.emplace_back(x, y);     // z defaults to 0
        square_points.emplace_back(x, 2.0); // Constant value
        log_points.emplace_back(x, z);
    }

    // Set the size of output image = 1200x780 pixels
    plt.figure_size(1200, 780);

    // Plot line from Concord points. Color is selected automatically.
    plt.plot(sine_points);

    // Plot a red dashed line from Concord points
    plt.plot(square_points, "r--");

    // Plot with Pigment green color
    plt.plot(log_points, pigment::RGB::green());

    // Set x-axis to interval [0,1000000]
    plt.xlim(0, 1000 * 1000);

    // Add graph title
    plt.title("Sample figure with Concord Points");

    // Enable legend.
    plt.legend();

    // save figure
    const char *filename = "./basic.png";
    std::cout << "Saving result to " << filename << std::endl;
    plt.save(filename);
}
