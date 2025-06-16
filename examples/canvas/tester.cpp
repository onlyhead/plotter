#include <canvas/canvas.hpp>
#include <cmath>
#include <iostream>
#include <vector>

int main() {
    // Create a canvas with Pigment/Concord integration
    plotter::Canvas canvas(400, 300, false);

    // Demonstrate Pigment color usage
    plotter::Color red("#FF0000");
    plotter::Color green("#00FF00");
    plotter::Color blue("#0000FF");
    plotter::Color purple("#9932CC");

    // Set background using Pigment color
    canvas.set_background(plotter::Color("#F0F0F0")); // Light gray background

    // Create some sample data for plotting
    std::vector<double> x1, y1;
    std::vector<double> x2, y2;
    std::vector<double> x3, y3;

    // Sine wave data
    for (int i = 0; i < 100; ++i) {
        double t = i * 0.1;
        x1.push_back(t);
        y1.push_back(std::sin(t));
    }

    // Cosine wave data
    for (int i = 0; i < 100; ++i) {
        double t = i * 0.1;
        x2.push_back(t);
        y2.push_back(std::cos(t));
    }

    // Parabolic curve
    for (int i = 0; i < 50; ++i) {
        double t = (i - 25) * 0.2;
        x3.push_back(t);
        y3.push_back(t * t * 0.1);
    }

    // Plot different curves with different Pigment colors
    canvas.plot(x1, y1, red);    // Red sine wave
    canvas.plot(x2, y2, blue);   // Blue cosine wave
    canvas.plot(x3, y3, purple); // Purple parabola

    // Test named color functionality
    std::vector<double> x4 = {0, 2, 4, 6, 8};
    std::vector<double> y4 = {0, 1, -1, 0.5, -0.5};
    canvas.plot_with_named_color(x4, y4, "green");

    // Demonstrate pixel-level operations using grid
    std::cout << "Setting individual pixels using Concord grid..." << std::endl;

    // Set some individual pixels directly (this uses the Concord grid internally)
    for (int i = 0; i < 10; ++i) {
        canvas.set_pixel_color(50 + i, 50 + i, plotter::Color("#FFA500")); // Orange diagonal line
    }

    // Save the canvas
    bool success = canvas.save("demo_output.png");

    if (success) {
        std::cout << "Canvas saved successfully as 'demo_output.png'" << std::endl;
        std::cout << "This demonstrates:" << std::endl;
        std::cout << "- Pigment RGB color support with hex string constructor" << std::endl;
        std::cout << "- Named color plotting functionality" << std::endl;
        std::cout << "- Concord Grid integration for pixel-level operations" << std::endl;
        std::cout << "- Multiple plot overlays with different colors" << std::endl;
    } else {
        std::cout << "Failed to save canvas" << std::endl;
        return 1;
    }

    return 0;
}