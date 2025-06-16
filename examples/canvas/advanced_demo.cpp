#include <canvas/canvas.hpp>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

int main() {
    // Create an animated canvas to show Pigment/Concord integration
    plotter::Canvas canvas(500, 400, true); // Enable animation

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    // Create a color palette using Pigment
    std::vector<plotter::Color> palette = {
        plotter::Color("#FF6B6B"), // Coral red
        plotter::Color("#4ECDC4"), // Turquoise
        plotter::Color("#45B7D1"), // Sky blue
        plotter::Color("#F9CA24"), // Golden yellow
        plotter::Color("#6C5CE7"), // Purple
        plotter::Color("#A0E7E5"), // Light cyan
        plotter::Color("#FD79A8"), // Pink
        plotter::Color("#FDCB6E")  // Light orange
    };

    // Generate multiple animation frames
    for (int frame = 0; frame < 20; ++frame) {
        // Set a gradient background color that changes over time
        int bg_intensity = 200 + (int)(30 * std::sin(frame * 0.3));
        canvas.set_background(plotter::Color(bg_intensity, bg_intensity, bg_intensity + 20));

        // Create multiple animated sine waves with different frequencies and colors
        for (int wave = 0; wave < 5; ++wave) {
            std::vector<double> x, y;
            plotter::Color wave_color = palette[wave % palette.size()];

            for (int i = 0; i < 100; ++i) {
                double t = i * 0.1;
                double phase = frame * 0.2 + wave * 0.8;
                double frequency = 1.0 + wave * 0.3;
                double amplitude = 0.3 + wave * 0.1;

                x.push_back(t);
                y.push_back(amplitude * std::sin(frequency * t + phase) + wave * 0.2);
            }

            canvas.plot(x, y, wave_color);
        }

        // Add some animated dots using the Concord grid pixel functionality
        for (int i = 0; i < 50; ++i) {
            int px = (int)(250 + 100 * std::cos(frame * 0.1 + i * 0.3));
            int py = (int)(200 + 50 * std::sin(frame * 0.15 + i * 0.4));

            if (px >= 0 && px < 500 && py >= 0 && py < 400) {
                plotter::Color dot_color = palette[i % palette.size()];
                // Fade the alpha based on frame
                dot_color.a = (uint8_t)(128 + 127 * std::sin(frame * 0.2 + i * 0.1));
                canvas.set_pixel_color(px, py, dot_color);
            }
        }

        // Set this frame in the animation
        canvas.set_frame();

        std::cout << "Generated frame " << (frame + 1) << "/20" << std::endl;
    }

    // Save as animated GIF
    bool success = canvas.save("animated_demo.gif", 5); // 5 centiseconds delay between frames

    if (success) {
        std::cout << "\nAnimated GIF saved successfully as 'animated_demo.gif'" << std::endl;
        std::cout << "This advanced demo showcases:" << std::endl;
        std::cout << "- Animated canvas with multiple frames" << std::endl;
        std::cout << "- Rich color palette using Pigment hex colors" << std::endl;
        std::cout << "- Dynamic background color changes" << std::endl;
        std::cout << "- Multiple overlapping animated sine waves" << std::endl;
        std::cout << "- Pixel-level animation using Concord Grid" << std::endl;
        std::cout << "- Alpha transparency support from Pigment RGB" << std::endl;
    } else {
        std::cout << "Failed to save animated canvas" << std::endl;
        return 1;
    }

    return 0;
}
