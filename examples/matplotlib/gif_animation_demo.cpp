#define _USE_MATH_DEFINES
#include <cmath>
#include <plotter.hpp>

int main() {
    std::cout << "Creating animated GIF with Concord Points..." << std::endl;

    plotter::Plotter plt;

    // Enable animation mode with 200ms per frame
    plt.enable_animation(200);

    // Set up the plot
    plt.figure_size(800, 600);
    plt.xlim(-2, 10);
    plt.ylim(-2, 2);
    plt.title("Animated Sine Wave Growth");
    plt.xlabel("X");
    plt.ylabel("Y");

    // Create animated sine wave that grows over time
    for (int frame = 1; frame <= 20; ++frame) {
        plt.clf(); // Clear previous plot

        // Create sine wave points up to current frame
        std::vector<concord::Point> sine_points;
        for (int i = 0; i <= frame * 5; ++i) {
            double x = i * 0.1;
            double y = std::sin(x);
            sine_points.emplace_back(x, y);
        }

        // Plot with different colors based on frame
        pigment::RGB color;
        if (frame < 7) {
            color = pigment::RGB::blue();
        } else if (frame < 14) {
            color = pigment::RGB::green();
        } else {
            color = pigment::RGB::red();
        }

        plt.plot(sine_points, color);

        // Add current frame info
        std::string frame_title = "Animated Sine Wave - Frame " + std::to_string(frame);
        plt.title(frame_title.c_str());

        // Manually capture this frame after all plot operations
        plt.frame();

        std::cout << "Captured frame " << frame << "/" << 20 << std::endl;
    }

    // Save as animated GIF
    std::cout << "Creating animated GIF..." << std::endl;
    plt.save("animated_sine_wave.gif", true); // animation=true

    // Also save the final frame as a static image
    plt.save("final_sine_wave.png", false); // animation=false

    std::cout << "Animation complete!" << std::endl;
    std::cout << "Created files:" << std::endl;
    std::cout << "- animated_sine_wave.gif (animated)" << std::endl;
    std::cout << "- final_sine_wave.png (static final frame)" << std::endl;

    return 0;
}
