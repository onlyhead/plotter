#pragma once

#include "types.hpp"
#include <string>
#include <vector>

namespace plotter {

    // Subplot structure
    struct Subplot {
        int row, col;
        int x_offset, y_offset;
        int width, height;
        double x_min, x_max, y_min, y_max;
        bool has_data;
        std::vector<Operation> operations;

        // Infrastructure fields for future features
        std::string title, xlabel, ylabel;
        bool show_grid;

        Subplot(int r, int c, int x_off, int y_off, int w, int h)
            : row(r), col(c), x_offset(x_off), y_offset(y_off), width(w), height(h), x_min(0), x_max(1), y_min(0),
              y_max(1), has_data(false), title(""), xlabel(""), ylabel(""), show_grid(false) {}
    };

} // namespace plotter
