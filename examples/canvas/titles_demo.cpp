#include <canvas.hpp>
#include <cmath>
#include <iostream>
#include <vector>

int main() {
    std::cout << "=== Canvas Titles and Labels Demo ===" << std::endl;

    // Create canvas
    plotter::Canvas canvas(800, 600, false);
    canvas.set_light_theme();

    // Create a 2x2 subplot grid
    canvas.create_subplots(2, 2);

    // Generate sample data
    std::vector<double> x;
    std::vector<double> y_sin, y_cos, y_exp, y_log;

    for (int i = 0; i < 100; ++i) {
        double val = i * 0.1;
        x.push_back(val);
        y_sin.push_back(std::sin(val));
        y_cos.push_back(std::cos(val));
        y_exp.push_back(std::exp(-val * 0.2));
        y_log.push_back(std::log(val + 1));
    }

    // Plot 1: Main title and basic labels
    canvas.subplot(0, 0);
    canvas.set_title("Sine Wave Function");
    canvas.set_xlabel("Time (seconds)");
    canvas.set_ylabel("Amplitude");
    canvas.plot(x, y_sin, {255, 0, 0, 255});

    // Plot 2: Longer title with styling
    canvas.subplot(0, 1);
    canvas.set_title("Cosine Wave with Phase Shift");
    canvas.set_xlabel("Time");
    canvas.set_ylabel("Value");
    canvas.plot(x, y_cos, {0, 255, 0, 255});

    // Plot 3: Mathematical notation in title
    canvas.subplot(1, 0);
    canvas.set_title("Exponential Decay: y = e^(-0.2x)");
    canvas.set_xlabel("x");
    canvas.set_ylabel("y = e^(-0.2x)");
    canvas.plot(x, y_exp, {0, 0, 255, 255});

    // Plot 4: Longer descriptive title
    canvas.subplot(1, 1);
    canvas.set_title("Natural Logarithm Growth");
    canvas.set_xlabel("Input Value");
    canvas.set_ylabel("ln(x + 1)");
    canvas.plot(x, y_log, {255, 165, 0, 255});

    // Set an overall canvas title
    canvas.set_canvas_title("Mathematical Functions Comparison");

    // Save the result
    canvas.save("titles_demo.png");

    std::cout << "Demo completed! Output saved to titles_demo.png" << std::endl;
    std::cout << "Features demonstrated:" << std::endl;
    std::cout << "- Individual subplot titles" << std::endl;
    std::cout << "- X and Y axis labels" << std::endl;
    std::cout << "- Overall canvas title" << std::endl;
    std::cout << "- Mathematical notation in titles" << std::endl;

    return 0;
}
