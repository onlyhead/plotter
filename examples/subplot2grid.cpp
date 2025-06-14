#define _USE_MATH_DEFINES
#include <cmath>
#include <plotter/plotter.hpp>

using namespace std;
using namespace plotter;

int main() {
    // Prepare data
    int n = 500;
    std::vector<double> x(n), u(n), v(n), w(n);
    for (int i = 0; i < n; ++i) {
        x.at(i) = i;
        u.at(i) = sin(2 * M_PI * i / 500.0);
        v.at(i) = 100.0 / i;
        w.at(i) = sin(2 * M_PI * i / 1000.0);
    }

    // Set the "super title"
    suptitle("My plot");

    const long nrows = 3, ncols = 3;
    long row = 2, col = 2;

    subplot2grid(nrows, ncols, row, col);
    plot(x, w, "g-");

    long spanr = 1, spanc = 2;
    col = 0;
    subplot2grid(nrows, ncols, row, col, spanr, spanc);
    plot(x, v, "r-");

    spanr = 2, spanc = 3;
    row = 0, col = 0;
    subplot2grid(nrows, ncols, row, col, spanr, spanc);
    plot(x, u, "b-");
    // Add some text to the plot
    text(100., -0.5, "Hello!");

    // Show plots
    show();
    return 0;
}
