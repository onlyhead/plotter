#define _USE_MATH_DEFINES
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>

// For demonstration purposes, let's show the concept with a mock interface
// In the actual implementation, this would be: #include <plotter.hpp>

namespace plotter {
    // This is a conceptual example showing how the class-based interface would work
    class Plotter {
      private:
        long figure_num_;
        static long next_figure_num_;

      public:
        Plotter() : figure_num_(next_figure_num_++) {
            std::cout << "Created plotter instance with figure " << figure_num_ << std::endl;
        }

        long figure_number() const { return figure_num_; }

        template <typename T1, typename T2>
        void plot(const std::vector<T1> &x, const std::vector<T2> &y, const char *format = "") {
            std::cout << "Plotting on figure " << figure_num_ << " with " << x.size() << " points";
            if (format && strlen(format) > 0) {
                std::cout << " using format: " << format;
            }
            std::cout << std::endl;
        }

        void title(const char *title) {
            std::cout << "Setting title for figure " << figure_num_ << ": " << title << std::endl;
        }

        void xlabel(const char *label) {
            std::cout << "Setting xlabel for figure " << figure_num_ << ": " << label << std::endl;
        }

        void ylabel(const char *label) {
            std::cout << "Setting ylabel for figure " << figure_num_ << ": " << label << std::endl;
        }

        void save(const char *filename) {
            std::cout << "Saving figure " << figure_num_ << " to: " << filename << std::endl;
        }
    };

    long Plotter::next_figure_num_ = 1;
} // namespace plotter

int main() {
    std::cout << "=== Demonstrating Class-Based Plotter Interface ===" << std::endl;

    // Create two separate plotter instances
    plotter::Plotter plot1;
    plotter::Plotter plot2;

    std::cout << "Plot 1 figure number: " << plot1.figure_number() << std::endl;
    std::cout << "Plot 2 figure number: " << plot2.figure_number() << std::endl;

    // Prepare data for first plot
    int n = 100;
    std::vector<double> x1(n), y1(n);
    for (int i = 0; i < n; ++i) {
        x1[i] = i * 0.1;
        y1[i] = sin(x1[i]);
    }

    // Prepare data for second plot
    std::vector<double> x2(n), y2(n);
    for (int i = 0; i < n; ++i) {
        x2[i] = i * 0.1;
        y2[i] = cos(x2[i]);
    }

    std::cout << "\n=== Plotting on first instance ===" << std::endl;
    plot1.plot(x1, y1);
    plot1.title("Sine Wave");
    plot1.xlabel("X");
    plot1.ylabel("sin(x)");
    plot1.save("sine_plot.png");

    std::cout << "\n=== Plotting on second instance ===" << std::endl;
    plot2.plot(x2, y2, "r-");
    plot2.title("Cosine Wave");
    plot2.xlabel("X");
    plot2.ylabel("cos(x)");
    plot2.save("cosine_plot.png");

    std::cout << "\n=== Creating multiple plots in a loop ===" << std::endl;
    std::vector<plotter::Plotter> plots;
    for (int i = 0; i < 3; ++i) {
        plots.emplace_back();
        std::vector<double> data = {1.0 * i, 2.0 * i, 3.0 * i, 4.0 * i};
        std::vector<double> indices = {0, 1, 2, 3};
        plots[i].plot(indices, data);
        plots[i].title(("Dataset " + std::to_string(i)).c_str());
        plots[i].save(("dataset_" + std::to_string(i) + ".png").c_str());
    }

    std::cout << "\n=== Summary ===" << std::endl;
    std::cout << "Successfully demonstrated class-based interface!" << std::endl;
    std::cout << "- Created multiple independent plotter instances" << std::endl;
    std::cout << "- Each instance manages its own figure number" << std::endl;
    std::cout << "- Can plot simultaneously on different instances" << std::endl;
    std::cout << "- Supports all the same plotting operations" << std::endl;

    return 0;
}
