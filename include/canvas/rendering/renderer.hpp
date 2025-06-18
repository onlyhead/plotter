#pragma once

#include "../core/subplot.hpp"
#include "../core/types.hpp"
#include "../utils/text_renderer.hpp"
#include <algorithm>
#include <cmath>
#include <vector>

namespace plotter {

    class Renderer {
      private:
        int width_, height_;
        std::vector<uint8_t> &pixels_;
        Color background_color_;

      public:
        Renderer(int width, int height, std::vector<uint8_t> &pixels)
            : width_(width), height_(height), pixels_(pixels), background_color_(255, 255, 255) {}

        void set_background_color(const Color &bg) { background_color_ = bg; }

        void clear_canvas() {
            // Clear pixels with background color
            for (size_t i = 0; i < pixels_.size(); i += 4) {
                pixels_[i] = background_color_.r;
                pixels_[i + 1] = background_color_.g;
                pixels_[i + 2] = background_color_.b;
                pixels_[i + 3] = background_color_.a;
            }
        }

        void draw_subplot_borders(const std::vector<Subplot> &subplots, const Color &border_color, int rows, int cols) {
            if (rows <= 1 && cols <= 1)
                return;

            // Draw horizontal lines
            for (int r = 1; r < rows; ++r) {
                int y = r * (height_ / rows);
                for (int x = 0; x < width_; ++x) {
                    set_pixel(x, y, border_color);
                }
            }

            // Draw vertical lines
            for (int c = 1; c < cols; ++c) {
                int x = c * (width_ / cols);
                for (int y = 0; y < height_; ++y) {
                    set_pixel(x, y, border_color);
                }
            }
        }

        void render_subplot(Subplot &subplot, canvas::TextRenderer &text_renderer) {
            if (subplot.operations.empty())
                return;

            // Find data bounds for this subplot (only for PLOT operations)
            double xmin = 0, xmax = 1, ymin = 0, ymax = 1;
            bool has_plot_data = false;

            for (auto &op : subplot.operations) {
                if (op.type == OperationType::PLOT && !op.xs.empty() && !op.ys.empty()) {
                    if (!has_plot_data) {
                        xmin = xmax = op.xs[0];
                        ymin = ymax = op.ys[0];
                        has_plot_data = true;
                    }
                    for (double x : op.xs) {
                        xmin = std::min(xmin, x);
                        xmax = std::max(xmax, x);
                    }
                    for (double y : op.ys) {
                        ymin = std::min(ymin, y);
                        ymax = std::max(ymax, y);
                    }
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

            // Process each operation within the subplot bounds
            for (auto &op : subplot.operations) {
                if (op.type == OperationType::PLOT) {
                    // Handle plot operations
                    std::vector<std::pair<double, double>> pts;
                    pts.reserve(op.xs.size());
                    for (size_t i = 0; i < op.xs.size(); ++i) {
                        double nx = (op.xs[i] - xmin) / (xmax - xmin) * (subplot.width - 1) + subplot.x_offset;
                        double ny = (op.ys[i] - ymin) / (ymax - ymin) * (subplot.height - 1) + subplot.y_offset;
                        pts.emplace_back(nx, subplot.y_offset + subplot.height - 1 - (ny - subplot.y_offset));
                    }
                    draw_polyline_clipped(pts, op.c, subplot);
                } else if (op.type == OperationType::TEXT) {
                    // Handle text operations
                    render_text_operation(op, subplot, xmin, xmax, ymin, ymax, text_renderer);
                }
            }
        }

      private:
        void set_pixel(int x, int y, const Color &c) {
            if (x < 0 || x >= width_ || y < 0 || y >= height_)
                return;
            int i = (y * width_ + x) * 4;
            pixels_[i] = c.r;
            pixels_[i + 1] = c.g;
            pixels_[i + 2] = c.b;
            pixels_[i + 3] = c.a;
        }

        void draw_line(int x0, int y0, int x1, int y1, const Color &c) {
            int dx = std::abs(x1 - x0), dy = std::abs(y1 - y0);
            int sx = x0 < x1 ? 1 : -1, sy = y0 < y1 ? 1 : -1;
            int err = dx - dy;
            while (true) {
                set_pixel(x0, y0, c);
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

        void render_text_operation(const Operation &op, const Subplot &subplot, double xmin, double xmax, double ymin,
                                   double ymax, canvas::TextRenderer &text_renderer) {
            int pixel_x, pixel_y;

            if (op.use_pixel_coords) {
                // Use pixel coordinates directly
                pixel_x = static_cast<int>(op.x);
                pixel_y = static_cast<int>(op.y);
            } else {
                // Convert data coordinates to pixel coordinates
                double nx = (op.x - xmin) / (xmax - xmin) * (subplot.width - 1) + subplot.x_offset;
                double ny = (op.y - ymin) / (ymax - ymin) * (subplot.height - 1) + subplot.y_offset;
                pixel_x = static_cast<int>(nx);
                pixel_y = static_cast<int>(subplot.y_offset + subplot.height - 1 - (ny - subplot.y_offset));
            }

            // Create text style from the operation data
            canvas::TextStyle style;
            style.color = op.c;
            style.font_size = op.font_size;
            style.align = op.text_align;
            style.baseline = op.text_baseline;

            // Use the passed text renderer with style and font from operation
            text_renderer.render_text(pixels_, width_, height_, op.text, static_cast<double>(pixel_x),
                                      static_cast<double>(pixel_y), style, op.font_name);
        }
    };

} // namespace plotter
