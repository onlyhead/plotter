#define _USE_MATH_DEFINES
#include <cmath>
#include <plotter.hpp>

using namespace std;

// Example fill plot adapted for Concord Points
int main() {
    plotter::Plotter plt;

    // Prepare data using Concord Points
    vector<double> theta;
    for (double d = 0; d < 8 * M_PI; d += 0.1)
        theta.push_back(d);

    const int a = 1;
    const double b = 0.2;

    for (double dt = 0; dt < 2 * M_PI; dt += M_PI / 2.0) {
        vector<concord::Point> spiral_points1, spiral_points2, fill_points;

        for (double th : theta) {
            double x1 = a * cos(th + dt) * exp(b * th);
            double y1 = a * sin(th + dt) * exp(b * th);
            spiral_points1.emplace_back(x1, y1);

            double x2 = a * cos(th + dt + M_PI / 4.0) * exp(b * th);
            double y2 = a * sin(th + dt + M_PI / 4.0) * exp(b * th);
            spiral_points2.emplace_back(x2, y2);
        }

        // Combine points for fill operation
        fill_points = spiral_points1;
        for (auto it = spiral_points2.rbegin(); it != spiral_points2.rend(); ++it) {
            fill_points.push_back(*it);
        }

        // Fill the spiral shape with Pigment color
        plt.fill(fill_points, pigment::RGB::cyan());
    }

    plt.title("Spiral Fill with Concord Points");
    plt.show();
}
