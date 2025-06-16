#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <plotter.hpp>

using namespace std;
using namespace plotter;

int main() {
    // Prepare data
    int ncols = 500, nrows = 300;
    std::vector<float> z(ncols * nrows);
    for (int j = 0; j < nrows; ++j) {
        for (int i = 0; i < ncols; ++i) {
            z.at(ncols * j + i) = std::sin(std::hypot(i - ncols / 2, j - nrows / 2));
        }
    }

    const float *zptr = &(z[0]);
    const int colors = 1;

    title("My matrix");
    imshow(zptr, nrows, ncols, colors);

    // Show plots
    save("imshow.png");
    std::cout << "Result saved to 'imshow.png'.\n";
    return 0;
}
