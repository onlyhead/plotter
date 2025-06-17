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
#include "core/types.hpp"
#include "core/theme.hpp"
#include "core/subplot.hpp"
#include "managers/theme_manager.hpp"
#include "managers/subplot_manager.hpp"
#include "rendering/renderer.hpp"
#include "plotting/plot_interface.hpp"

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

        // Legacy support (for backward compatibility)
        std::vector<Operation> ops;

    public:
        Canvas(int w, int h, bool animate = false)
            : width(w), height(h), animated(animate), pixels(w * h * 4, 255),
              subplot_manager_(w, h) {
            
            // Initialize grid with the canvas dimensions
            grid = std::make_unique<concord::Grid<Color>>(h, w, 1.0, concord::Datum(), false, concord::Pose{});
            
            // Initialize renderer
            renderer_ = std::make_unique<Renderer>(width, height, pixels);
            
            // Initialize with single subplot covering entire canvas
            subplot_manager_.create_subplots(1, 1);
            
            // Set initial background
            renderer_->set_background_color(theme_manager_.get_background_color());
        }

        // Theme management (delegates to ThemeManager)
        void set_theme(const Theme& theme) {
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
        void set_palette(const pigment::Palette& palette) {
            theme_manager_.set_palette(palette);
        }

        void set_material_design_palette() {
            theme_manager_.set_material_design_palette();
        }

        void set_warm_palette() {
            theme_manager_.set_warm_palette();
        }

        void set_cool_palette() {
            theme_manager_.set_cool_palette();
        }

        void set_vibrant_palette(size_t count = 8) {
            theme_manager_.set_vibrant_palette(count);
        }

        // Subplot management (delegates to SubplotManager)
        void create_subplots(int rows, int cols) {
            subplot_manager_.create_subplots(rows, cols);
        }

        void subplot(int row, int col) {
            subplot_manager_.set_current_subplot(row, col);
        }

        // Plotting methods
        void plot(const std::vector<double>& xs, const std::vector<double>& ys, Color c = Color()) {
            if (c == Color()) {
                // Use theme colors if no color specified
                size_t color_index = subplot_manager_.get_current_subplot().operations.size();
                c = theme_manager_.get_next_plot_color(color_index);
            }

            Subplot& current_subplot = subplot_manager_.get_current_subplot();
            current_subplot.operations.push_back({xs, ys, c});
            current_subplot.has_data = true;
        }

        // Named color convenience methods (delegates to PlotInterface)
        void plot_red(const std::vector<double>& xs, const std::vector<double>& ys) {
            Subplot& current_subplot = subplot_manager_.get_current_subplot();
            PlotInterface::plot_red(current_subplot.operations, xs, ys);
            current_subplot.has_data = true;
        }

        void plot_blue(const std::vector<double>& xs, const std::vector<double>& ys) {
            Subplot& current_subplot = subplot_manager_.get_current_subplot();
            PlotInterface::plot_blue(current_subplot.operations, xs, ys);
            current_subplot.has_data = true;
        }

        void plot_green(const std::vector<double>& xs, const std::vector<double>& ys) {
            Subplot& current_subplot = subplot_manager_.get_current_subplot();
            PlotInterface::plot_green(current_subplot.operations, xs, ys);
            current_subplot.has_data = true;
        }

        void plot_orange(const std::vector<double>& xs, const std::vector<double>& ys) {
            Subplot& current_subplot = subplot_manager_.get_current_subplot();
            PlotInterface::plot_orange(current_subplot.operations, xs, ys);
            current_subplot.has_data = true;
        }

        void plot_purple(const std::vector<double>& xs, const std::vector<double>& ys) {
            Subplot& current_subplot = subplot_manager_.get_current_subplot();
            PlotInterface::plot_purple(current_subplot.operations, xs, ys);
            current_subplot.has_data = true;
        }

        void plot_cyan(const std::vector<double>& xs, const std::vector<double>& ys) {
            Subplot& current_subplot = subplot_manager_.get_current_subplot();
            PlotInterface::plot_cyan(current_subplot.operations, xs, ys);
            current_subplot.has_data = true;
        }

        void plot_with_named_color(const std::vector<double>& xs, const std::vector<double>& ys, const std::string& color_name) {
            Subplot& current_subplot = subplot_manager_.get_current_subplot();
            PlotInterface::plot_with_named_color(current_subplot.operations, xs, ys, color_name);
            current_subplot.has_data = true;
        }

        // Infrastructure methods for future features
        void set_title(const std::string& title) {
            subplot_manager_.get_current_subplot().title = title;
        }

        void set_xlabel(const std::string& xlabel) {
            subplot_manager_.get_current_subplot().xlabel = xlabel;
        }

        void set_ylabel(const std::string& ylabel) {
            subplot_manager_.get_current_subplot().ylabel = ylabel;
        }

        void set_xlim(double xmin, double xmax) {
            Subplot& subplot = subplot_manager_.get_current_subplot();
            subplot.x_min = xmin;
            subplot.x_max = xmax;
        }

        void set_ylim(double ymin, double ymax) {
            Subplot& subplot = subplot_manager_.get_current_subplot();
            subplot.y_min = ymin;
            subplot.y_max = ymax;
        }

        void show_grid(bool show = true) {
            subplot_manager_.get_current_subplot().show_grid = show;
        }

        // Query methods
        int get_subplot_count() const { 
            return subplot_manager_.get_subplot_count(); 
        }

        std::pair<int, int> get_current_subplot_index() const { 
            return subplot_manager_.get_current_subplot_index(); 
        }

        std::pair<int, int> get_subplot_layout() const { 
            return subplot_manager_.get_layout(); 
        }

        // Legacy pixel access methods (backward compatibility)
        void set_background(const Color& bg) { 
            renderer_->set_background_color(bg);
        }

        Color get_pixel(int x, int y) const {
            if (x < 0 || x >= width || y < 0 || y >= height) {
                return theme_manager_.get_background_color();
            }
            return (*grid)(y, x).second; // Grid uses (row, col) indexing
        }

        void set_pixel_color(int x, int y, const Color& c) {
            if (x < 0 || x >= width || y < 0 || y >= height)
                return;

            // Update the grid
            (*grid)(y, x).second = c;

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

        bool save(const std::string& fname, int delay_cs = 10) {
            if (animated) {
                if (!ops.empty()) {
                    render();
                    frames.emplace_back(pixels);
                    ops.clear();
                }
                GifWriter writer;
                if (!GifBegin(&writer, fname.c_str(), width, height, delay_cs))
                    return false;
                for (auto& f : frames)
                    GifWriteFrame(&writer, f.data(), width, height, delay_cs);
                return GifEnd(&writer);
            } else {
                render();
                return stbi_write_png(fname.c_str(), width, height, 4, pixels.data(), width * 4) != 0;
            }
        }

    private:
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

            // Draw subplot borders
            auto layout = subplot_manager_.get_layout();
            renderer_->draw_subplot_borders(subplot_manager_.get_all_subplots(), 
                                          theme_manager_.get_border_color(),
                                          layout.first, layout.second);

            // Render each subplot
            for (auto& subplot : subplot_manager_.get_all_subplots()) {
                renderer_->render_subplot(subplot);
            }
        }
    };

} // namespace plotter

#endif
