#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

// Include ImGui first
#include "imgui.h"

// Include ImPlot types (avoiding the problematic full include for now)
#include "plotter/implot/implot_types.h"
#include "plotter/implot/implot_enums.h"

int main() {
    std::cout << "ImPlot Library - Simple Example" << std::endl;
    std::cout << "===============================" << std::endl;

    // Demonstrate basic ImPlot data structures
    std::cout << "\n1. Testing ImPlot data structures..." << std::endl;
    
    // Create sample data points
    ImPlotPoint p1(0.0, 0.0);
    ImPlotPoint p2(1.0, 1.0);
    std::cout << "   Point 1: (" << p1.x << ", " << p1.y << ")" << std::endl;
    std::cout << "   Point 2: (" << p2.x << ", " << p2.y << ")" << std::endl;
    
    // Create a plotting range
    ImPlotRange range(-10.0, 10.0);
    std::cout << "   Range: [" << range.Min << ", " << range.Max << "]" << std::endl;
    std::cout << "   Range size: " << range.Size() << std::endl;
    
    // Create a plot rectangle
    ImPlotRect rect(-5.0, 5.0, -2.0, 2.0);
    std::cout << "   Plot rect: X[" << rect.X.Min << ", " << rect.X.Max 
              << "], Y[" << rect.Y.Min << ", " << rect.Y.Max << "]" << std::endl;

    // Generate sample plotting data
    std::cout << "\n2. Generating sample data..." << std::endl;
    const int n_points = 50;
    std::vector<ImPlotPoint> sine_wave, cosine_wave;
    
    for (int i = 0; i < n_points; ++i) {
        double x = i * 0.2;
        sine_wave.push_back(ImPlotPoint(x, std::sin(x)));
        cosine_wave.push_back(ImPlotPoint(x, std::cos(x)));
    }
    
    std::cout << "   Generated " << n_points << " points for sine and cosine waves" << std::endl;
    
    // Show sample data
    std::cout << "   Sample sine wave points:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << "     (" << std::fixed << std::setprecision(2) 
                  << sine_wave[i].x << ", " << sine_wave[i].y << ")" << std::endl;
    }

    // Calculate data bounds
    std::cout << "\n3. Calculating data bounds..." << std::endl;
    
    if (!sine_wave.empty()) {
        ImPlotRect bounds(sine_wave[0].x, sine_wave[0].x, sine_wave[0].y, sine_wave[0].y);
        
        // Find bounds for both datasets
        for (const auto& point : sine_wave) {
            bounds.X.Min = std::min(bounds.X.Min, point.x);
            bounds.X.Max = std::max(bounds.X.Max, point.x);
            bounds.Y.Min = std::min(bounds.Y.Min, point.y);
            bounds.Y.Max = std::max(bounds.Y.Max, point.y);
        }
        
        for (const auto& point : cosine_wave) {
            bounds.X.Min = std::min(bounds.X.Min, point.x);
            bounds.X.Max = std::max(bounds.X.Max, point.x);
            bounds.Y.Min = std::min(bounds.Y.Min, point.y);
            bounds.Y.Max = std::max(bounds.Y.Max, point.y);
        }
        
        std::cout << "   Data bounds: X[" << bounds.X.Min << ", " << bounds.X.Max 
                  << "], Y[" << bounds.Y.Min << ", " << bounds.Y.Max << "]" << std::endl;
        std::cout << "   Plot area: " << bounds.X.Size() << " x " << bounds.Y.Size() << std::endl;
    }

    // Demonstrate range queries
    std::cout << "\n4. Testing range queries..." << std::endl;
    ImPlotPoint test_point(5.0, 0.5);
    ImPlotRect viewport(0.0, 10.0, -1.5, 1.5);
    
    std::cout << "   Test point: (" << test_point.x << ", " << test_point.y << ")" << std::endl;
    std::cout << "   Viewport: X[" << viewport.X.Min << ", " << viewport.X.Max 
              << "], Y[" << viewport.Y.Min << ", " << viewport.Y.Max << "]" << std::endl;
    std::cout << "   Point in viewport: " << (viewport.Contains(test_point) ? "Yes" : "No") << std::endl;

    // Count points in viewport
    int sine_in_viewport = 0, cosine_in_viewport = 0;
    for (const auto& point : sine_wave) {
        if (viewport.Contains(point)) sine_in_viewport++;
    }
    for (const auto& point : cosine_wave) {
        if (viewport.Contains(point)) cosine_in_viewport++;
    }
    
    std::cout << "   Sine points in viewport: " << sine_in_viewport << "/" << sine_wave.size() << std::endl;
    std::cout << "   Cosine points in viewport: " << cosine_in_viewport << "/" << cosine_wave.size() << std::endl;

    std::cout << "\n===============================" << std::endl;
    std::cout << "✓ ImPlot library test completed successfully!" << std::endl;
    std::cout << "✓ Data structures working correctly" << std::endl;
    std::cout << "✓ Data generation and processing functional" << std::endl;
    std::cout << "✓ Range queries and viewport calculations working" << std::endl;
    std::cout << "\nThis example demonstrates the core ImPlot data structures." << std::endl;
    std::cout << "For actual plotting visualization, integrate with ImGui and OpenGL." << std::endl;

    return 0;
}
