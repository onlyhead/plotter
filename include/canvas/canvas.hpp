#pragma once

#ifndef PLOTPP_HPP
#define PLOTPP_HPP

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "io/img.hpp"

#define GIF_H_IMPLEMENTATION
#include "io/gif.hpp"

// Include Pigment and Concord libraries
#include <concord/concord.hpp>
#include <pigment/pigment.hpp>
#include <pigment/named_colors.hpp>

namespace plotter {

    using Color = pigment::RGB;

    // Operation structure for plotting data
    struct Operation {
        std::vector<double> xs, ys;
        Color c;
    };

    // Theme definitions
    struct Theme {
        Color background;
        Color grid_color;
        Color text_color;
        Color border_color;
        pigment::Palette plot_colors;

        // Predefined themes using Pigment named colors and palettes
        static Theme light() {
            return {
                pigment::colors::white(),           // white background
                pigment::colors::lightgray(),       // light gray grid
                pigment::colors::black(),           // black text
                pigment::colors::silver(),          // silver border
                pigment::Palette::material_design() // material design palette
            };
        }

        static Theme dark() {
            return {
                pigment::colors::darkslategray(),   // dark gray background
                pigment::colors::dimgray(),         // medium gray grid
                pigment::colors::white(),           // white text
                pigment::colors::gray(),            // gray border
                pigment::Palette::cool()            // cool color palette for dark theme
            };
        }

        static Theme vibrant() {
            return {
                pigment::colors::black(),           // black background
                pigment::colors::darkgray(),        // dark gray grid
                pigment::colors::white(),           // white text
                pigment::colors::silver(),          // silver border
                pigment::Palette::vibrant(6)       // vibrant colors
            };
        }
    };

    // Subplot structure
    struct Subplot {
        int row, col;
        int x_offset, y_offset;
        int width, height;
        double x_min, x_max, y_min, y_max;
        bool has_data;
        std::vector<Operation> operations;

        // New members for titles, labels, and grid support
        std::string title, xlabel, ylabel;
        bool show_grid;

        Subplot(int r, int c, int x_off, int y_off, int w, int h)
            : row(r), col(c), x_offset(x_off), y_offset(y_off), width(w), height(h), x_min(0), x_max(1), y_min(0),
              y_max(1), has_data(false), title(""), xlabel(""), ylabel(""), show_grid(false) {}
    };

    class Canvas {
      public:
        Canvas(int w, int h, bool animate = false)
            : width(w), height(h), animated(animate), pixels(w * h * 4, 255), current_theme(Theme::light()),
              subplot_rows(1), subplot_cols(1), current_subplot(0, 0) {
            // Initialize grid with the canvas dimensions
            // Grid constructor: Grid(rows, cols, diameter, datum, centered, pose)
            grid = std::make_unique<concord::Grid<Color>>(h, w, 1.0, concord::Datum(), false, concord::Pose{});

            // Initialize with single subplot covering entire canvas
            create_subplots(1, 1);
            set_background(current_theme.background);
        }

        // Theme management
        void set_theme(const Theme &theme) {
            current_theme = theme;
            set_background(current_theme.background);
        }

        void set_dark_theme() { set_theme(Theme::dark()); }
        void set_light_theme() { set_theme(Theme::light()); }

        // Subplot management
        void create_subplots(int rows, int cols) {
            subplot_rows = rows;
            subplot_cols = cols;
            subplots.clear();

            int subplot_width = width / cols;
            int subplot_height = height / rows;

            for (int r = 0; r < rows; ++r) {
                for (int c = 0; c < cols; ++c) {
                    int x_offset = c * subplot_width;
                    int y_offset = r * subplot_height;
                    subplots.emplace_back(r, c, x_offset, y_offset, subplot_width, subplot_height);
                }
            }

            // Set current subplot to first one
            current_subplot = {0, 0};
        }

        void subplot(int row, int col) {
            if (row >= 0 && row < subplot_rows && col >= 0 && col < subplot_cols) {
                current_subplot = {row, col};
            }
        }

        // Enhanced plotting with subplot support
        void plot(const std::vector<double> &xs, const std::vector<double> &ys, Color c = Color()) {
            if (c == Color()) {
                // Use theme colors if no color specified
                int color_index = get_current_subplot().operations.size() % current_theme.plot_colors.size();
                c = current_theme.plot_colors[color_index];
            }

            Subplot &subplot = get_current_subplot();
            subplot.operations.push_back({xs, ys, c});
            subplot.has_data = true;
        }

        // Add method to set background color using Pigment
        void set_background(const Color &bg) { background_color = bg; }

        // Add method to get a pixel color from the grid
        Color get_pixel(int x, int y) const {
            if (x < 0 || x >= width || y < 0 || y >= height) {
                return background_color;
            }
            return (*grid)(y, x).second; // Grid uses (row, col) indexing
        }

        // Add method to set a pixel using both pixel buffer and grid
        void set_pixel_color(int x, int y, const Color &c) {
            if (x < 0 || x >= width || y < 0 || y >= height)
                return;

            // Update the grid
            (*grid)(y, x).second = c;

            // Update pixel buffer for rendering
            set_pixel(x, y, c);
        }

        void set_frame() {
            render();
            if (animated) {
                frames.emplace_back(pixels);
            }
            // Clear operations from all subplots
            for (auto &subplot : subplots) {
                subplot.operations.clear();
            }
        }

        void show() {
            render();
            // Clear operations from all subplots
            for (auto &subplot : subplots) {
                subplot.operations.clear();
            }
        }

        bool save(const std::string &fname, int delay_cs = 10) {
            if (animated) {
                if (!ops.empty()) {
                    render();
                    frames.emplace_back(pixels);
                    ops.clear();
                }
                GifWriter writer;
                if (!GifBegin(&writer, fname.c_str(), width, height, delay_cs))
                    return false;
                for (auto &f : frames)
                    GifWriteFrame(&writer, f.data(), width, height, delay_cs);
                return GifEnd(&writer);
            } else {
                render();
                return stbi_write_png(fname.c_str(), width, height, 4, pixels.data(), width * 4) != 0;
            }
        }

        // Add utility methods for working with Pigment colors
        void plot_with_named_color(const std::vector<double> &xs, const std::vector<double> &ys,
                                   const std::string &color_name) {
            Color c = pigment::colors::red(); // Default to red if color name not found
            
            if (color_name == "red") c = pigment::colors::red();
            else if (color_name == "green") c = pigment::colors::green();
            else if (color_name == "blue") c = pigment::colors::blue();
            else if (color_name == "orange") c = pigment::colors::orange();
            else if (color_name == "purple") c = pigment::colors::purple();
            else if (color_name == "cyan") c = pigment::colors::cyan();
            else if (color_name == "yellow") c = pigment::colors::yellow();
            else if (color_name == "pink") c = pigment::colors::pink();
            else if (color_name == "brown") c = pigment::colors::brown();
            else if (color_name == "gray") c = pigment::colors::gray();
            else if (color_name == "black") c = pigment::colors::black();
            else if (color_name == "white") c = pigment::colors::white();
            
            plot(xs, ys, c);
        }

        // Convenience methods for named colors
        void plot_red(const std::vector<double> &xs, const std::vector<double> &ys) {
            plot(xs, ys, pigment::colors::red());
        }
        
        void plot_blue(const std::vector<double> &xs, const std::vector<double> &ys) {
            plot(xs, ys, pigment::colors::blue());
        }
        
        void plot_green(const std::vector<double> &xs, const std::vector<double> &ys) {
            plot(xs, ys, pigment::colors::green());
        }
        
        void plot_orange(const std::vector<double> &xs, const std::vector<double> &ys) {
            plot(xs, ys, pigment::colors::orange());
        }
        
        void plot_purple(const std::vector<double> &xs, const std::vector<double> &ys) {
            plot(xs, ys, pigment::colors::purple());
        }
        
        void plot_cyan(const std::vector<double> &xs, const std::vector<double> &ys) {
            plot(xs, ys, pigment::colors::cyan());
        }

        // Infrastructure methods for future features
        
        // Title and label support (placeholder for future implementation)
        void set_title(const std::string& title) {
            // TODO: Implement text rendering
            get_current_subplot().title = title;
        }
        
        void set_xlabel(const std::string& xlabel) {
            // TODO: Implement text rendering
            get_current_subplot().xlabel = xlabel;
        }
        
        void set_ylabel(const std::string& ylabel) {
            // TODO: Implement text rendering  
            get_current_subplot().ylabel = ylabel;
        }
        
        // Axis limits
        void set_xlim(double xmin, double xmax) {
            Subplot& subplot = get_current_subplot();
            subplot.x_min = xmin;
            subplot.x_max = xmax;
        }
        
        void set_ylim(double ymin, double ymax) {
            Subplot& subplot = get_current_subplot();
            subplot.y_min = ymin;
            subplot.y_max = ymax;
        }
        
        // Grid support (placeholder for future implementation)
        void show_grid(bool show = true) {
            // TODO: Implement grid rendering
            get_current_subplot().show_grid = show;
        }
        
        // Get subplot information for external use
        int get_subplot_count() const { return subplots.size(); }
        std::pair<int, int> get_current_subplot_index() const { return current_subplot; }
        std::pair<int, int> get_subplot_layout() const { return {subplot_rows, subplot_cols}; }

        // Palette management
        void set_palette(const pigment::Palette& palette) {
            current_theme.plot_colors = palette;
        }
        
        void set_material_design_palette() {
            set_palette(pigment::Palette::material_design());
        }
        
        void set_warm_palette() {
            set_palette(pigment::Palette::warm());
        }
        
        void set_cool_palette() {
            set_palette(pigment::Palette::cool());
        }
        
        void set_vibrant_palette(size_t count = 8) {
            set_palette(pigment::Palette::vibrant(count));
        }

      private:
        int width, height;
        bool animated;
        std::vector<uint8_t> pixels;
        std::vector<Operation> ops;
        std::vector<std::vector<uint8_t>> frames;
        Color background_color;
        std::unique_ptr<concord::Grid<Color>> grid; // Use Concord's Grid structure

        // New members for enhanced functionality
        Theme current_theme;
        int subplot_rows, subplot_cols;
        std::vector<Subplot> subplots;
        std::pair<int, int> current_subplot;

        // Helper methods
        Subplot &get_current_subplot() {
            int index = current_subplot.first * subplot_cols + current_subplot.second;
            return subplots[index];
        }

        const Subplot &get_current_subplot() const {
            int index = current_subplot.first * subplot_cols + current_subplot.second;
            return subplots[index];
        }

        void render() {
            // Clear pixels with background color
            for (size_t i = 0; i < pixels.size(); i += 4) {
                pixels[i] = background_color.r;
                pixels[i + 1] = background_color.g;
                pixels[i + 2] = background_color.b;
                pixels[i + 3] = background_color.a;
            }

            // Clear grid with background color
            for (int r = 0; r < height; ++r) {
                for (int c = 0; c < width; ++c) {
                    (*grid)(r, c).second = background_color;
                }
            }

            // Draw subplot borders
            draw_subplot_borders();

            // Render each subplot
            for (auto &subplot : subplots) {
                render_subplot(subplot);
            }
        }

        void set_pixel(int x, int y, const Color &c) {
            if (x < 0 || x >= width || y < 0 || y >= height)
                return;
            int i = (y * width + x) * 4;
            pixels[i] = c.r;
            pixels[i + 1] = c.g;
            pixels[i + 2] = c.b;
            pixels[i + 3] = c.a;
        }

        void draw_line(int x0, int y0, int x1, int y1, const Color &c) {
            int dx = std::abs(x1 - x0), dy = std::abs(y1 - y0);
            int sx = x0 < x1 ? 1 : -1, sy = y0 < y1 ? 1 : -1;
            int err = dx - dy;
            while (true) {
                set_pixel_color(x0, y0, c); // Use our enhanced set_pixel method
                if (x0 == x1 && y0 == y1)
                    break;
                int e2 = err * 2;
                if (e2 > -dy) {
                    err -= dy;
                    x0 += sx;
                }
                if (e2 < dx) {
                    err += dx;
                    y0 += sy;
                }
            }
        }

        void draw_polyline(const std::vector<std::pair<double, double>> &pts, const Color &c) {
            for (size_t i = 1; i < pts.size(); ++i) {
                draw_line(int(pts[i - 1].first), int(pts[i - 1].second), int(pts[i].first), int(pts[i].second), c);
            }
        }

        void draw_subplot_borders() {
            if (subplot_rows <= 1 && subplot_cols <= 1)
                return;

            // Draw horizontal lines
            for (int r = 1; r < subplot_rows; ++r) {
                int y = r * (height / subplot_rows);
                for (int x = 0; x < width; ++x) {
                    set_pixel_color(x, y, current_theme.border_color);
                }
            }

            // Draw vertical lines
            for (int c = 1; c < subplot_cols; ++c) {
                int x = c * (width / subplot_cols);
                for (int y = 0; y < height; ++y) {
                    set_pixel_color(x, y, current_theme.border_color);
                }
            }
        }

        void render_subplot(Subplot &subplot) {
            if (subplot.operations.empty())
                return;

            // Find data bounds for this subplot
            double xmin = subplot.operations[0].xs[0], xmax = xmin;
            double ymin = subplot.operations[0].ys[0], ymax = ymin;

            for (auto &op : subplot.operations) {
                for (double x : op.xs) {
                    xmin = std::min(xmin, x);
                    xmax = std::max(xmax, x);
                }
                for (double y : op.ys) {
                    ymin = std::min(ymin, y);
                    ymax = std::max(ymax, y);
                }
            }

            if (xmax == xmin)
                xmax = xmin + 1;
            if (ymax == ymin)
                ymax = ymin + 1;

            // Store bounds for future use (axis labels, etc.)
            subplot.x_min = xmin;
            subplot.x_max = xmax;
            subplot.y_min = ymin;
            subplot.y_max = ymax;

            // Plot each operation within the subplot bounds
            for (auto &op : subplot.operations) {
                std::vector<std::pair<double, double>> pts;
                pts.reserve(op.xs.size());
                for (size_t i = 0; i < op.xs.size(); ++i) {
                    double nx = (op.xs[i] - xmin) / (xmax - xmin) * (subplot.width - 1) + subplot.x_offset;
                    double ny = (op.ys[i] - ymin) / (ymax - ymin) * (subplot.height - 1) + subplot.y_offset;
                    pts.emplace_back(nx, subplot.y_offset + subplot.height - 1 - (ny - subplot.y_offset));
                }
                draw_polyline_clipped(pts, op.c, subplot);
            }
        }

        void draw_polyline_clipped(const std::vector<std::pair<double, double>> &pts, const Color &c,
                                   const Subplot &subplot) {
            for (size_t i = 1; i < pts.size(); ++i) {
                draw_line_clipped(int(pts[i - 1].first), int(pts[i - 1].second), int(pts[i].first), int(pts[i].second),
                                  c, subplot);
            }
        }

        void draw_line_clipped(int x0, int y0, int x1, int y1, const Color &c, const Subplot &subplot) {
            // Clip line to subplot bounds
            if (!clip_line_to_rect(x0, y0, x1, y1, subplot.x_offset, subplot.y_offset, subplot.x_offset + subplot.width,
                                   subplot.y_offset + subplot.height)) {
                return;
            }

            draw_line(x0, y0, x1, y1, c);
        }

        bool clip_line_to_rect(int &x0, int &y0, int &x1, int &y1, int xmin, int ymin, int xmax, int ymax) {
            // Simple Cohen-Sutherland line clipping
            const int INSIDE = 0, LEFT = 1, RIGHT = 2, BOTTOM = 4, TOP = 8;

            auto compute_code = [&](int x, int y) {
                int code = INSIDE;
                if (x < xmin)
                    code |= LEFT;
                else if (x > xmax)
                    code |= RIGHT;
                if (y < ymin)
                    code |= BOTTOM;
                else if (y > ymax)
                    code |= TOP;
                return code;
            };

            int code0 = compute_code(x0, y0);
            int code1 = compute_code(x1, y1);

            while (true) {
                if (!(code0 | code1))
                    return true; // Both points inside
                if (code0 & code1)
                    return false; // Both points outside same region

                int code_out = code0 ? code0 : code1;
                int x = 0, y = 0;

                if (code_out & TOP) {
                    x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
                    y = ymax;
                } else if (code_out & BOTTOM) {
                    x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
                    y = ymin;
                } else if (code_out & RIGHT) {
                    y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
                    x = xmax;
                } else if (code_out & LEFT) {
                    y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
                    x = xmin;
                }

                if (code_out == code0) {
                    x0 = x;
                    y0 = y;
                    code0 = compute_code(x0, y0);
                } else {
                    x1 = x;
                    y1 = y;
                    code1 = compute_code(x1, y1);
                }
            }
        }
    };

} // namespace plotter

#endif
