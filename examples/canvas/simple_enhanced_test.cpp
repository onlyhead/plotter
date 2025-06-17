#include <canvas/canvas.hpp>
#include <iostream>
#include <vector>

int main() {
    std::cout << "Simple Enhanced Canvas Test" << std::endl;

    // Create a simple canvas
    plotter::Canvas canvas(400, 300, false);
    
    // Test theme setting
    canvas.set_dark_theme();
    std::cout << "Set dark theme" << std::endl;
    
    // Simple plot
    std::vector<double> x = {0, 1, 2, 3, 4};
    std::vector<double> y = {0, 1, 4, 9, 16};
    
    canvas.plot(x, y);
    std::cout << "Added simple plot" << std::endl;
    
    // Save
    bool success = canvas.save("simple_enhanced_test.png");
    
    if (success) {
        std::cout << "Test saved successfully!" << std::endl;
    } else {
        std::cout << "Failed to save test" << std::endl;
        return 1;
    }
    
    return 0;
}
