#define _USE_MATH_DEFINES

#include <iostream>
#include <plotter.hpp>
#include <string>

int main(int argc, char **argv) {
    plotter::Plotter plt;

    // Create bar chart data using Concord Points
    std::vector<concord::Point> bar_points;
    for (int i = 0; i < 20; i++) {
        bar_points.emplace_back(i, i); // x position, y height
    }

    plt.bar(bar_points, pigment::RGB::blue());
    plt.show();

    return (0);
}
