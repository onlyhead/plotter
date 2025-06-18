#include <canvas/canvas.hpp>
#include <cmath>
#include <iostream>
#include <vector>

int main() {
    std::cout << "=== Comprehensive Enhanced Canvas Demo ===" << std::endl;
    
    // Create a larger canvas for comprehensive demonstration
    plotter::Canvas canvas(1200, 800, false);
    
    // Start with dark theme
    canvas.set_dark_theme();
    std::cout << "Set dark theme" << std::endl;
    
    // Create a 3x2 subplot grid
    canvas.create_subplots(3, 2);
    std::cout << "Created 3x2 subplot grid" << std::endl;
    
    // Generate various mathematical functions
    std::vector<double> x;
    for (int i = 0; i < 200; ++i) {
        x.push_back(i * 0.05);
    }
    
    // Plot 1: Sine wave with automatic color
    canvas.subplot(0, 0);
    canvas.set_title("Sine Wave");
    canvas.set_xlabel("Time");
    canvas.set_ylabel("Amplitude");
    std::vector<double> y_sin;
    for (double t : x) {
        y_sin.push_back(std::sin(t));
    }
    canvas.plot(x, y_sin); // Uses first theme color
    
    // Plot 2: Cosine wave with automatic color
    canvas.subplot(0, 1);
    canvas.set_title("Cosine Wave");
    canvas.set_xlabel("Time");
    canvas.set_ylabel("Amplitude");
    std::vector<double> y_cos;
    for (double t : x) {
        y_cos.push_back(std::cos(t));
    }
    canvas.plot(x, y_cos); // Uses second theme color
    
    // Plot 3: Exponential decay with manual color
    canvas.subplot(1, 0);
    canvas.set_title("Exponential Decay");
    canvas.set_xlabel("Time");
    canvas.set_ylabel("Value");
    canvas.set_ylim(0, 1.2);
    std::vector<double> y_exp;
    for (double t : x) {
        y_exp.push_back(std::exp(-t * 0.2));
    }
    canvas.plot(x, y_exp, plotter::Color("#FF6B6B")); // Custom red color
    
    // Plot 4: Multiple overlapping plots
    canvas.subplot(1, 1);
    canvas.set_title("Multiple Functions");
    canvas.set_xlabel("Time");
    canvas.set_ylabel("Value");
    
    std::vector<double> y1, y2, y3;
    for (double t : x) {
        y1.push_back(std::sin(t) * 0.5);
        y2.push_back(std::cos(t) * 0.3);
        y3.push_back(std::sin(t * 2) * 0.2);
    }
    canvas.plot(x, y1); // Automatic color cycling
    canvas.plot(x, y2); // Next automatic color
    canvas.plot(x, y3); // Next automatic color
    
    // Plot 5: Parabola with custom limits
    canvas.subplot(2, 0);
    canvas.set_title("Parabola");
    canvas.set_xlabel("X");
    canvas.set_ylabel("Y");
    canvas.set_xlim(-5, 5);
    canvas.set_ylim(0, 25);
    
    std::vector<double> x_para, y_para;
    for (int i = -50; i <= 50; ++i) {
        double t = i * 0.1;
        x_para.push_back(t);
        y_para.push_back(t * t);
    }
    canvas.plot(x_para, y_para);
    
    // Plot 6: Step function
    canvas.subplot(2, 1);
    canvas.set_title("Step Function");
    canvas.set_xlabel("X");
    canvas.set_ylabel("Y");
    
    std::vector<double> x_step, y_step;
    for (int i = 0; i < 100; ++i) {
        double t = i * 0.1;
        x_step.push_back(t);
        y_step.push_back(std::floor(t));
    }
    canvas.plot(x_step, y_step);
    
    // Save the dark theme version
    bool success = canvas.save("comprehensive_demo_dark.png");
    if (success) {
        std::cout << "Dark theme demo saved as 'comprehensive_demo_dark.png'" << std::endl;
    }
    
    // Switch to light theme and save again
    std::cout << "Switching to light theme..." << std::endl;
    canvas.set_light_theme();
    
    success = canvas.save("comprehensive_demo_light.png");
    if (success) {
        std::cout << "Light theme demo saved as 'comprehensive_demo_light.png'" << std::endl;
    }
    
    // Display information about the canvas setup
    auto [rows, cols] = canvas.get_subplot_layout();
    auto [current_row, current_col] = canvas.get_current_subplot_index();
    int total_subplots = canvas.get_subplot_count();
    
    std::cout << "\n=== Canvas Information ===" << std::endl;
    std::cout << "Subplot layout: " << rows << "x" << cols << std::endl;
    std::cout << "Total subplots: " << total_subplots << std::endl;
    std::cout << "Current subplot: (" << current_row << "," << current_col << ")" << std::endl;
    
    std::cout << "\n=== Features Demonstrated ===" << std::endl;
    std::cout << "✓ Multiple subplot layout (3x2 grid)" << std::endl;
    std::cout << "✓ Theme switching (dark/light themes)" << std::endl;
    std::cout << "✓ Automatic color cycling" << std::endl;
    std::cout << "✓ Manual color specification" << std::endl;
    std::cout << "✓ Multiple plots per subplot" << std::endl;
    std::cout << "✓ Custom axis limits" << std::endl;
    std::cout << "✓ Title and label infrastructure" << std::endl;
    std::cout << "✓ Subplot border rendering" << std::endl;
    std::cout << "✓ Independent data scaling per subplot" << std::endl;
    std::cout << "✓ Backward compatibility maintained" << std::endl;
    
    return 0;
}
