#include <cmath>
#include <plotter.hpp>

int main() {
    // This example shows the clean public API
    // Users only need to include <plotter.hpp>

    plotter::Plotter plt;

    // Basic plotting using Concord Points
    std::vector<concord::Point> basic_points;
    std::vector<double> x = {0, 1, 2, 3, 4};
    std::vector<double> y = {0, 1, 4, 9, 16};
    for (size_t i = 0; i < x.size(); ++i) {
        basic_points.emplace_back(x[i], y[i]);
    }
    plt.plot(basic_points);

    // Concord and Pigment integration
    std::vector<concord::Point> points;
    for (int i = 0; i <= 20; ++i) {
        double t = i * M_PI / 10.0;
        points.emplace_back(t, std::sin(t), 0.0);
    }

    plt.plot(points, pigment::RGB::red());
    plt.plot_circle(M_PI, 0.5, 0.2, pigment::RGB::blue());

    plt.title("Clean Public API Demo");
    plt.xlabel("X");
    plt.ylabel("Y");

    std::cout << "Public API demo completed successfully!" << std::endl;
    std::cout << "Library version: " << plotter::version() << std::endl;

    return 0;
}
