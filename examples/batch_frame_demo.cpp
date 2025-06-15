#include <iostream>
#include <plotter.hpp>

int main() {
    std::cout << "Demonstrating batch plotting with manual frame capture..." << std::endl;

    plotter::Plotter plt;

    // Enable animation mode
    plt.enable_animation(500); // 500ms per frame

    // Set up the plot
    plt.figure_size(800, 600);
    plt.xlim(0, 10);
    plt.ylim(0, 10);
    plt.title("Grid Animation - Multiple Rectangles Per Frame");

    // Create animation with growing grid
    for (int frame = 1; frame <= 5; ++frame) {
        plt.clf(); // Clear previous frame

        std::cout << "Creating frame " << frame << " with " << (frame * frame) << " rectangles..." << std::endl;

        // Plot multiple rectangles in this frame
        for (int i = 0; i < frame; ++i) {
            for (int j = 0; j < frame; ++j) {
                double x = i * 2.0;
                double y = j * 2.0;
                double width = 1.5;
                double height = 1.5;

                // Use different colors based on position
                pigment::RGB color;
                if ((i + j) % 3 == 0) {
                    color = pigment::RGB::red();
                } else if ((i + j) % 3 == 1) {
                    color = pigment::RGB::green();
                } else {
                    color = pigment::RGB::blue();
                }

                plt.plot_rectangle(x, y, width, height, color);
            }
        }

        // Add frame title
        std::string frame_title = "Grid " + std::to_string(frame) + "x" + std::to_string(frame) + " (" +
                                  std::to_string(frame * frame) + " rectangles)";
        plt.title(frame_title.c_str());

        // NOW capture this as a single frame (after all rectangles are plotted)
        plt.frame();

        std::cout << "Frame " << frame << " captured!" << std::endl;
    }

    std::cout << "Total frames captured: " << plt.frame_count() << std::endl;

    // Save as animated GIF
    plt.save("batch_frame_demo.gif", true);

    std::cout << "Animation saved as batch_frame_demo.gif" << std::endl;

    return 0;
}
