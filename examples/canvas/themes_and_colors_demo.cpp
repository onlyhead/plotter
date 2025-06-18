#include <canvas/canvas.hpp>
#include <cmath>
#include <iostream>
#include <vector>

int main() {
    std::cout << "Enhanced Canvas Demo with Named Colors and Palettes" << std::endl;

    // Create a canvas with subplots
    plotter::Canvas canvas(900, 700, false);
    canvas.create_subplots(2, 3);  // 2x3 grid for more examples
    
    // Test vibrant theme
    canvas.set_vibrant_palette(8);
    
    std::cout << "Created 2x3 subplot grid with vibrant palette" << std::endl;

    // Generate sample data
    std::vector<double> x;
    for (int i = 0; i < 100; ++i) {
        x.push_back(i * 0.1);
    }

    // Plot 1: Using named color convenience methods
    canvas.subplot(0, 0);
    canvas.set_title("Named Colors");
    std::vector<double> y1;
    for (double val : x) y1.push_back(std::sin(val));
    canvas.plot_red(x, y1);

    // Plot 2: Using automatic palette colors
    canvas.subplot(0, 1);
    canvas.set_title("Auto Palette Colors");
    std::vector<double> y2, y3;
    for (double val : x) {
        y2.push_back(std::cos(val));
        y3.push_back(std::sin(val * 2) * 0.5);
    }
    canvas.plot(x, y2);  // Will use first palette color
    canvas.plot(x, y3);  // Will use second palette color

    // Plot 3: Material Design palette
    canvas.subplot(0, 2);
    canvas.set_title("Material Design");
    canvas.set_material_design_palette();
    std::vector<double> y4;
    for (double val : x) y4.push_back(std::exp(-val * 0.1) * std::sin(val));
    canvas.plot(x, y4);

    // Plot 4: Warm palette
    canvas.subplot(1, 0);
    canvas.set_title("Warm Palette");
    canvas.set_warm_palette();
    std::vector<double> y5, y6;
    for (double val : x) {
        y5.push_back(std::sin(val) * std::cos(val * 0.5));
        y6.push_back(std::cos(val) * std::sin(val * 0.3));
    }
    canvas.plot(x, y5);
    canvas.plot(x, y6);

    // Plot 5: Cool palette
    canvas.subplot(1, 1);
    canvas.set_title("Cool Palette");
    canvas.set_cool_palette();
    std::vector<double> y7, y8, y9;
    for (double val : x) {
        y7.push_back(std::sin(val * 0.5));
        y8.push_back(std::cos(val * 0.7));
        y9.push_back(std::sin(val * 0.3) * 0.8);
    }
    canvas.plot(x, y7);
    canvas.plot(x, y8);
    canvas.plot(x, y9);

    // Plot 6: Mixed named colors
    canvas.subplot(1, 2);
    canvas.set_title("Mixed Named Colors");
    std::vector<double> y10, y11, y12;
    for (double val : x) {
        y10.push_back(std::sin(val + 0.5));
        y11.push_back(std::cos(val + 1.0));
        y12.push_back(std::sin(val + 1.5) * 0.7);
    }
    canvas.plot_blue(x, y10);
    canvas.plot_orange(x, y11);
    canvas.plot_purple(x, y12);

    // Save the result
    bool success = canvas.save("pigment_palette_demo.png");

    if (success) {
        std::cout << "\nPigment palette demo saved as 'pigment_palette_demo.png'" << std::endl;
        std::cout << "Features demonstrated:" << std::endl;
        std::cout << "- Named color convenience methods (plot_red, plot_blue, etc.)" << std::endl;
        std::cout << "- Automatic palette color cycling" << std::endl;
        std::cout << "- Material Design palette" << std::endl;
        std::cout << "- Warm and Cool predefined palettes" << std::endl;
        std::cout << "- Mixed named colors in same subplot" << std::endl;
        std::cout << "- 2x3 subplot grid layout" << std::endl;
    } else {
        std::cout << "Failed to save pigment demo" << std::endl;
        return 1;
    }

    // Test different themes with same data
    std::cout << "\nTesting different themes..." << std::endl;
    
    // Dark theme test
    canvas.set_dark_theme();
    canvas.subplot(0, 0);
    canvas.plot_cyan(x, y1);
    canvas.save("pigment_dark_theme.png");
    
    // Light theme test  
    canvas.set_light_theme();
    canvas.subplot(0, 0);
    canvas.plot_green(x, y1);
    canvas.save("pigment_light_theme.png");

    std::cout << "Additional theme demos saved!" << std::endl;

    return 0;
}
