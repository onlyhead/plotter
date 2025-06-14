#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>
#include <random>

int main() {
    std::cout << "Starting Simple Data Processing Test..." << std::endl;
    std::cout << "=====================================" << std::endl;
    
    // Generate sample data for plotting
    const int data_size = 100;
    std::vector<double> x_data(data_size);
    std::vector<double> sin_data(data_size);
    std::vector<double> cos_data(data_size);
    std::vector<double> exp_data(data_size);
    
    // Fill with sample mathematical functions
    for (int i = 0; i < data_size; ++i) {
        x_data[i] = i * 0.1;
        sin_data[i] = std::sin(x_data[i]);
        cos_data[i] = std::cos(x_data[i]);
        exp_data[i] = std::exp(-x_data[i] * 0.1) * std::sin(x_data[i] * 2.0);
    }
    
    std::cout << "Generated " << data_size << " data points for plotting:" << std::endl;
    
    // Display sample points
    std::cout << "\nSample data points:" << std::endl;
    std::cout << "x\t\tsin(x)\t\tcos(x)\t\texp_decay" << std::endl;
    std::cout << "---\t\t------\t\t------\t\t---------" << std::endl;
    
    for (int i = 0; i < 10; ++i) {
        std::cout << std::fixed << std::setprecision(3) 
                  << x_data[i] << "\t\t"
                  << sin_data[i] << "\t\t"
                  << cos_data[i] << "\t\t"
                  << exp_data[i] << std::endl;
    }
    
    // Generate scatter plot data
    std::vector<double> scatter_x(50), scatter_y(50);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dist(0.0, 1.0);
    
    for (int i = 0; i < 50; ++i) {
        scatter_x[i] = dist(gen);
        scatter_y[i] = dist(gen);
    }
    
    std::cout << "\nGenerated scatter plot data (first 5 points):" << std::endl;
    std::cout << "x\t\ty" << std::endl;
    std::cout << "---\t\t---" << std::endl;
    
    for (int i = 0; i < 5; ++i) {
        std::cout << std::fixed << std::setprecision(3)
                  << scatter_x[i] << "\t\t" << scatter_y[i] << std::endl;
    }
    
    // Calculate some basic statistics
    double sin_min = *std::min_element(sin_data.begin(), sin_data.end());
    double sin_max = *std::max_element(sin_data.begin(), sin_data.end());
    double cos_min = *std::min_element(cos_data.begin(), cos_data.end());
    double cos_max = *std::max_element(cos_data.begin(), cos_data.end());
    
    std::cout << "\nData statistics:" << std::endl;
    std::cout << "sin(x) range: [" << sin_min << ", " << sin_max << "]" << std::endl;
    std::cout << "cos(x) range: [" << cos_min << ", " << cos_max << "]" << std::endl;
    
    // Demonstrate range calculations (similar to ImPlotRange)
    struct DataRange {
        double min, max;
        DataRange(double _min, double _max) : min(_min), max(_max) {}
        double size() const { return max - min; }
        bool contains(double value) const { return value >= min && value <= max; }
        double clamp(double value) const { 
            return (value < min) ? min : (value > max) ? max : value; 
        }
    };
    
    DataRange sin_range(sin_min, sin_max);
    DataRange cos_range(cos_min, cos_max);
    
    std::cout << "\nRange calculations:" << std::endl;
    std::cout << "sin(x) range size: " << sin_range.size() << std::endl;
    std::cout << "cos(x) range size: " << cos_range.size() << std::endl;
    std::cout << "sin_range contains 0.5: " << (sin_range.contains(0.5) ? "Yes" : "No") << std::endl;
    std::cout << "cos_range contains 1.5: " << (cos_range.contains(1.5) ? "Yes" : "No") << std::endl;
    
    std::cout << "\n=====================================" << std::endl;
    std::cout << "Data processing test completed successfully!" << std::endl;
    std::cout << "This data would be suitable for plotting with ImPlot library." << std::endl;
    std::cout << "Next step: Integrate with ImGui/ImPlot for actual visualization." << std::endl;
    
    return 0;
}
