#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <plotter.hpp>

int main() {
    // Create a plotter instance
    plotter::Plotter plt;

    // Create data using Concord Points
    // Note: Concord Points can be created with just x and y, z defaults to 0
    std::vector<concord::Point> points;

    int n = 50;
    for (int i = 0; i < n; ++i) {
        double x = i * 0.1;
        double y = sin(2 * M_PI * x);
        // z automatically defaults to 0.0
        points.emplace_back(x, y);
    }

    // Set the size of output image = 1200x780 pixels
    plt.figure_size(1200, 780);

    // Plot line using Concord points with automatic color
    plt.plot(points);

    // Create more points for a second series
    std::vector<concord::Point> points2;
    for (int i = 0; i < n; ++i) {
        double x = i * 0.1;
        double y = cos(2 * M_PI * x);
        points2.emplace_back(x, y); // z defaults to 0
    }

    // Plot with specific Pigment color
    plt.plot(points2, pigment::RGB::red());

    // Create scatter plot points
    std::vector<concord::Point> scatter_points;
    for (int i = 0; i < 20; ++i) {
        double x = i * 0.25;
        double y = x * x * 0.1;
        scatter_points.emplace_back(x, y);
    }

    // Scatter plot with Pigment color and size
    plt.scatter(scatter_points, 50.0, pigment::RGB::green());

    // Create bar chart data
    std::vector<concord::Point> bar_points;
    for (int i = 0; i < 10; ++i) {
        double x = i;            // Position
        double y = (i + 1) * 10; // Height
        bar_points.emplace_back(x, y);
    }

    // Bar plot with Pigment color
    plt.bar(bar_points, pigment::RGB::blue());

    // Set axis limits
    plt.xlim(0, 5);
    plt.ylim(-2, 2);

    // Add labels and title
    plt.title("Concord Points and Pigment Colors Demo");
    plt.xlabel("X Coordinate");
    plt.ylabel("Y Coordinate");

    // Enable legend
    plt.legend();

    // Save figure
    const char *filename = "./concord_points_demo.png";
    std::cout << "Saving result to " << filename << std::endl;
    plt.save(filename);

    return 0;
}
