#pragma once

#include "../core/types.hpp"
#include <pigment/named_colors.hpp>
#include <string>
#include <vector>

namespace plotter {

    class PlotInterface {
      public:
        // Named color convenience methods
        static void plot_red(std::vector<Operation> &operations, const std::vector<double> &xs,
                             const std::vector<double> &ys) {
            operations.push_back({OperationType::PLOT, xs, ys, pigment::colors::red()});
        }

        static void plot_blue(std::vector<Operation> &operations, const std::vector<double> &xs,
                              const std::vector<double> &ys) {
            operations.push_back({OperationType::PLOT, xs, ys, pigment::colors::blue()});
        }

        static void plot_green(std::vector<Operation> &operations, const std::vector<double> &xs,
                               const std::vector<double> &ys) {
            operations.push_back({OperationType::PLOT, xs, ys, pigment::colors::green()});
        }

        static void plot_orange(std::vector<Operation> &operations, const std::vector<double> &xs,
                                const std::vector<double> &ys) {
            operations.push_back({OperationType::PLOT, xs, ys, pigment::colors::orange()});
        }

        static void plot_purple(std::vector<Operation> &operations, const std::vector<double> &xs,
                                const std::vector<double> &ys) {
            operations.push_back({OperationType::PLOT, xs, ys, pigment::colors::purple()});
        }

        static void plot_cyan(std::vector<Operation> &operations, const std::vector<double> &xs,
                              const std::vector<double> &ys) {
            operations.push_back({OperationType::PLOT, xs, ys, pigment::colors::cyan()});
        }

        static void plot_with_named_color(std::vector<Operation> &operations, const std::vector<double> &xs,
                                          const std::vector<double> &ys, const std::string &color_name) {
            Color c = pigment::colors::red(); // Default to red if color name not found

            if (color_name == "red")
                c = pigment::colors::red();
            else if (color_name == "green")
                c = pigment::colors::green();
            else if (color_name == "blue")
                c = pigment::colors::blue();
            else if (color_name == "orange")
                c = pigment::colors::orange();
            else if (color_name == "purple")
                c = pigment::colors::purple();
            else if (color_name == "cyan")
                c = pigment::colors::cyan();
            else if (color_name == "yellow")
                c = pigment::colors::yellow();
            else if (color_name == "pink")
                c = pigment::colors::pink();
            else if (color_name == "brown")
                c = pigment::colors::brown();
            else if (color_name == "gray")
                c = pigment::colors::gray();
            else if (color_name == "black")
                c = pigment::colors::black();
            else if (color_name == "white")
                c = pigment::colors::white();

            operations.push_back({OperationType::PLOT, xs, ys, c});
        }
    };

} // namespace plotter
