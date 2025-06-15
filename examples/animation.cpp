#define _USE_MATH_DEFINES
#include <cmath>
#include <plotter.hpp>

int main() {
    plotter::Plotter plt;
    int n = 100; // Reduced for better performance
    std::vector<concord::Point> sine_points, log_points;

    for (int i = 1; i < n; i++) { // Start from 1 to avoid log(0)
        double x_val = i * i;
        double y_val = sin(2 * M_PI * i / 360.0);
        double z_val = log(i);

        sine_points.emplace_back(x_val, y_val);
        log_points.emplace_back(x_val, z_val);

        if (i % 10 == 0) {
            // Clear previous plot
            plt.clf();

            // Plot line using Concord points
            plt.plot(sine_points, pigment::RGB::blue());
            plt.plot(log_points, pigment::RGB::red());

            // Set x-axis to interval [0,1000000]
            plt.xlim(0, n * n);

            // Add graph title
            plt.title("Animation with Concord Points");

            // Enable legend
            plt.legend();

            // Pause for animation effect
            // Display plot continuously (pause function might need to be added to Plotter class)
            // plt.pause(0.01);
        }
    }

    plt.save("animation_final.png");
    return 0;
}
