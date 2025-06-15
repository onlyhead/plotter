#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <plotter.hpp>

int main() {
    // Create a plotter instance
    plotter::Plotter plt;

    std::cout << "Demonstrating Concord and Pigment integration..." << std::endl;

    // Set the size of output image
    plt.figure_size(1200, 800);

    // ============ Concord Point Usage ============

    // Create some points using Concord
    std::vector<concord::Point> sine_points;
    std::vector<concord::Point> cosine_points;

    for (int i = 0; i <= 100; ++i) {
        double x = i * 2 * M_PI / 100.0;
        sine_points.emplace_back(x, std::sin(x), 0.0);
        cosine_points.emplace_back(x, std::cos(x), 0.0);
    }

    // Plot using Concord points with Pigment colors
    plt.plot(sine_points, pigment::RGB::red());
    plt.plot(cosine_points, pigment::RGB::blue());

    // ============ Geometric Shapes ============

    // Plot a circle using integrated geometry functions
    plt.plot_circle(3.0, 0.5, 0.3, pigment::RGB("#FF6B35")); // Orange circle

    // Plot a rectangle
    plt.plot_rectangle(1.0, -0.8, 1.5, 0.4, pigment::RGB("#2E8B57")); // Sea green rectangle

    // ============ Advanced Pigment Usage ============

    // Create some scattered points with HSL colors
    std::vector<concord::Point> scatter_points;
    for (int i = 0; i < 50; ++i) {
        double x = (rand() % 1000) / 1000.0 * 2 * M_PI;
        double y = (rand() % 1000) / 1000.0 * 2.0 - 1.0;
        scatter_points.emplace_back(x, y, 0.0);
    }

    // Use HSL color converted to RGB
    pigment::HSL purple_hsl(280.0, 0.8, 0.6); // Purple in HSL
    plt.scatter(scatter_points, 30.0, purple_hsl.to_rgb());

    // ============ Color Palette Usage ============

    // Create a custom palette
    pigment::Palette custom_palette{
        pigment::RGB("#FF6B35"), // Orange
        pigment::RGB("#F7931E"), // Yellow-orange
        pigment::RGB("#FFD23F"), // Yellow
        pigment::RGB("#06FFA5"), // Mint green
        pigment::RGB("#06D6A0")  // Teal
    };

    plt.set_color_palette(custom_palette);

    // Plot multiple lines using palette colors
    for (int offset = 0; offset < 5; ++offset) {
        std::vector<concord::Point> wave_points;
        for (int i = 0; i <= 50; ++i) {
            double x = i * 2 * M_PI / 50.0;
            double y = 0.3 * std::sin(x + offset * M_PI / 4) + offset * 0.2 - 0.4;
            wave_points.emplace_back(x, y, 0.0);
        }
        plt.plot(wave_points, plt.get_next_color());
    }

    // ============ Filled Shapes ============

    // Create a triangle and fill it
    std::vector<concord::Point> triangle{
        concord::Point{4.5, 0.8, 0.0}, concord::Point{5.5, 0.8, 0.0}, concord::Point{5.0, 1.3, 0.0},
        concord::Point{4.5, 0.8, 0.0} // Close the triangle
    };

    // Fill with semi-transparent color
    pigment::RGB fill_color("#9B59B6");
    fill_color.a = 128; // Semi-transparent
    plt.fill(triangle, fill_color);

    // ============ Plot Styling ============

    plt.title("Concord Geometry & Pigment Colors Integration Demo");
    plt.xlabel("X Coordinate");
    plt.ylabel("Y Coordinate");
    plt.xlim(0.0, 2 * M_PI);
    plt.ylim(-1.5, 1.5);

    // Save the result
    const char *filename = "./integration_demo.png";
    std::cout << "Saving result to " << filename << std::endl;
    plt.save(filename);

    std::cout << "Demo completed! Check the generated image." << std::endl;

    return 0;
}
