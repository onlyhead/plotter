#define _USE_MATH_DEFINES
#include <cmath>
#include <plotter.hpp>

using namespace std;

int main() {
    plotter::Plotter plt;

    // Prepare data for parametric plot using Concord Points
    int n = 500; // reduced for cleaner output
    vector<concord::Point> heart_points;

    for (int i = 0; i < n; ++i) {
        double t = 2 * M_PI * i / n;
        double x = 16 * sin(t) * sin(t) * sin(t);
        double y = 13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t);
        heart_points.emplace_back(x, y); // z defaults to 0
    }

    // Plot with red color using Pigment
    plt.plot(heart_points, pigment::RGB::red());

    // Set aspect ratio - these functions might need to be added to the class
    // plt.set_aspect_equal();

    plt.title("Parametric Heart Shape");
    plt.show();
    return 0;
}
