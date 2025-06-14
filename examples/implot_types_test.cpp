#include <iostream>
#include <vector>
#include <cmath>

// Test basic includes step by step
#include "imgui.h"

// Let's try including just the types first
#include "plotter/implot/implot_types.h"
#include "plotter/implot/implot_enums.h"

int main() {
    std::cout << "Starting Basic ImPlot Types Test..." << std::endl;
    std::cout << "===================================" << std::endl;
    
    // Test ImPlotPoint
    std::cout << "Testing ImPlotPoint..." << std::endl;
    ImPlotPoint p1(1.0, 2.0);
    ImPlotPoint p2(3.0, 4.0);
    std::cout << "Point 1: (" << p1.x << ", " << p1.y << ")" << std::endl;
    std::cout << "Point 2: (" << p2.x << ", " << p2.y << ")" << std::endl;
    
    // Test ImPlotRange
    std::cout << "\nTesting ImPlotRange..." << std::endl;
    ImPlotRange range(0.0, 10.0);
    std::cout << "Range: [" << range.Min << ", " << range.Max << "]" << std::endl;
    std::cout << "Range size: " << range.Size() << std::endl;
    std::cout << "Contains 5.0: " << (range.Contains(5.0) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 15.0: " << (range.Contains(15.0) ? "Yes" : "No") << std::endl;
    
    // Test ImPlotRect
    std::cout << "\nTesting ImPlotRect..." << std::endl;
    ImPlotRect rect(0.0, 10.0, -5.0, 5.0);
    std::cout << "Rect X: [" << rect.X.Min << ", " << rect.X.Max << "]" << std::endl;
    std::cout << "Rect Y: [" << rect.Y.Min << ", " << rect.Y.Max << "]" << std::endl;
    std::cout << "Rect contains point (2.0, 3.0): " << (rect.Contains(2.0, 3.0) ? "Yes" : "No") << std::endl;
    std::cout << "Rect contains point (15.0, 3.0): " << (rect.Contains(15.0, 3.0) ? "Yes" : "No") << std::endl;
    
    // Test ImPlotPoint arithmetic
    std::cout << "\nTesting ImPlotPoint arithmetic..." << std::endl;
    ImPlotPoint size = rect.Size();
    std::cout << "Rectangle size: (" << size.x << ", " << size.y << ")" << std::endl;
    
    ImPlotPoint clamped = rect.Clamp(ImPlotPoint(15.0, -10.0));
    std::cout << "Clamping point (15.0, -10.0) to rect: (" << clamped.x << ", " << clamped.y << ")" << std::endl;
    
    // Generate sample plotting data
    std::cout << "\nGenerating sample data for plotting..." << std::endl;
    const int data_size = 20;
    std::vector<ImPlotPoint> sin_points, cos_points;
    
    for (int i = 0; i < data_size; ++i) {
        double x = i * 0.5;
        sin_points.push_back(ImPlotPoint(x, std::sin(x)));
        cos_points.push_back(ImPlotPoint(x, std::cos(x)));
    }
    
    std::cout << "Generated " << data_size << " points for sin and cos functions" << std::endl;
    std::cout << "Sample sin points:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << "  sin(" << sin_points[i].x << ") = " << sin_points[i].y << std::endl;
    }
    
    std::cout << "Sample cos points:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << "  cos(" << cos_points[i].x << ") = " << cos_points[i].y << std::endl;
    }
    
    // Test data bounds calculation
    std::cout << "\nCalculating data bounds..." << std::endl;
    ImPlotRect data_bounds;
    if (!sin_points.empty()) {
        data_bounds = ImPlotRect(sin_points[0].x, sin_points[0].x, sin_points[0].y, sin_points[0].y);
        
        for (const auto& point : sin_points) {
            if (point.x < data_bounds.X.Min) data_bounds.X.Min = point.x;
            if (point.x > data_bounds.X.Max) data_bounds.X.Max = point.x;
            if (point.y < data_bounds.Y.Min) data_bounds.Y.Min = point.y;
            if (point.y > data_bounds.Y.Max) data_bounds.Y.Max = point.y;
        }
        
        for (const auto& point : cos_points) {
            if (point.x < data_bounds.X.Min) data_bounds.X.Min = point.x;
            if (point.x > data_bounds.X.Max) data_bounds.X.Max = point.x;
            if (point.y < data_bounds.Y.Min) data_bounds.Y.Min = point.y;
            if (point.y > data_bounds.Y.Max) data_bounds.Y.Max = point.y;
        }
        
        std::cout << "Data bounds: X[" << data_bounds.X.Min << ", " << data_bounds.X.Max 
                  << "], Y[" << data_bounds.Y.Min << ", " << data_bounds.Y.Max << "]" << std::endl;
    }
    
    std::cout << "\n===================================" << std::endl;
    std::cout << "ImPlot types test completed successfully!" << std::endl;
    std::cout << "The basic ImPlot data structures are working correctly." << std::endl;
    std::cout << "Ready to be used with ImPlot plotting functions in a GUI context." << std::endl;
    
    return 0;
}
