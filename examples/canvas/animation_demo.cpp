#include <canvas.hpp>
#include <cmath>
#include <iostream>
#include <vector>

int main() {
    std::cout << "=== Canvas Animation Demo (GIF Creation) ===" << std::endl;

    // Create an animated canvas
    plotter::Canvas canvas(400, 300, true); // true = animated
    canvas.set_dark_theme();

    // Set canvas title
    canvas.set_canvas_title("Animated Wave Functions");

    // Generate data for animation
    std::vector<double> x;
    for (int i = 0; i < 100; ++i) {
        x.push_back(i * 0.1);
    }

    // Create 20 frames of animation
    const int num_frames = 20;
    for (int frame = 0; frame < num_frames; ++frame) {
        std::cout << "Generating frame " << (frame + 1) << "/" << num_frames << std::endl;

        // Calculate phase shift for this frame
        double phase = frame * 2.0 * M_PI / num_frames;

        // Generate animated sine wave data
        std::vector<double> y_sin, y_cos;
        for (double xi : x) {
            y_sin.push_back(std::sin(xi + phase));
            y_cos.push_back(std::cos(xi + phase * 0.7) * 0.8);
        }

        // Plot the waves
        canvas.plot(x, y_sin, {255, 100, 100, 255}); // Red sine wave
        canvas.plot(x, y_cos, {100, 255, 100, 255}); // Green cosine wave

        // Add some animated text
        canvas::TextStyle text_style;
        text_style.color = {255, 255, 255, 255};
        text_style.font_size = 16;
        text_style.align = canvas::TextAlign::CENTER;
        text_style.baseline = canvas::TextBaseline::MIDDLE;

        std::string frame_text = "Frame " + std::to_string(frame + 1);
        canvas.draw_text_pixel(200, 250, frame_text, text_style);

        // Add animated moving dot
        int dot_x = 50 + (int)(300 * frame / (double)num_frames);
        int dot_y = 150 + (int)(50 * std::sin(phase));
        for (int dy = -3; dy <= 3; dy++) {
            for (int dx = -3; dx <= 3; dx++) {
                if (dx * dx + dy * dy <= 9) {
                    canvas.set_pixel_color(dot_x + dx, dot_y + dy, {255, 255, 0, 255});
                }
            }
        }

        // Capture this frame
        canvas.set_frame();
    }

    // Save as animated GIF
    canvas.save("animation_demo.gif", 20); // 20 = delay in centiseconds (0.2 seconds per frame)

    std::cout << "Animation demo completed! Output saved to animation_demo.gif" << std::endl;
    std::cout << "Features demonstrated:" << std::endl;
    std::cout << "- Animated plotting with multiple data series" << std::endl;
    std::cout << "- GIF creation with multiple frames" << std::endl;
    std::cout << "- Canvas title on animated content" << std::endl;
    std::cout << "- Animated text and graphics elements" << std::endl;
    std::cout << "- Phase-shifted wave animation" << std::endl;

    return 0;
}
