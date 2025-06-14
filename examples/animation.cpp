#define _USE_MATH_DEFINES
#include <cmath>
#include <plotter/plotter.hpp>

using namespace plotter;

int main() {
    int n = 1000;
    std::vector<double> x, y, z;

    for (int i = 0; i < n; i++) {
        x.push_back(i * i);
        y.push_back(sin(2 * M_PI * i / 360.0));
        z.push_back(log(i));

        if (i % 10 == 0) {
            // Clear previous plot
            clf();
            // Plot line from given x and y data. Color is selected automatically.
            plot(x, y);
            // Plot a line whose name will show up as "log(x)" in the legend.
            named_plot("log(x)", x, z);

            // Set x-axis to interval [0,1000000]
            xlim(0, n * n);

            // Add graph title
            title("Sample figure");
            // Enable legend.
            legend();
            // Display plot continuously
            pause(0.01);
        }
    }
}
