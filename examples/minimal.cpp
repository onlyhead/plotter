#include <plotter.hpp>

int main() {
    plotter::Plotter plt;

    // Create points using Concord Points
    std::vector<concord::Point> points;
    points.emplace_back(0, 1); // z defaults to 0
    points.emplace_back(1, 3);
    points.emplace_back(2, 2);
    points.emplace_back(3, 4);

    plt.plot(points);
    plt.save("minimal.png");
}
