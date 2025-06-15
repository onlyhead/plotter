#include <plotter.hpp>
#include <iostream>

int main() {
    plotter::Plotter plt;
    
    std::cout << "Simple GIF Animation Example" << std::endl;
    
    // Enable animation mode
    plt.enable_animation(300);  // 300ms per frame
    
    // Create 5 simple frames
    for (int i = 1; i <= 5; ++i) {
        plt.clf();  // Clear plot
        
        // Create simple moving point
        std::vector<concord::Point> points;
        points.emplace_back(i, i);  // Point moves diagonally
        points.emplace_back(i+1, i+0.5);
        
        plt.plot(points, pigment::RGB::blue());
        plt.xlim(0, 6);
        plt.ylim(0, 6);
        plt.title("Simple Animation");
        
        std::cout << "Frame " << i << " captured" << std::endl;
    }
    
    // Check frame count
    std::cout << "Total frames captured: " << plt.frame_count() << std::endl;
    
    // Save as GIF
    if (plt.is_animation_enabled()) {
        plt.save("simple_animation.gif", true);
        std::cout << "GIF saved!" << std::endl;
    }
    
    return 0;
}
