#pragma once

#include "../core/subplot.hpp"
#include "../core/types.hpp"
#include "../utils/text_renderer.hpp"
#include <algorithm>
#include <cmath>
#include <cstdio>
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

        void render_axes(Subplot &subplot, canvas::TextRenderer &text_renderer, const Color &theme_text_color) {
            // Reserve space for axes (margins)
            int left_margin = 60;   // Space for Y-axis labels
            int bottom_margin = 40; // Space for X-axis labels
            int right_margin = 10;  // Small margin
            int top_margin = 10;    // Small margin

            // Calculate adjusted subplot drawing area to account for axes
            int plot_x = subplot.x_offset + left_margin;
            int plot_y = subplot.y_offset + top_margin;
            int plot_width = subplot.width - left_margin - right_margin;
            int plot_height = subplot.height - top_margin - bottom_margin;

            // Draw X-axis
            if (subplot.x_axis.show_axis) {
                render_x_axis(subplot, text_renderer, plot_x, plot_y + plot_height, plot_width, theme_text_color);
            }

            // Draw Y-axis
            if (subplot.y_axis.show_axis) {
                render_y_axis(subplot, text_renderer, plot_x, plot_y, plot_height, theme_text_color);
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

        void render_x_axis(const Subplot &subplot, canvas::TextRenderer &text_renderer, int x_start, int y_pos,
                           int width, const Color &theme_text_color) {
            // Draw main X-axis line (use theme color instead of axis config color)
            draw_line(x_start, y_pos, x_start + width, y_pos, theme_text_color);

            // Calculate tick positions
            double data_min = subplot.x_axis.auto_scale ? subplot.x_min : subplot.x_axis.min_value;
            double data_max = subplot.x_axis.auto_scale ? subplot.x_max : subplot.x_axis.max_value;
            double data_range = data_max - data_min;

            if (data_range <= 0)
                return;

            // Draw ticks and labels
            for (int i = 0; i <= subplot.x_axis.num_ticks; ++i) {
                double tick_value = data_min + (data_range * i) / subplot.x_axis.num_ticks;
                int tick_x = x_start + (width * i) / subplot.x_axis.num_ticks;

                // Draw tick mark (use theme color)
                draw_line(tick_x, y_pos, tick_x, y_pos + static_cast<int>(subplot.x_axis.tick_length),
                          theme_text_color);

                // Draw tick label (use theme color)
                canvas::TextStyle label_style;
                label_style.color = theme_text_color;
                label_style.font_size = subplot.x_axis.font_size;
                label_style.align = canvas::TextAlign::CENTER;
                label_style.baseline = canvas::TextBaseline::TOP;

                std::string label_text = format_tick_label(tick_value);
                text_renderer.render_text(pixels_, width_, height_, label_text, static_cast<double>(tick_x),
                                          static_cast<double>(y_pos + subplot.x_axis.tick_length + 5), label_style, "");
            }

            // Draw axis label if present (use theme color)
            if (!subplot.x_axis.label.empty()) {
                canvas::TextStyle axis_label_style;
                axis_label_style.color = theme_text_color;
                axis_label_style.font_size = subplot.x_axis.font_size + 2;
                axis_label_style.align = canvas::TextAlign::CENTER;
                axis_label_style.baseline = canvas::TextBaseline::TOP;

                text_renderer.render_text(pixels_, width_, height_, subplot.x_axis.label,
                                          static_cast<double>(x_start + width / 2.0), static_cast<double>(y_pos + 25),
                                          axis_label_style, "");
            }
        }

        void render_y_axis(const Subplot &subplot, canvas::TextRenderer &text_renderer, int x_pos, int y_start,
                           int height, const Color &theme_text_color) {
            // Draw main Y-axis line (use theme color)
            draw_line(x_pos, y_start, x_pos, y_start + height, theme_text_color);

            // Calculate tick positions
            double data_min = subplot.y_axis.auto_scale ? subplot.y_min : subplot.y_axis.min_value;
            double data_max = subplot.y_axis.auto_scale ? subplot.y_max : subplot.y_axis.max_value;
            double data_range = data_max - data_min;

            if (data_range <= 0)
                return;

            // Draw ticks and labels
            for (int i = 0; i <= subplot.y_axis.num_ticks; ++i) {
                double tick_value = data_min + (data_range * i) / subplot.y_axis.num_ticks;
                int tick_y = y_start + height - (height * i) / subplot.y_axis.num_ticks; // Flip Y coordinate

                // Draw tick mark (use theme color)
                draw_line(x_pos - static_cast<int>(subplot.y_axis.tick_length), tick_y, x_pos, tick_y,
                          theme_text_color);

                // Draw tick label (use theme color)
                canvas::TextStyle label_style;
                label_style.color = theme_text_color;
                label_style.font_size = subplot.y_axis.font_size;
                label_style.align = canvas::TextAlign::RIGHT;
                label_style.baseline = canvas::TextBaseline::MIDDLE;

                std::string label_text = format_tick_label(tick_value);
                text_renderer.render_text(pixels_, width_, height_, label_text,
                                          static_cast<double>(x_pos - subplot.y_axis.tick_length - 5),
                                          static_cast<double>(tick_y), label_style, "");
            }

            // Draw axis label if present (use theme color)
            if (!subplot.y_axis.label.empty()) {
                canvas::TextStyle axis_label_style;
                axis_label_style.color = theme_text_color;
                axis_label_style.font_size = subplot.y_axis.font_size + 2;
                axis_label_style.align = canvas::TextAlign::CENTER;
                axis_label_style.baseline = canvas::TextBaseline::MIDDLE;

                // Render Y-axis label vertically (character by character)
                render_vertical_text(text_renderer, subplot.y_axis.label, static_cast<double>(x_pos - 40),
                                     static_cast<double>(y_start + height / 2.0), axis_label_style);
            }
        }

        std::string format_tick_label(double value) {
            // Simple number formatting
            if (std::abs(value) < 1e-10) {
                return "0";
            } else if (std::abs(value) >= 1000 || std::abs(value) < 0.01) {
                // Use scientific notation for very large or very small numbers
                char buffer[32];
                snprintf(buffer, sizeof(buffer), "%.2e", value);
                return std::string(buffer);
            } else {
                // Use fixed-point notation
                char buffer[32];
                snprintf(buffer, sizeof(buffer), "%.2f", value);
                // Remove trailing zeros
                std::string result(buffer);
                size_t end = result.find_last_not_of('0');
                if (end != std::string::npos && result[end] == '.') {
                    end--;
                }
                return result.substr(0, end + 1);
            }
        }

        void render_vertical_text(canvas::TextRenderer &text_renderer, const std::string &text, 
                                double x, double y, const canvas::TextStyle &style) {
            // Calculate the total height needed for the text
            double char_height = text_renderer.text_height(style, "");
            double total_height = char_height * text.length();
            
            // Start position (center the text vertically around y)
            double start_y = y - total_height / 2.0;
            
            // Render each character below the previous one
            for (size_t i = 0; i < text.length(); ++i) {
                std::string single_char(1, text[i]);
                double char_y = start_y + i * char_height;
                
                text_renderer.render_text(pixels_, width_, height_, single_char,
                                        x, char_y, style, "");
            }
        }
    };

} // namespace plotter
