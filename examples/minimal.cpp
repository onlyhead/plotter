#include <plotter.hpp>

int main() {
    plotter::Plotter plt;
    std::vector<int> data = {1, 3, 2, 4};
    plt.plot(data);
    plt.save("minimal.png");
}
