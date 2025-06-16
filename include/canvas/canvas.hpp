#pragma once

#ifndef PLOTPP_HPP
#define PLOTPP_HPP

#include <algorithm>
#include <cmath>
#include <cstdint>
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

namespace plotter {

    using Color = pigment::RGB;

    class Canvas {
      public:
        Canvas(int w, int h, bool animate = false)
            : width(w), height(h), animated(animate), pixels(w * h * 4, 255), background_color(255, 255, 255, 255) {
            // Initialize grid with the canvas dimensions
            // Grid uses row/col structure where each cell represents a pixel
            grid = std::make_unique<concord::Grid<Color>>(h, w, 1.0, false, concord::Pose{});
        }

        void plot(const std::vector<double> &xs, const std::vector<double> &ys, Color c) { ops.push_back({xs, ys, c}); }

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
            ops.clear();
        }

        void show() {
            render();
            ops.clear();
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
            // Create colors from hex strings (Pigment supports this)
            Color c("#FF0000"); // Default to red if color name not found
            if (color_name == "red")
                c = Color("#FF0000");
            else if (color_name == "green")
                c = Color("#00FF00");
            else if (color_name == "blue")
                c = Color("#0000FF");
            else if (color_name == "black")
                c = Color("#000000");
            else if (color_name == "white")
                c = Color("#FFFFFF");
            plot(xs, ys, c);
        }

      private:
        struct Operation {
            std::vector<double> xs, ys;
            Color c;
        };

        int width, height;
        bool animated;
        std::vector<uint8_t> pixels;
        std::vector<Operation> ops;
        std::vector<std::vector<uint8_t>> frames;
        Color background_color;
        std::unique_ptr<concord::Grid<Color>> grid; // Use Concord's Grid structure

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

            if (ops.empty())
                return;

            // Find data bounds
            double xmin = ops[0].xs[0], xmax = xmin, ymin = ops[0].ys[0], ymax = ymin;
            for (auto &op : ops) {
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

            // Plot each operation
            for (auto &op : ops) {
                std::vector<std::pair<double, double>> pts;
                pts.reserve(op.xs.size());
                for (size_t i = 0; i < op.xs.size(); ++i) {
                    double nx = (op.xs[i] - xmin) / (xmax - xmin) * (width - 1);
                    double ny = (op.ys[i] - ymin) / (ymax - ymin) * (height - 1);
                    pts.emplace_back(nx, height - 1 - ny);
                }
                draw_polyline(pts, op.c);
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
    };

} // namespace plotter

#endif
