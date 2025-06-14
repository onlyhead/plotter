#define _USE_MATH_DEFINES
#include <cmath>
#include <plotter/plotter.hpp>

using namespace plotter;
using namespace std;

int main() {
    // Prepare data.
    int n = 5000;
    std::vector<double> x(n), y(n), z(n), w(n, 2);
    for (int i = 0; i < n; ++i) {
        x.at(i) = i * i;
        y.at(i) = sin(2 * M_PI * i / 360.0);
        z.at(i) = log(i);
    }

    // Plot line from given x and y data. Color is selected automatically.
    subplot(2, 2, 1);
    plot(x, y);

    // Plot a red dashed line from given x and y data.
    subplot(2, 2, 2);
    plot(x, w, "r--");

    // Plot a line whose name will show up as "log(x)" in the legend.
    subplot(2, 2, 3);
    named_plot("log(x)", x, z);

    // Set x-axis to interval [0,1000000]
    xlim(0, 1000 * 1000);

    // Add graph title
    title("Sample figure");
    // Enable legend.
    legend();

    show(false);

    cout << "plotter::show() is working in an non-blocking mode" << endl;
    getchar();
    return 0;
}
