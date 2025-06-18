#pragma once

#ifndef PLOTPP_MODULAR_HPP
#define PLOTPP_MODULAR_HPP

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

// Include Concord libraries
#include <concord/concord.hpp>

// Include our modular components
#include "core/subplot.hpp"
#include "core/theme.hpp"
#include "core/types.hpp"
#include "managers/subplot_manager.hpp"
#include "managers/theme_manager.hpp"
#include "plotting/plot_interface.hpp"
#include "rendering/renderer.hpp"
#include "utils/text_renderer.hpp"

namespace plotter {

    class Canvas {
      private:
        // Core data
        int width, height;
        bool animated;
        std::vector<uint8_t> pixels;
        std::vector<std::vector<uint8_t>> frames;
        std::unique_ptr<concord::Grid<Color>> grid;

        // Managers
        ThemeManager theme_manager_;
        SubplotManager subplot_manager_;
        std::unique_ptr<Renderer> renderer_;
        canvas::TextRenderer text_renderer_;

        // Default font name for canvas
        std::string default_font_name_;

        // Canvas title
        std::string canvas_title_;

        // Legacy support (for backward compatibility)
        std::vector<Operation> ops;

      public:
        Canvas(int w, int h, bool animate = false)
            : width(w), height(h), animated(animate), pixels(w * h * 4, 255), subplot_manager_(w, h) {

            // Initialize grid with the canvas dimensions
            grid = std::make_unique<concord::Grid<Color>>(h, w, 1.0, false, concord::Pose{});

            // Initialize renderer
            renderer_ = std::make_unique<Renderer>(width, height, pixels);

            // Initialize with single subplot covering entire canvas
            subplot_manager_.create_subplots(1, 1);

            // Set initial background
            renderer_->set_background_color(theme_manager_.get_background_color());
        }

        // Theme management (delegates to ThemeManager)
        void set_theme(const Theme &theme) {
            theme_manager_.set_theme(theme);
            renderer_->set_background_color(theme_manager_.get_background_color());
        }

        void set_dark_theme() {
            theme_manager_.set_dark_theme();
            renderer_->set_background_color(theme_manager_.get_background_color());
        }

        void set_light_theme() {
            theme_manager_.set_light_theme();
            renderer_->set_background_color(theme_manager_.get_background_color());
        }

        void set_vibrant_theme() {
            theme_manager_.set_vibrant_theme();
            renderer_->set_background_color(theme_manager_.get_background_color());
        }

        // Palette management (delegates to ThemeManager)
        void set_palette(const pigment::Palette &palette) { theme_manager_.set_palette(palette); }

        void set_material_design_palette() { theme_manager_.set_material_design_palette(); }

        void set_warm_palette() { theme_manager_.set_warm_palette(); }

        void set_cool_palette() { theme_manager_.set_cool_palette(); }

        void set_vibrant_palette(size_t count = 8) { theme_manager_.set_vibrant_palette(count); }

        // Subplot management (delegates to SubplotManager)
        void create_subplots(int rows, int cols) { subplot_manager_.create_subplots(rows, cols); }

        void subplot(int row, int col) { subplot_manager_.set_current_subplot(row, col); }

        // Plotting methods
        void plot(const std::vector<double> &xs, const std::vector<double> &ys, Color c = Color()) {
            if (c == Color()) {
                // Use theme colors if no color specified
                size_t color_index = subplot_manager_.get_current_subplot().operations.size();
                c = theme_manager_.get_next_plot_color(color_index);
            }

            Subplot &current_subplot = subplot_manager_.get_current_subplot();
            current_subplot.operations.push_back({OperationType::PLOT, xs, ys, c});
            current_subplot.has_data = true;
        }

        // Named color convenience methods (delegates to PlotInterface)
        void plot_red(const std::vector<double> &xs, const std::vector<double> &ys) {
            Subplot &current_subplot = subplot_manager_.get_current_subplot();
            PlotInterface::plot_red(current_subplot.operations, xs, ys);
            current_subplot.has_data = true;
        }

        void plot_blue(const std::vector<double> &xs, const std::vector<double> &ys) {
            Subplot &current_subplot = subplot_manager_.get_current_subplot();
            PlotInterface::plot_blue(current_subplot.operations, xs, ys);
            current_subplot.has_data = true;
        }

        void plot_green(const std::vector<double> &xs, const std::vector<double> &ys) {
            Subplot &current_subplot = subplot_manager_.get_current_subplot();
            PlotInterface::plot_green(current_subplot.operations, xs, ys);
            current_subplot.has_data = true;
        }

        void plot_orange(const std::vector<double> &xs, const std::vector<double> &ys) {
            Subplot &current_subplot = subplot_manager_.get_current_subplot();
            PlotInterface::plot_orange(current_subplot.operations, xs, ys);
            current_subplot.has_data = true;
        }

        void plot_purple(const std::vector<double> &xs, const std::vector<double> &ys) {
            Subplot &current_subplot = subplot_manager_.get_current_subplot();
            PlotInterface::plot_purple(current_subplot.operations, xs, ys);
            current_subplot.has_data = true;
        }

        void plot_cyan(const std::vector<double> &xs, const std::vector<double> &ys) {
            Subplot &current_subplot = subplot_manager_.get_current_subplot();
            PlotInterface::plot_cyan(current_subplot.operations, xs, ys);
            current_subplot.has_data = true;
        }

        void plot_with_named_color(const std::vector<double> &xs, const std::vector<double> &ys,
                                   const std::string &color_name) {
            Subplot &current_subplot = subplot_manager_.get_current_subplot();
            PlotInterface::plot_with_named_color(current_subplot.operations, xs, ys, color_name);
            current_subplot.has_data = true;
        }

        // Infrastructure methods for future features
        void set_title(const std::string &title) { subplot_manager_.get_current_subplot().title = title; }

        void set_canvas_title(const std::string &title) { canvas_title_ = title; }

        void set_xlabel(const std::string &xlabel) { subplot_manager_.get_current_subplot().xlabel = xlabel; }

        void set_ylabel(const std::string &ylabel) { subplot_manager_.get_current_subplot().ylabel = ylabel; }

        void set_xlim(double xmin, double xmax) {
            Subplot &subplot = subplot_manager_.get_current_subplot();
            subplot.x_min = xmin;
            subplot.x_max = xmax;
        }

        void set_ylim(double ymin, double ymax) {
            Subplot &subplot = subplot_manager_.get_current_subplot();
            subplot.y_min = ymin;
            subplot.y_max = ymax;
        }

        void show_grid(bool show = true) { subplot_manager_.get_current_subplot().show_grid = show; }

        // Text rendering methods
        void draw_text(double x, double y, const std::string &text,
                       const canvas::TextStyle &style = canvas::TextStyle(), const std::string &font_name = "") {
            // Add text operation to current subplot
            Subplot &current_subplot = subplot_manager_.get_current_subplot();
            Operation text_op;
            text_op.type = OperationType::TEXT;
            text_op.text = text;
            // Use provided font_name, or fallback to canvas default, or empty for bitmap fallback
            text_op.font_name = font_name.empty() ? default_font_name_ : font_name;
            text_op.font_size = style.font_size;
            text_op.text_align = style.align;
            text_op.text_baseline = style.baseline;
            text_op.x = x;
            text_op.y = y;
            text_op.c = style.color;
            text_op.use_pixel_coords = false;
            current_subplot.operations.push_back(text_op);
            current_subplot.has_data = true;
        }

        void draw_text_pixel(int x, int y, const std::string &text,
                             const canvas::TextStyle &style = canvas::TextStyle(), const std::string &font_name = "") {
            // Add text operation with pixel coordinates
            Subplot &current_subplot = subplot_manager_.get_current_subplot();
            Operation text_op;
            text_op.type = OperationType::TEXT;
            text_op.text = text;
            // Use provided font_name, or fallback to canvas default, or empty for bitmap fallback
            text_op.font_name = font_name.empty() ? default_font_name_ : font_name;
            text_op.font_size = style.font_size;
            text_op.text_align = style.align;
            text_op.text_baseline = style.baseline;
            text_op.x = static_cast<double>(x);
            text_op.y = static_cast<double>(y);
            text_op.c = style.color;
            text_op.use_pixel_coords = true;
            current_subplot.operations.push_back(text_op);
            current_subplot.has_data = true;
        }

        canvas::TextBounds measure_text(const std::string &text, const canvas::TextStyle &style = canvas::TextStyle()) {
            return text_renderer_.measure_text(text, style);
        }

        canvas::FontMetrics get_font_metrics(const canvas::TextStyle &style = canvas::TextStyle(),
                                             const std::string &font_name = "") {
            return text_renderer_.get_font_metrics(style, font_name);
        }

        // Update existing text methods to support font parameter
        double text_width(const std::string &text, const canvas::TextStyle &style = canvas::TextStyle(),
                          const std::string &font_name = "") {
            return text_renderer_.text_width(text, style, font_name);
        }

        double text_height(const canvas::TextStyle &style = canvas::TextStyle(), const std::string &font_name = "") {
            return text_renderer_.text_height(style, font_name);
        }

        // Convenience text method (alias for draw_text_pixel with font support)
        void text(const std::string &text, int x, int y, const canvas::TextStyle &style = canvas::TextStyle(),
                  const std::string &font_name = "") {
            draw_text_pixel(x, y, text, style, font_name);
        }

        // Font management methods
        bool load_font(const std::string &font_name, const std::string &font_path) {
            return text_renderer_.load_font(font_name, font_path);
        }

        bool load_font_from_memory(const std::string &font_name, const unsigned char *data, size_t size) {
            return text_renderer_.load_font_from_memory(font_name, data, size);
        }

        void set_default_font(const std::string &font_name) {
            default_font_name_ = font_name;
            text_renderer_.set_default_font(font_name);
        }

        std::string get_default_font() const { return default_font_name_; }

        // Query methods
        int get_subplot_count() const { return subplot_manager_.get_subplot_count(); }

        std::pair<int, int> get_current_subplot_index() const { return subplot_manager_.get_current_subplot_index(); }

        std::pair<int, int> get_subplot_layout() const { return subplot_manager_.get_layout(); }

        // Legacy pixel access methods (backward compatibility)
        void set_background(const Color &bg) { renderer_->set_background_color(bg); }

        Color get_pixel(int x, int y) const {
            if (x < 0 || x >= width || y < 0 || y >= height) {
                return theme_manager_.get_background_color();
            }
            return (*grid)(y, x).second; // Grid uses (row, col) indexing
        }

        void set_pixel_color(int x, int y, const Color &c) {
            if (x < 0 || x >= width || y < 0 || y >= height)
                return;

            // Update pixel buffer directly
            int i = (y * width + x) * 4;
            pixels[i] = c.r;
            pixels[i + 1] = c.g;
            pixels[i + 2] = c.b;
            pixels[i + 3] = c.a;
        }

        // Frame and output methods
        void set_frame() {
            render();
            if (animated) {
                frames.emplace_back(pixels);
            }
            subplot_manager_.clear_all_operations();
        }

        void show() {
            render();
            subplot_manager_.clear_all_operations();
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

        // Render the canvas (make operations visible)
        void render() {
            // Clear canvas
            renderer_->clear_canvas();

            // Clear grid with background color
            Color bg = theme_manager_.get_background_color();
            for (int r = 0; r < height; ++r) {
                for (int c = 0; c < width; ++c) {
                    (*grid)(r, c).second = bg;
                }
            }

            // Draw canvas title if set
            if (!canvas_title_.empty()) {
                canvas::TextStyle title_style;
                title_style.color = theme_manager_.get_theme().text_color;
                title_style.font_size = 20; // Larger font for canvas title
                title_style.align = canvas::TextAlign::CENTER;
                title_style.baseline = canvas::TextBaseline::TOP;

                // Position title at top center of canvas
                int title_x = width / 2;
                int title_y = 10; // Small margin from top

                text_renderer_.render_text(pixels, width, height, canvas_title_, static_cast<double>(title_x),
                                           static_cast<double>(title_y), title_style, default_font_name_);
            }

            // Draw subplot borders
            auto layout = subplot_manager_.get_layout();
            renderer_->draw_subplot_borders(subplot_manager_.get_all_subplots(), theme_manager_.get_border_color(),
                                            layout.first, layout.second);

            // Render each subplot
            for (auto &subplot : subplot_manager_.get_all_subplots()) {
                renderer_->render_subplot(subplot, text_renderer_);
            }
        }

      private:
    };

} // namespace plotter

#endif
