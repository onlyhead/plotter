#define _USE_MATH_DEFINES
#include <cmath>
#include <plotter.hpp>
#include <vector>

using namespace plotter;

int main() {
    std::vector<double> t(1000);
    std::vector<double> x(t.size());

    for (size_t i = 0; i < t.size(); i++) {
        t[i] = i / 100.0;
        x[i] = sin(2.0 * M_PI * 1.0 * t[i]);
    }

    xkcd();
    plot(t, x);
    title("AN ORDINARY SIN WAVE");
    show();
    return 0;
}
