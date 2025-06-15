#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <plotter.hpp>

int main() {
    std::cout << "=== Demonstrating Class-Based Plotter Interface with Concord Points ===" << std::endl;

    // Create two separate plotter instances
    plotter::Plotter plot1;
    plotter::Plotter plot2;

    std::cout << "Plot 1 figure number: " << plot1.figure_number() << std::endl;
    std::cout << "Plot 2 figure number: " << plot2.figure_number() << std::endl;

    // Prepare data for first plot using Concord Points
    int n = 100;
    std::vector<concord::Point> sine_points;
    for (int i = 0; i < n; ++i) {
        double x = i * 0.1;
        double y = sin(x);
        sine_points.emplace_back(x, y);
    }

    // Prepare data for second plot using Concord Points
    std::vector<concord::Point> cosine_points;
    for (int i = 0; i < n; ++i) {
        double x = i * 0.1;
        double y = cos(x);
        cosine_points.emplace_back(x, y);
    }

    std::cout << "\n=== Plotting on first instance ===" << std::endl;
    plot1.plot(sine_points, pigment::RGB::blue());
    plot1.title("Sine Wave");
    plot1.xlabel("X");
    plot1.ylabel("sin(x)");
    plot1.save("sine_plot.png");

    std::cout << "\n=== Plotting on second instance ===" << std::endl;
    plot2.plot(cosine_points, "r-");
    plot2.title("Cosine Wave");
    plot2.xlabel("X");
    plot2.ylabel("cos(x)");
    plot2.save("cosine_plot.png");

    std::cout << "\n=== Creating multiple plots in a loop ===" << std::endl;
    std::vector<plotter::Plotter> plots;
    for (int i = 0; i < 3; ++i) {
        plots.emplace_back();
        std::vector<concord::Point> data_points;
        data_points.emplace_back(0, 1.0 * i);
        data_points.emplace_back(1, 2.0 * i);
        data_points.emplace_back(2, 3.0 * i);
        data_points.emplace_back(3, 4.0 * i);

        plots[i].plot(data_points, pigment::RGB::green());
        plots[i].title(("Dataset " + std::to_string(i)).c_str());
        plots[i].save(("dataset_" + std::to_string(i) + ".png").c_str());
    }

    std::cout << "\n=== Summary ===" << std::endl;
    std::cout << "Successfully demonstrated class-based interface with Concord Points!" << std::endl;
    std::cout << "- Created multiple independent plotter instances" << std::endl;
    std::cout << "- Each instance manages its own figure number" << std::endl;
    std::cout << "- Can plot simultaneously on different instances" << std::endl;
    std::cout << "- All coordinates use Concord Points" << std::endl;
    std::cout << "- All colors use Pigment RGB types" << std::endl;

    return 0;
}
