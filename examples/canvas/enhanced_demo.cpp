#include <canvas/canvas.hpp>
#include <cmath>
#include <iostream>
#include <vector>

int main() {
    std::cout << "Enhanced Canvas Demo with Subplots and Themes" << std::endl;

    // Create a canvas with subplots (2x2 grid)
    plotter::Canvas canvas(800, 600, false);
    canvas.create_subplots(2, 2);
    
    // Test dark theme
    canvas.set_dark_theme();
    
    std::cout << "Created 2x2 subplot grid with dark theme" << std::endl;

    // Generate some sample data
    std::vector<double> x1, y1, y2, y3, y4;
    for (int i = 0; i < 100; ++i) {
        double t = i * 0.1;
        x1.push_back(t);
        y1.push_back(std::sin(t));
        y2.push_back(std::cos(t));
        y3.push_back(std::sin(t) * std::cos(t));
        y4.push_back(std::exp(-t * 0.1) * std::sin(t));
    }

    // Plot in first subplot (0,0) - sine wave
    canvas.subplot(0, 0);
    canvas.set_title("Sine Wave");
    canvas.set_xlabel("Time");
    canvas.set_ylabel("Amplitude");
    canvas.plot(x1, y1);
    
    // Plot in second subplot (0,1) - cosine wave
    canvas.subplot(0, 1);
    canvas.set_title("Cosine Wave");
    canvas.set_xlabel("Time");
    canvas.set_ylabel("Amplitude");
    canvas.plot(x1, y2);
    
    // Plot in third subplot (1,0) - sine*cosine
    canvas.subplot(1, 0);
    canvas.set_title("Sin*Cos");
    canvas.set_xlabel("Time");
    canvas.set_ylabel("Amplitude");
    canvas.plot(x1, y3);
    
    // Plot in fourth subplot (1,1) - damped sine
    canvas.subplot(1, 1);
    canvas.set_title("Damped Sine");
    canvas.set_xlabel("Time");
    canvas.set_ylabel("Amplitude");
    canvas.plot(x1, y4);

    // Save the result
    bool success = canvas.save("enhanced_canvas_demo.png");

    if (success) {
        std::cout << "\nEnhanced canvas demo saved as 'enhanced_canvas_demo.png'" << std::endl;
        std::cout << "Features demonstrated:" << std::endl;
        std::cout << "- 2x2 subplot grid layout" << std::endl;
        std::cout << "- Dark theme with custom color palette" << std::endl;
        std::cout << "- Automatic color cycling within subplots" << std::endl;
        std::cout << "- Subplot border rendering" << std::endl;
        std::cout << "- Independent data scaling per subplot" << std::endl;
        std::cout << "- Infrastructure for titles and labels (stored for future rendering)" << std::endl;
    } else {
        std::cout << "Failed to save enhanced canvas demo" << std::endl;
        return 1;
    }

    // Demonstrate theme switching
    std::cout << "\nTesting light theme..." << std::endl;
    canvas.set_light_theme();
    
    // Add one more plot to show theme change
    canvas.subplot(0, 0);
    std::vector<double> x_extra = {0, 1, 2, 3, 4};
    std::vector<double> y_extra = {0, 2, 1, 3, 2};
    canvas.plot(x_extra, y_extra, plotter::Color("#FF0000")); // Red line
    
    success = canvas.save("enhanced_canvas_light_theme.png");
    
    if (success) {
        std::cout << "Light theme demo saved as 'enhanced_canvas_light_theme.png'" << std::endl;
    }

    return 0;
}
