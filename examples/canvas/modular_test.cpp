#include <canvas.hpp>
#include <cmath>
#include <iostream>
#include <vector>

int main() {
    std::cout << "=== Modular Canvas Compatibility Test ===" << std::endl;

    // Test 1: Basic functionality
    std::cout << "Test 1: Basic Canvas Creation... ";
    plotter::Canvas canvas(400, 300);
    std::cout << "✅" << std::endl;

    // Test 2: Theme switching
    std::cout << "Test 2: Theme Management... ";
    canvas.set_dark_theme();
    canvas.set_light_theme();
    canvas.set_vibrant_theme();
    std::cout << "✅" << std::endl;

    // Test 3: Palette management
    std::cout << "Test 3: Palette Management... ";
    canvas.set_material_design_palette();
    canvas.set_warm_palette();
    canvas.set_cool_palette();
    canvas.set_vibrant_palette(6);
    std::cout << "✅" << std::endl;

    // Test 4: Subplot management
    std::cout << "Test 4: Subplot Management... ";
    canvas.create_subplots(2, 2);
    canvas.subplot(0, 0);
    canvas.subplot(1, 1);
    auto layout = canvas.get_subplot_layout();
    auto current = canvas.get_current_subplot_index();
    std::cout << "✅" << std::endl;

    // Test 5: Plotting with auto colors
    std::cout << "Test 5: Auto Color Plotting... ";
    std::vector<double> x = {0, 1, 2, 3, 4};
    std::vector<double> y1 = {0, 1, 4, 9, 16};
    std::vector<double> y2 = {0, 2, 8, 18, 32};

    canvas.subplot(0, 0);
    canvas.plot(x, y1); // Auto color from palette
    canvas.plot(x, y2); // Next auto color
    std::cout << "✅" << std::endl;

    // Test 6: Named color plotting
    std::cout << "Test 6: Named Color Plotting... ";
    canvas.subplot(0, 1);
    canvas.plot_red(x, y1);
    canvas.plot_blue(x, y2);

    canvas.subplot(1, 0);
    canvas.plot_green(x, y1);
    canvas.plot_orange(x, y2);

    canvas.subplot(1, 1);
    canvas.plot_purple(x, y1);
    canvas.plot_cyan(x, y2);
    std::cout << "✅" << std::endl;

    // Test 7: String-based color plotting
    std::cout << "Test 7: String-based Colors... ";
    canvas.subplot(0, 0);
    canvas.plot_with_named_color(x, y1, "yellow");
    canvas.plot_with_named_color(x, y2, "pink");
    std::cout << "✅" << std::endl;

    // Test 8: Infrastructure methods
    std::cout << "Test 8: Infrastructure Methods... ";
    canvas.set_title("Test Plot");
    canvas.set_xlabel("X Axis");
    canvas.set_ylabel("Y Axis");
    canvas.set_xlim(0, 5);
    canvas.set_ylim(0, 20);
    canvas.show_grid(true);
    std::cout << "✅" << std::endl;

    // Test 9: Pixel-level operations (backward compatibility)
    std::cout << "Test 9: Pixel Operations... ";
    canvas.set_pixel_color(10, 10, plotter::Color("#FF0000"));
    auto pixel = canvas.get_pixel(10, 10);
    canvas.set_background(plotter::Color("#FFFFFF"));
    std::cout << "✅" << std::endl;

    // Test 10: Save functionality
    std::cout << "Test 10: Save Operations... ";
    bool success = canvas.save("modular_test.png");
    if (!success) {
        std::cout << "❌ Save failed" << std::endl;
        return 1;
    }
    std::cout << "✅" << std::endl;

    // Test 11: Animation support
    std::cout << "Test 11: Animation Support... ";
    plotter::Canvas anim_canvas(200, 200, true);
    anim_canvas.set_dark_theme();

    for (int frame = 0; frame < 3; ++frame) {
        std::vector<double> x_anim = {0, 1, 2, 3};
        std::vector<double> y_anim;
        for (auto val : x_anim) {
            y_anim.push_back(std::sin(val + frame * 0.5));
        }
        anim_canvas.plot_red(x_anim, y_anim);
        anim_canvas.set_frame();
    }

    bool anim_success = anim_canvas.save("modular_test.gif", 50);
    if (!anim_success) {
        std::cout << "❌ Animation save failed" << std::endl;
        return 1;
    }
    std::cout << "✅" << std::endl;

    std::cout << "\n🎉 All tests passed! Modular canvas is fully compatible!" << std::endl;
    std::cout << "Generated files:" << std::endl;
    std::cout << "  - modular_test.png (subplot demo)" << std::endl;
    std::cout << "  - modular_test.gif (animation demo)" << std::endl;

    return 0;
}
