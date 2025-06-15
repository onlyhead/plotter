/**
 * Complete Integration Demo
 *
 * This example demonstrates the full integration of Concord and Pigment
 * with the Plotter library, showcasing a clean public API.
 */

#include <cmath>
#include <iostream>
#include <plotter.hpp>
#include <vector>

int main() {
    std::cout << "=== Complete Plotter Integration Demo ===" << std::endl;

    try {
        // Create a plotter instance
        plotter::Plotter plt;

        // Demo 1: Traditional plotting with vectors
        std::cout << "1. Traditional vector plotting..." << std::endl;
        std::vector<double> x_vals, y_vals;
        for (int i = 0; i <= 50; ++i) {
            double x = i * 0.2;
            x_vals.push_back(x);
            y_vals.push_back(std::sin(x));
        }
        plt.plot(x_vals, y_vals, "b-");

        // Demo 2: Concord Point plotting
        std::cout << "2. Concord Point plotting..." << std::endl;
        std::vector<concord::Point> cosine_points;
        for (int i = 0; i <= 50; ++i) {
            double x = i * 0.2;
            cosine_points.emplace_back(x, std::cos(x), 0.0);
        }
        plt.plot(cosine_points, pigment::RGB::red());

        // Demo 3: Pigment color management
        std::cout << "3. Pigment color management..." << std::endl;

        // Create a custom palette
        std::vector<pigment::RGB> custom_colors = {
            pigment::RGB("#FF6B35"), // Orange
            pigment::RGB("#F7931E"), // Golden
            pigment::RGB("#FFD23F"), // Yellow
            pigment::RGB("#06FFA5"), // Mint
            pigment::RGB("#06D6A0")  // Teal
        };
        pigment::Palette custom_palette(custom_colors);
        plt.set_color_palette(custom_palette);

        // Demo 4: Geometric shapes
        std::cout << "4. Geometric shapes..." << std::endl;

        // Plot multiple circles with palette colors
        for (int i = 0; i < 3; ++i) {
            double center_x = 2.0 + i * 1.5;
            double center_y = 0.5;
            double radius = 0.3;

            auto color = plt.get_next_color();
            plt.plot_circle(center_x, center_y, radius, color);
        }

        // Demo 5: Different color spaces
        std::cout << "5. Different color spaces..." << std::endl;

        // HSL color
        pigment::HSL purple_hsl(280, 0.8, 0.6);
        auto purple_rgb = purple_hsl.to_rgb();

        // HSV color
        pigment::HSV bright_green_hsv(120, 1.0, 1.0);
        auto green_rgb = bright_green_hsv.toRGB();

        // Plot rectangles with these colors
        plt.plot_rectangle(6.0, -0.8, 1.0, 0.6, purple_rgb);
        plt.plot_rectangle(7.5, -0.8, 1.0, 0.6, green_rgb);

        // Demo 6: Scatter plot with Concord points
        std::cout << "6. Scatter plot with random points..." << std::endl;
        std::vector<concord::Point> scatter_points;
        for (int i = 0; i < 20; ++i) {
            double x = 1.0 + (rand() % 100) / 20.0;
            double y = -1.5 + (rand() % 100) / 50.0;
            scatter_points.emplace_back(x, y, 0.0);
        }
        plt.scatter(scatter_points, pigment::RGB::blue());

        // Configure the plot
        plt.xlabel("X Values");
        plt.ylabel("Y Values");
        plt.title("Complete Integration Demo: Concord + Pigment + Plotter");
        plt.legend();

        // Save the plot
        plt.save("complete_demo.png");

        std::cout << "=== Demo completed successfully! ===" << std::endl;
        std::cout << "Plot saved as 'complete_demo.png'" << std::endl;

        // Display some integration info
        std::cout << "\n=== Integration Summary ===" << std::endl;
        std::cout << "✓ Concord geometry integration working" << std::endl;
        std::cout << "✓ Pigment color management working" << std::endl;
        std::cout << "✓ Clean public API (only plotter.hpp included)" << std::endl;
        std::cout << "✓ No OpenCV dependencies" << std::endl;
        std::cout << "✓ Modern C++ interface" << std::endl;

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
