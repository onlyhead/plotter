#include "plotter/plotter.hpp"
#include <cmath>
#include <vector>

int main() {
    // Example usage of the modular plotter library

    // Generate some sample data
    std::vector<double> x, y;
    for (int i = 0; i < 100; ++i) {
        double val = i * 0.1;
        x.push_back(val);
        y.push_back(std::sin(val));
    }

    // Note: These functions would work when Python headers are available
    // and the implementation is completed

    // plotter::figure();
    // plotter::plot(x, y);
    // plotter::xlabel("X Values");
    // plotter::ylabel("Y Values");
    // plotter::title("Sine Wave");
    // plotter::grid(true);
    // plotter::show();

    return 0;
}
