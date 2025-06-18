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

            // Try to load Ubuntu font as default, fallback to bitmap if not available
            initialize_default_font();
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
        void create_subplots(int rows, int cols) {
            update_subplot_layout();
            subplot_manager_.create_subplots(rows, cols);
        }

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

        void set_canvas_title(const std::string &title) {
            canvas_title_ = title;
            update_subplot_layout();
        }

        void set_xlabel(const std::string &xlabel) { 
            Subplot &subplot = subplot_manager_.get_current_subplot();
            subplot.xlabel = xlabel; 
            subplot.x_axis.label = xlabel;
        }

        void set_ylabel(const std::string &ylabel) { 
            Subplot &subplot = subplot_manager_.get_current_subplot();
            subplot.ylabel = ylabel; 
            subplot.y_axis.label = ylabel;
        }

        void set_xlim(double xmin, double xmax) {
            Subplot &subplot = subplot_manager_.get_current_subplot();
            subplot.x_min = xmin;
            subplot.x_max = xmax;
            // Override auto-scaling when manual limits are set
            subplot.x_axis.auto_scale = false;
            subplot.x_axis.min_value = xmin;
            subplot.x_axis.max_value = xmax;
        }

        void set_ylim(double ymin, double ymax) {
            Subplot &subplot = subplot_manager_.get_current_subplot();
            subplot.y_min = ymin;
            subplot.y_max = ymax;
            // Override auto-scaling when manual limits are set
            subplot.y_axis.auto_scale = false;
            subplot.y_axis.min_value = ymin;
            subplot.y_axis.max_value = ymax;
        }

        void show_grid(bool show = true) { subplot_manager_.get_current_subplot().show_grid = show; }

        // Axis configuration methods
        void show_axes(bool show_x = true, bool show_y = true) {
            Subplot &subplot = subplot_manager_.get_current_subplot();
            subplot.x_axis.show_axis = show_x;
            subplot.y_axis.show_axis = show_y;
        }

        void set_x_axis_config(bool auto_scale = true, double min_val = 0.0, double max_val = 1.0, int num_ticks = 5) {
            Subplot &subplot = subplot_manager_.get_current_subplot();
            subplot.x_axis.auto_scale = auto_scale;
            subplot.x_axis.min_value = min_val;
            subplot.x_axis.max_value = max_val;
            subplot.x_axis.num_ticks = num_ticks;
        }

        void set_y_axis_config(bool auto_scale = true, double min_val = 0.0, double max_val = 1.0, int num_ticks = 5) {
            Subplot &subplot = subplot_manager_.get_current_subplot();
            subplot.y_axis.auto_scale = auto_scale;
            subplot.y_axis.min_value = min_val;
            subplot.y_axis.max_value = max_val;
            subplot.y_axis.num_ticks = num_ticks;
        }

        void set_axis_colors(const Color &axis_color, const Color &tick_color, const Color &label_color) {
            Subplot &subplot = subplot_manager_.get_current_subplot();
            subplot.x_axis.axis_color = axis_color;
            subplot.x_axis.tick_color = tick_color;
            subplot.x_axis.label_color = label_color;
            subplot.y_axis.axis_color = axis_color;
            subplot.y_axis.tick_color = tick_color;
            subplot.y_axis.label_color = label_color;
        }

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
                title_style.baseline = canvas::TextBaseline::MIDDLE;

                // Position title in the reserved space at top
                int title_x = width / 2;
                int title_height = static_cast<int>(text_renderer_.text_height(title_style, default_font_name_));
                int title_y = (title_height + 20) / 2; // Center in the reserved space

                text_renderer_.render_text(pixels, width, height, canvas_title_, static_cast<double>(title_x),
                                           static_cast<double>(title_y), title_style, default_font_name_);
            }

            // Draw subplot borders
            auto layout = subplot_manager_.get_layout();
            renderer_->draw_subplot_borders(subplot_manager_.get_all_subplots(), theme_manager_.get_border_color(),
                                            layout.first, layout.second);

            // Render each subplot
            for (auto &subplot : subplot_manager_.get_all_subplots()) {
                // Make a copy of subplot for rendering with adjusted dimensions
                Subplot render_subplot = subplot;
                
                // Adjust the copy for plot rendering (reserve space for axes)
                if (subplot.x_axis.show_axis || subplot.y_axis.show_axis) {
                    int left_margin = subplot.y_axis.show_axis ? 60 : 10;
                    int bottom_margin = subplot.x_axis.show_axis ? 40 : 10;
                    int right_margin = 10;
                    int top_margin = 10;
                    
                    render_subplot.x_offset = subplot.x_offset + left_margin;
                    render_subplot.y_offset = subplot.y_offset + top_margin;
                    render_subplot.width = subplot.width - left_margin - right_margin;
                    render_subplot.height = subplot.height - top_margin - bottom_margin;
                }
                
                // First render the plot data within the adjusted subplot
                renderer_->render_subplot(render_subplot, text_renderer_);
                
                // Then render axes OVER the figure (so they're visible on top)
                renderer_->render_axes(subplot, text_renderer_, theme_manager_.get_theme().text_color);
            }
        }

      private:
        void update_subplot_layout() {
            int title_height = 0;
            int title_padding = 20; // Padding above and below title

            if (!canvas_title_.empty()) {
                // Calculate space needed for canvas title
                canvas::TextStyle title_style;
                title_style.font_size = 20;
                title_height = static_cast<int>(text_renderer_.text_height(title_style, default_font_name_));
                title_height += title_padding; // Add padding
            }

            // Update subplot manager with adjusted dimensions
            subplot_manager_.set_canvas_dimensions(width, height - title_height, 0, title_height);
        }

        void initialize_default_font() {
            // List of Ubuntu font paths to try, in order of preference
            std::vector<std::string> ubuntu_font_paths = {
                "/usr/share/fonts/truetype/ubuntu/Ubuntu-R.ttf",
                "/usr/share/fonts/truetype/ubuntu/Ubuntu-Regular.ttf",
                "/System/Library/Fonts/Helvetica.ttc",             // macOS fallback
                "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", // Debian/Ubuntu fallback
                "/usr/share/fonts/TTF/DejaVuSans.ttf",             // Arch Linux fallback
            };

            // Try to load Ubuntu font
            for (const auto &font_path : ubuntu_font_paths) {
                if (text_renderer_.load_font("ubuntu", font_path)) {
                    default_font_name_ = "ubuntu";
                    text_renderer_.set_default_font("ubuntu");
                    std::cout << "Loaded font: " << font_path << std::endl;
                    return;
                }
            }

            // If no TrueType font found, use bitmap fallback
            default_font_name_ = ""; // Empty string means bitmap fallback
            std::cout << "No TrueType font found, using bitmap fallback" << std::endl;
        }
    };

} // namespace plotter

#endif
