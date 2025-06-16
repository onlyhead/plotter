#include <canvas/canvas.hpp>
#include <cmath>
#include <iostream>
#include <vector>

int main() {
    // Create a canvas that demonstrates the Concord Grid's spatial capabilities
    plotter::Canvas canvas(600, 600, false);

    // Set a nice background using Pigment
    canvas.set_background(plotter::Color("#2C3E50")); // Dark blue-gray

    std::cout << "Creating spatial grid demonstration..." << std::endl;

    // Test Pigment color operations
    plotter::Color base_color("#E74C3C");   // Red
    plotter::Color accent_color("#3498DB"); // Blue

    // Create a gradient effect by mixing colors and testing pixel operations
    for (int y = 0; y < 600; ++y) {
        for (int x = 0; x < 600; ++x) {
            // Skip most pixels for performance, create a pattern
            if ((x + y) % 20 == 0) {
                // Create a distance-based color gradient
                double center_x = 300.0;
                double center_y = 300.0;
                double distance = std::sqrt((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y));
                double max_distance = std::sqrt(center_x * center_x + center_y * center_y);

                // Normalize distance to 0-1
                double norm_dist = distance / max_distance;

                // Create a color that changes with distance
                int red = (int)(base_color.r * (1.0 - norm_dist) + accent_color.r * norm_dist);
                int green = (int)(base_color.g * (1.0 - norm_dist) + accent_color.g * norm_dist);
                int blue = (int)(base_color.b * (1.0 - norm_dist) + accent_color.b * norm_dist);

                plotter::Color pixel_color(red, green, blue, 180); // Semi-transparent
                canvas.set_pixel_color(x, y, pixel_color);
            }
        }
    }

    // Create some mathematical curves to overlay
    std::vector<plotter::Color> curve_colors = {
        plotter::Color("#F39C12"), // Orange
        plotter::Color("#9B59B6"), // Purple
        plotter::Color("#1ABC9C"), // Turquoise
        plotter::Color("#E67E22"), // Dark orange
        plotter::Color("#2ECC71")  // Green
    };

    // Draw several mathematical curves
    for (int curve_idx = 0; curve_idx < 5; ++curve_idx) {
        std::vector<double> x, y;

        // Different mathematical functions for each curve
        for (int i = 0; i < 200; ++i) {
            double t = (i - 100) * 0.05;
            double curve_x, curve_y;

            switch (curve_idx) {
            case 0: // Spiral
                curve_x = t * std::cos(t * 2);
                curve_y = t * std::sin(t * 2);
                break;
            case 1: // Rose curve
                curve_x = std::cos(t * 3) * std::cos(t);
                curve_y = std::cos(t * 3) * std::sin(t);
                break;
            case 2: // Lissajous curve
                curve_x = std::sin(t * 2) * 2;
                curve_y = std::sin(t * 3) * 2;
                break;
            case 3: // Hyperbola
                if (std::abs(t) > 0.1) {
                    curve_x = t;
                    curve_y = 1.0 / t;
                } else {
                    continue;
                }
                break;
            case 4: // Cardioid
                curve_x = (1 + std::cos(t)) * std::cos(t);
                curve_y = (1 + std::cos(t)) * std::sin(t);
                break;
            }

            x.push_back(curve_x);
            y.push_back(curve_y);
        }

        canvas.plot(x, y, curve_colors[curve_idx]);
    }

    // Test the Pigment color features more extensively
    std::cout << "Testing Pigment color features:" << std::endl;

    // Test color mixing using Pigment arithmetic operations
    plotter::Color color1("#FF0000");       // Red
    plotter::Color color2("#00FF00");       // Green
    plotter::Color mixed = color1 + color2; // Should create yellow-ish

    std::cout << "Color1 (red): " << color1.to_hex() << std::endl;
    std::cout << "Color2 (green): " << color2.to_hex() << std::endl;
    std::cout << "Mixed color: " << mixed.to_hex() << std::endl;

    // Create a small colorbar showing the mixed color
    for (int i = 0; i < 50; ++i) {
        for (int j = 0; j < 10; ++j) {
            canvas.set_pixel_color(50 + i, 50 + j, mixed);
        }
    }

    // Save the result
    bool success = canvas.save("spatial_grid_demo.png");

    if (success) {
        std::cout << "\nSpatial grid demo saved as 'spatial_grid_demo.png'" << std::endl;
        std::cout << "This demo showcases:" << std::endl;
        std::cout << "- Concord Grid's pixel-level spatial operations" << std::endl;
        std::cout << "- Distance-based color gradients using grid coordinates" << std::endl;
        std::cout << "- Pigment color arithmetic operations (color mixing)" << std::endl;
        std::cout << "- Mathematical curve plotting with multiple colors" << std::endl;
        std::cout << "- Hex color string parsing and conversion" << std::endl;
        std::cout << "- Semi-transparent pixel operations" << std::endl;
    } else {
        std::cout << "Failed to save spatial grid demo" << std::endl;
        return 1;
    }

    return 0;
}
