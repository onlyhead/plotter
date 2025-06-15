#define _USE_MATH_DEFINES
#include <cmath>
#include <plotter.hpp>

using namespace std;
using namespace plotter;

int main() {
    // plot(y) - the x-coordinates are implicitly set to [0,1,...,n)
    // plt::plot({1,2,3,4});

    // Prepare data for parametric plot.
    int n = 5000; // number of data points
    vector<double> x(n), y(n);
    for (int i = 0; i < n; ++i) {
        double t = 2 * M_PI * i / n;
        x.at(i) = 16 * sin(t) * sin(t) * sin(t);
        y.at(i) = 13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t);
    }

    // plot() takes an arbitrary number of (x,y,format)-triples.
    // x must be iterable (that is, anything providing begin(x) and end(x)),
    // y must either be callable (providing operator() const) or iterable.
    plot(x, y, "r-");
    // Note: The lambda function version is not supported in this implementation

    // set_aspect(0.5);
    set_aspect_equal();

    // show plots
    show();
    return 0;
}
