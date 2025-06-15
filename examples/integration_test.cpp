#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <plotter/internal/integrations.hpp>

int main() {
    std::cout << "Testing Concord and Pigment integration at C++ level..." << std::endl;

    // ============ Test Concord Point Operations ============

    std::cout << "\n--- Testing Concord Points ---" << std::endl;

    // Create some points using Concord
    std::vector<concord::Point> test_points;
    for (int i = 0; i <= 10; ++i) {
        double x = i * 0.1;
        test_points.emplace_back(x, std::sin(x), 0.0);
    }

    std::cout << "Created " << test_points.size() << " points" << std::endl;

    // Extract coordinates
    auto x_coords = plotter::integrations::geometry::extract_x(test_points);
    auto y_coords = plotter::integrations::geometry::extract_y(test_points);

    std::cout << "First point: (" << x_coords[0] << ", " << y_coords[0] << ")" << std::endl;
    std::cout << "Last point: (" << x_coords.back() << ", " << y_coords.back() << ")" << std::endl;

    // Test geometric shape generation
    auto circle_points = plotter::integrations::geometry::generate_circle_points(0.0, 0.0, 1.0, 8);
    std::cout << "Generated circle with " << circle_points.size() << " points" << std::endl;

    auto rect_points = plotter::integrations::geometry::generate_rectangle_points(0.0, 0.0, 2.0, 1.0);
    std::cout << "Generated rectangle with " << rect_points.size() << " points" << std::endl;

    // ============ Test Pigment Color Operations ============

    std::cout << "\n--- Testing Pigment Colors ---" << std::endl;

    // Test RGB colors
    pigment::RGB red_color = pigment::RGB::red();
    pigment::RGB blue_color("#0000FF");
    pigment::RGB custom_color(128, 64, 192);

    std::cout << "Red color: " << red_color.to_hex() << std::endl;
    std::cout << "Blue color: " << blue_color.to_hex() << std::endl;
    std::cout << "Custom color: " << custom_color.to_hex() << std::endl;

    // Test color conversions
    std::string red_matplotlib = plotter::integrations::color::to_matplotlib_color(red_color);
    std::string blue_matplotlib = plotter::integrations::color::to_matplotlib_color(blue_color);

    std::cout << "Red color for matplotlib: " << red_matplotlib << std::endl;
    std::cout << "Blue color for matplotlib: " << blue_matplotlib << std::endl;

    // Test HSL colors
    pigment::HSL purple_hsl(280.0, 0.8, 0.6);
    pigment::RGB purple_rgb = purple_hsl.to_rgb();
    std::string purple_matplotlib = plotter::integrations::color::to_matplotlib_color(purple_hsl);

    std::cout << "Purple HSL (" << purple_hsl.h << ", " << purple_hsl.s << ", " << purple_hsl.l << ") -> RGB "
              << purple_rgb.to_hex() << std::endl;
    std::cout << "Purple for matplotlib: " << purple_matplotlib << std::endl;

    // Test HSV colors
    pigment::HSV green_hsv(120.0f, 1.0f, 1.0f);
    pigment::RGB green_rgb = green_hsv.toRGB();
    std::string green_matplotlib = plotter::integrations::color::to_matplotlib_color(green_hsv);

    std::cout << "Green HSV (" << green_hsv.h << ", " << green_hsv.s << ", " << green_hsv.v << ") -> RGB "
              << green_rgb.to_hex() << std::endl;
    std::cout << "Green for matplotlib: " << green_matplotlib << std::endl;

    // Test color palette
    auto default_palette = plotter::integrations::color::create_default_palette();
    std::cout << "Default palette has " << default_palette.size() << " colors" << std::endl;

    for (size_t i = 0; i < std::min(size_t(5), default_palette.size()); ++i) {
        auto color = plotter::integrations::color::get_palette_color(default_palette, i);
        std::cout << "  Color " << i << ": " << color.to_hex() << std::endl;
    }

    // Test custom palette
    pigment::Palette custom_palette{
        pigment::RGB("#FF6B35"), // Orange
        pigment::RGB("#F7931E"), // Yellow-orange
        pigment::RGB("#FFD23F"), // Yellow
        pigment::RGB("#06FFA5"), // Mint green
        pigment::RGB("#06D6A0")  // Teal
    };

    std::cout << "Custom palette has " << custom_palette.size() << " colors:" << std::endl;
    for (size_t i = 0; i < custom_palette.size(); ++i) {
        std::cout << "  Color " << i << ": " << custom_palette[i].to_hex() << std::endl;
    }

    std::cout << "\n--- Integration Tests Completed Successfully! ---" << std::endl;

    return 0;
}
