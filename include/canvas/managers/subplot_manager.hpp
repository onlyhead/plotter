#pragma once

#include "../core/subplot.hpp"
#include "../core/theme.hpp"
#include <utility>
#include <vector>

namespace plotter {

    class SubplotManager {
      private:
        int width_, height_;
        int rows_, cols_;
        std::vector<Subplot> subplots_;
        std::pair<int, int> current_subplot_;

      public:
        SubplotManager(int width, int height)
            : width_(width), height_(height), rows_(1), cols_(1), current_subplot_(0, 0) {}

        void create_subplots(int rows, int cols) {
            rows_ = rows;
            cols_ = cols;
            subplots_.clear();

            int subplot_width = width_ / cols;
            int subplot_height = height_ / rows;

            for (int r = 0; r < rows; ++r) {
                for (int c = 0; c < cols; ++c) {
                    int x_offset = c * subplot_width;
                    int y_offset = r * subplot_height;
                    subplots_.emplace_back(r, c, x_offset, y_offset, subplot_width, subplot_height);
                }
            }

            // Set current subplot to first one
            current_subplot_ = {0, 0};
        }

        void set_current_subplot(int row, int col) {
            if (row >= 0 && row < rows_ && col >= 0 && col < cols_) {
                current_subplot_ = {row, col};
            }
        }

        Subplot &get_current_subplot() {
            int index = current_subplot_.first * cols_ + current_subplot_.second;
            return subplots_[index];
        }

        const Subplot &get_current_subplot() const {
            int index = current_subplot_.first * cols_ + current_subplot_.second;
            return subplots_[index];
        }

        const std::vector<Subplot> &get_all_subplots() const { return subplots_; }

        std::vector<Subplot> &get_all_subplots() { return subplots_; }

        std::pair<int, int> get_current_subplot_index() const { return current_subplot_; }

        std::pair<int, int> get_layout() const { return {rows_, cols_}; }

        int get_subplot_count() const { return subplots_.size(); }

        void clear_all_operations() {
            for (auto &subplot : subplots_) {
                subplot.operations.clear();
            }
        }

        // Coordinate conversion methods
        std::pair<int, int> normalize_to_pixel(double x, double y, const Subplot &subplot) {
            // Convert normalized coordinates (0-1) to pixel coordinates within subplot bounds
            int pixel_x = static_cast<int>(subplot.x_offset + x * subplot.width);
            int pixel_y =
                static_cast<int>(subplot.y_offset + (1.0 - y) * subplot.height); // Flip Y for screen coordinates
            return {pixel_x, pixel_y};
        }

        std::pair<double, double> pixel_to_normalize(int pixel_x, int pixel_y, const Subplot &subplot) {
            // Convert pixel coordinates to normalized coordinates (0-1) within subplot
            double x = static_cast<double>(pixel_x - subplot.x_offset) / subplot.width;
            double y = 1.0 - static_cast<double>(pixel_y - subplot.y_offset) / subplot.height; // Flip Y back
            return {x, y};
        }
    };

} // namespace plotter
