#include <iostream>
#include <plotter.hpp>

int main() {
    // Create a plotter instance
    plotter::Plotter plt;

    // Create points using Concord - only x and y needed, z defaults to 0
    std::vector<concord::Point> points;
    points.emplace_back(1, 2); // Point(1, 2, 0) - z automatically set to 0
    points.emplace_back(2, 4); // Point(2, 4, 0)
    points.emplace_back(3, 1); // Point(3, 1, 0)
    points.emplace_back(4, 3); // Point(4, 3, 0)

    // Plot with automatic color
    plt.plot(points);

    // Create more points for scatter plot
    std::vector<concord::Point> scatter_points;
    scatter_points.emplace_back(1.5, 3);
    scatter_points.emplace_back(2.5, 2);
    scatter_points.emplace_back(3.5, 4);

    // Scatter plot with Pigment color
    plt.scatter(scatter_points, pigment::RGB::red());

    // Add title
    plt.title("Simple Concord Points Example");

    // Save the plot
    plt.save("simple_concord_example.png");

    std::cout << "Plot saved to simple_concord_example.png" << std::endl;
    return 0;
}
