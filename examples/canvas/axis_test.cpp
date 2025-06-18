#include <canvas.hpp>
#include <cmath>
#include <iostream>
#include <vector>

int main() {
    std::cout << "=== Axis Test ===" << std::endl;
    
    // Create a simple canvas
    plotter::Canvas canvas(600, 400, false);
    canvas.set_light_theme();
    
    // Generate simple data
    std::vector<double> x, y;
    for (int i = 0; i <= 20; ++i) {
        double val = i * 0.5;
        x.push_back(val);
        y.push_back(std::sin(val));
    }
    
    // Set up the plot with axes
    canvas.set_title("Simple Sine Wave with Axes");
    canvas.set_xlabel("X Values");
    canvas.set_ylabel("Y Values");
    canvas.show_axes(true, true);
    canvas.set_axis_colors({0, 0, 0, 255}, {100, 100, 100, 255}, {50, 50, 50, 255});
    
    // Plot the data
    canvas.plot(x, y, {255, 0, 0, 255});
    
    // Save the result
    canvas.save("axis_test.png");
    
    std::cout << "Axis test completed! Check axis_test.png" << std::endl;
    
    return 0;
}
