#include <plotter/plotter.hpp>

namespace plt = plotter;

int main() {
    plt::plot({1, 3, 2, 4});
    plt::show();
}
