#include <plotter.hpp>
#include <iostream>

int main() {
    std::cout << "Testing manual vs automatic frame capture..." << std::endl;

    plotter::Plotter plt;
    
    // Enable animation mode
    plt.enable_animation(100);
    plt.figure_size(400, 300);
    plt.xlim(0, 5);
    plt.ylim(0, 5);
    
    std::cout << "Initial frame count: " << plt.frame_count() << std::endl;
    
    // Make multiple plot calls - should NOT create frames automatically
    plt.plot_rectangle(0, 0, 1, 1, pigment::RGB::red());
    std::cout << "After first rectangle: " << plt.frame_count() << " frames" << std::endl;
    
    plt.plot_rectangle(1, 1, 1, 1, pigment::RGB::green());
    std::cout << "After second rectangle: " << plt.frame_count() << " frames" << std::endl;
    
    plt.plot_rectangle(2, 2, 1, 1, pigment::RGB::blue());
    std::cout << "After third rectangle: " << plt.frame_count() << " frames" << std::endl;
    
    // Now manually capture the frame
    plt.frame();
    std::cout << "After manual frame(): " << plt.frame_count() << " frames" << std::endl;
    
    // Clear and add more rectangles
    plt.clf();
    plt.plot_rectangle(0, 0, 2, 2, pigment::RGB::yellow());
    plt.plot_rectangle(2, 2, 2, 2, pigment::RGB::cyan());
    std::cout << "After more rectangles: " << plt.frame_count() << " frames" << std::endl;
    
    // Capture second frame
    plt.frame();
    std::cout << "After second manual frame(): " << plt.frame_count() << " frames" << std::endl;
    
    if (plt.frame_count() == 2) {
        std::cout << "✅ SUCCESS: Manual frame capture works correctly!" << std::endl;
        std::cout << "   - Multiple plot calls don't create automatic frames" << std::endl;
        std::cout << "   - Manual frame() calls create exactly one frame each" << std::endl;
    } else {
        std::cout << "❌ FAILURE: Expected 2 frames, got " << plt.frame_count() << std::endl;
    }
    
    return 0;
}
