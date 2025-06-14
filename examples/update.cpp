#define _USE_MATH_DEFINES
#include <chrono>
#include <cmath>
#include <plotter/plotter.hpp>

using namespace plotter;

void update_window(const double x, const double y, const double t, std::vector<double> &xt, std::vector<double> &yt) {
    const double target_length = 300;
    const double half_win = (target_length / (2. * sqrt(1. + t * t)));

    xt[0] = x - half_win;
    xt[1] = x + half_win;
    yt[0] = y - half_win * t;
    yt[1] = y + half_win * t;
}

int main() {
    size_t n = 1000;
    std::vector<double> x, y;

    const double w = 0.05;
    const double a = n / 2;

    for (size_t i = 0; i < n; i++) {
        x.push_back(i);
        y.push_back(a * sin(w * i));
    }

    std::vector<double> xt(2), yt(2);

    title("Tangent of a sine curve");
    xlim(x.front(), x.back());
    ylim(-a, a);
    // axis("equal");  // Not implemented yet

    // Plot sin once and for all.
    named_plot("sin", x, y);

    // Prepare plotting the tangent.
    // Note: Dynamic plot updating is not supported in this implementation
    // plt::Plot plot("tangent");

    legend();

    for (size_t i = 0; i < n; i++) {
        if (i % 10 == 0) {
            update_window(x[i], y[i], a * w * cos(w * x[i]), xt, yt);

            // Static plot of tangent line
            plot(xt, yt, "r-");

            // Small pause so the viewer has a chance to enjoy the animation.
            pause(0.1);
        }
    }

    show();
    return 0;
}
