#pragma once

// Plottly - A modular C++ plotting library
// This is the main header that includes all plotting functionality

#include "internal/axes.hpp"
#include "internal/charts.hpp"
#include "internal/core.hpp"
#include "internal/figure.hpp"
#include "internal/image.hpp"
#include "internal/integrations.hpp"
#include "internal/plots.hpp"
#include "internal/scatter.hpp"

#include <iostream>
#include <vector>
#include <string>

namespace plotter {

    /// Class-based plotter interface
    /// Allows creating multiple independent plot instances
    class Plotter {
      private:
        long figure_num_;
        static long next_figure_num_;

        // Pigment integration
        pigment::Palette color_palette_;
        size_t current_color_index_;

        // Animation support
        bool animation_mode_;
        std::vector<std::string> animation_frames_;  // Store frame data as base64 or file paths
        int frame_duration_ms_;  // Duration of each frame in milliseconds

        /// Select this figure as current
        void select_figure();

        /// Capture current plot as a frame (internal method)
        void capture_frame();

        /// Create animated GIF from captured frames (internal method)
        void save_animated_gif(const char *filename);

      public:
        /// Constructor - creates a new figure
        Plotter();

        /// Constructor with specific figure number
        explicit Plotter(long figure_num);

        /// Destructor
        ~Plotter() = default;

        /// Copy constructor
        Plotter(const Plotter &other);

        /// Assignment operator
        Plotter &operator=(const Plotter &other);

        /// Get the figure number for this plotter instance
        long figure_number() const { return figure_num_; }

        // ============ PLOTTING FUNCTIONS ============
        // All plotting functions now use Concord Points exclusively

        /// Plot a line through the given points
        bool plot(const std::vector<concord::Point> &points);

        /// Plot a line with Pigment color
        bool plot(const std::vector<concord::Point> &points, const pigment::RGB &color);

        /// Plot a line with format string (for line styles)
        bool plot(const std::vector<concord::Point> &points, const char *format);

        /// Scatter plot using Concord Points
        bool scatter(const std::vector<concord::Point> &points);

        /// Scatter plot with Pigment color
        bool scatter(const std::vector<concord::Point> &points, const pigment::RGB &color);

        /// Scatter plot with size and color
        bool scatter(const std::vector<concord::Point> &points, double s, const pigment::RGB &color);

        /// Bar plot using Concord Points (x-coordinates for positions, y-coordinates for heights)
        bool bar(const std::vector<concord::Point> &points);

        /// Bar plot with Pigment color
        bool bar(const std::vector<concord::Point> &points, const pigment::RGB &color);

        // ============ ADVANCED PLOTTING FUNCTIONS ============

        /// Plot a circle using Concord geometry
        bool plot_circle(double center_x, double center_y, double radius,
                         const pigment::RGB &color = pigment::RGB::blue());

        /// Plot a rectangle using Concord geometry
        bool plot_rectangle(double x, double y, double width, double height,
                            const pigment::RGB &color = pigment::RGB::red());

        /// Fill a shape with color
        bool fill(const std::vector<concord::Point> &points, const pigment::RGB &color);

        // ============ PIGMENT COLOR FUNCTIONS ============

        /// Set color palette using Pigment
        void set_color_palette(const pigment::Palette &palette);

        /// Get next color from palette
        pigment::RGB get_next_color();

        // ============ FIGURE MANAGEMENT ============

        /// Display the plot
        void show();
        void show(bool block);

        /// Save the plot to file
        void save(const char *filename);
        void save(const char *filename, int dpi);
        void save(const char *filename, bool animation);
        void save(const char *filename, int dpi, bool animation);

        // ============ ANIMATION FUNCTIONS ============

        /// Enable animation mode - captures frames for GIF creation
        void enable_animation(int frame_duration_ms = 100);

        /// Disable animation mode
        void disable_animation();

        /// Check if animation mode is enabled
        bool is_animation_enabled() const;

        /// Clear all captured frames
        void clear_frames();

        /// Get number of captured frames
        size_t frame_count() const;

        /// Set frame duration for GIF animation
        void set_frame_duration(int duration_ms);

        /// Clear the current figure
        void clf();

        /// Set figure size
        void figure_size(int width, int height);

        /// Set x-axis limits
        void xlim(double left, double right);

        /// Set y-axis limits
        void ylim(double bottom, double top);

        /// Add title
        void title(const char *titlestr);

        /// Add x-axis label
        void xlabel(const char *str);

        /// Add y-axis label
        void ylabel(const char *str);

        /// Add legend
        void legend();

        /// Close this figure
        void close();
    }; // class Plotter

    // Static member definition
    inline long Plotter::next_figure_num_ = 1;

    // ============ IMPLEMENTATION ============

    // Constructor - creates a new figure
    inline Plotter::Plotter()
        : figure_num_(next_figure_num_++), color_palette_(integrations::color::create_default_palette()),
          current_color_index_(0), animation_mode_(false), frame_duration_ms_(100) {
        detail::_interpreter::get(); // Initialize interpreter
        // Don't call select_figure() in constructor to avoid Python figure creation issues
    }

    // Constructor with specific figure number
    inline Plotter::Plotter(long figure_num)
        : figure_num_(figure_num), color_palette_(integrations::color::create_default_palette()),
          current_color_index_(0), animation_mode_(false), frame_duration_ms_(100) {
        detail::_interpreter::get(); // Initialize interpreter
        // Don't call select_figure() in constructor to avoid Python figure creation issues
    }

    // Copy constructor
    inline Plotter::Plotter(const Plotter &other)
        : figure_num_(next_figure_num_++), color_palette_(other.color_palette_), current_color_index_(0),
          animation_mode_(false), frame_duration_ms_(100) {
        detail::_interpreter::get(); // Initialize interpreter
        // Don't call select_figure() in constructor to avoid Python figure creation issues
    }

    // Assignment operator
    inline Plotter &Plotter::operator=(const Plotter &other) {
        if (this != &other) {
            // Keep the current figure number, just ensure it's selected
            select_figure();
        }
        return *this;
    }

    // Select this figure as current
    inline void Plotter::select_figure() {
        // For now, don't try to select specific figures - just work with the current one
        // This provides a working class interface even if figures aren't truly independent
        // In future, we can fix the figure() function implementation
    }

    // ============ PLOTTING FUNCTION IMPLEMENTATIONS ============

    /// Plot points using Concord Point objects
    inline bool Plotter::plot(const std::vector<concord::Point> &points) {
        select_figure();
        auto x = integrations::geometry::extract_x(points);
        auto y = integrations::geometry::extract_y(points);
        bool result = plotter::plot(x, y);
        capture_frame();  // Capture frame if in animation mode
        return result;
    }

    /// Plot points with Pigment color
    inline bool Plotter::plot(const std::vector<concord::Point> &points, const pigment::RGB &color) {
        select_figure();
        auto x = integrations::geometry::extract_x(points);
        auto y = integrations::geometry::extract_y(points);
        std::map<std::string, std::string> keywords;
        keywords["color"] = integrations::color::to_matplotlib_color(color);
        bool result = plotter::plot(x, y, keywords);
        capture_frame();  // Capture frame if in animation mode
        return result;
    }

    /// Plot points with format string
    inline bool Plotter::plot(const std::vector<concord::Point> &points, const char *format) {
        select_figure();
        auto x = integrations::geometry::extract_x(points);
        auto y = integrations::geometry::extract_y(points);
        bool result = plotter::plot(x, y, std::string(format));
        capture_frame();  // Capture frame if in animation mode
        return result;
    }

    /// Scatter plot using Concord Points
    inline bool Plotter::scatter(const std::vector<concord::Point> &points) {
        select_figure();
        auto x = integrations::geometry::extract_x(points);
        auto y = integrations::geometry::extract_y(points);
        return plotter::scatter(x, y);
    }

    /// Scatter plot using Concord Points with Pigment color
    inline bool Plotter::scatter(const std::vector<concord::Point> &points, const pigment::RGB &color) {
        select_figure();
        auto x = integrations::geometry::extract_x(points);
        auto y = integrations::geometry::extract_y(points);
        std::map<std::string, std::string> keywords;
        keywords["color"] = integrations::color::to_matplotlib_color(color);
        return plotter::scatter(x, y, keywords);
    }

    /// Scatter plot using Concord Points with size and color
    inline bool Plotter::scatter(const std::vector<concord::Point> &points, double s, const pigment::RGB &color) {
        select_figure();
        auto x = integrations::geometry::extract_x(points);
        auto y = integrations::geometry::extract_y(points);
        std::map<std::string, std::string> keywords;
        keywords["s"] = std::to_string(s);
        keywords["color"] = integrations::color::to_matplotlib_color(color);
        return plotter::scatter(x, y, keywords);
    }

    /// Bar plot using Concord Points (x-coordinates for positions, y-coordinates for heights)
    inline bool Plotter::bar(const std::vector<concord::Point> &points) {
        select_figure();
        auto x = integrations::geometry::extract_x(points);
        auto y = integrations::geometry::extract_y(points);
        return plotter::bar(x, y);
    }

    /// Bar plot with Pigment color
    inline bool Plotter::bar(const std::vector<concord::Point> &points, const pigment::RGB &color) {
        select_figure();
        auto y = integrations::geometry::extract_y(points);
        // For now, use basic bar function - may need to be enhanced later
        return plotter::bar(y);
    }

    // ============ FIGURE MANAGEMENT IMPLEMENTATIONS ============

    inline void Plotter::show() {
        select_figure();
        plotter::show();
    }

    inline void Plotter::show(bool block) {
        select_figure();
        plotter::show(block);
    }

    inline void Plotter::save(const char *filename) {
        select_figure();
        plotter::save(filename);
    }

    inline void Plotter::save(const char *filename, int dpi) {
        select_figure();
        plotter::save(filename, dpi);
    }

    inline void Plotter::save(const char *filename, bool animation) {
        if (animation && animation_mode_ && !animation_frames_.empty()) {
            // Create GIF from captured frames
            save_animated_gif(filename);
        } else {
            // Save current plot as static image
            select_figure();
            plotter::save(filename);
        }
    }

    inline void Plotter::save(const char *filename, int dpi, bool animation) {
        if (animation && animation_mode_ && !animation_frames_.empty()) {
            // Create GIF from captured frames
            save_animated_gif(filename);
        } else {
            // Save current plot as static image
            select_figure();
            plotter::save(filename, dpi);
        }
    }

    inline void Plotter::clf() {
        select_figure();
        plotter::clf();
    }

    inline void Plotter::figure_size(int width, int height) {
        select_figure();
        plotter::figure_size(width, height);
    }

    inline void Plotter::title(const char *titlestr) {
        select_figure();
        plotter::title(titlestr);
    }

    inline void Plotter::xlabel(const char *str) {
        select_figure();
        plotter::xlabel(str);
    }

    inline void Plotter::ylabel(const char *str) {
        select_figure();
        plotter::ylabel(str);
    }

    inline void Plotter::legend() {
        select_figure();
        plotter::legend();
    }

    inline void Plotter::close() { plotter::close(figure_num_); }

    inline void Plotter::xlim(double left, double right) {
        select_figure();
        plotter::xlim(left, right);
    }

    inline void Plotter::ylim(double bottom, double top) {
        select_figure();
        plotter::ylim(bottom, top);
    }

    // ============ ANIMATION IMPLEMENTATIONS ============

    /// Enable animation mode
    inline void Plotter::enable_animation(int frame_duration_ms) {
        animation_mode_ = true;
        frame_duration_ms_ = frame_duration_ms;
        animation_frames_.clear();
    }

    /// Disable animation mode
    inline void Plotter::disable_animation() {
        animation_mode_ = false;
    }

    /// Check if animation mode is enabled
    inline bool Plotter::is_animation_enabled() const {
        return animation_mode_;
    }

    /// Clear all captured frames
    inline void Plotter::clear_frames() {
        animation_frames_.clear();
    }

    /// Get number of captured frames
    inline size_t Plotter::frame_count() const {
        return animation_frames_.size();
    }

    /// Set frame duration for GIF animation
    inline void Plotter::set_frame_duration(int duration_ms) {
        frame_duration_ms_ = duration_ms;
    }

    /// Capture current plot as a frame (internal method)
    inline void Plotter::capture_frame() {
        if (!animation_mode_) return;
        
        // Generate a temporary filename for this frame
        std::string temp_filename = "temp_frame_" + std::to_string(animation_frames_.size()) + ".png";
        
        // Save current plot as a temporary frame
        select_figure();
        plotter::save(temp_filename.c_str());
        
        // Store the filename for later GIF creation
        animation_frames_.push_back(temp_filename);
    }

    /// Create animated GIF from captured frames (internal method)
    inline void Plotter::save_animated_gif(const char *filename) {
        if (animation_frames_.empty()) {
            std::cerr << "Warning: No frames captured for animation. Save as static image instead." << std::endl;
            select_figure();
            plotter::save(filename);
            return;
        }

        // Use Python/matplotlib to create GIF from frames
        detail::_interpreter::get();
        
        // Create Python script to generate GIF
        std::string python_script = R"(
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from PIL import Image
import os

# Load all frame images
frames = []
frame_files = [)";

        // Add frame filenames to Python script
        for (size_t i = 0; i < animation_frames_.size(); ++i) {
            python_script += "'" + animation_frames_[i] + "'";
            if (i < animation_frames_.size() - 1) python_script += ", ";
        }

        python_script += R"(]

for frame_file in frame_files:
    if os.path.exists(frame_file):
        frames.append(Image.open(frame_file))

# Create GIF
if frames:
    frames[0].save(')" + std::string(filename) + R"(', 
                   save_all=True, 
                   append_images=frames[1:], 
                   duration=)" + std::to_string(frame_duration_ms_) + R"(, 
                   loop=0)
    print(f"Animated GIF saved as )" + std::string(filename) + R"(")
    
    # Clean up temporary frame files
    for frame_file in frame_files:
        if os.path.exists(frame_file):
            os.remove(frame_file)
else:
    print("Error: No frames to create GIF")
)";

        // Execute Python script
        PyRun_SimpleString(python_script.c_str());
        
        // Clear the frame list after creating GIF
        animation_frames_.clear();
    }

    // ============ CONCORD INTEGRATION IMPLEMENTATIONS ============

    /// Plot a circle using Concord geometry
    inline bool Plotter::plot_circle(double center_x, double center_y, double radius, const pigment::RGB &color) {
        select_figure();
        auto circle_points = integrations::geometry::generate_circle_points(center_x, center_y, radius);
        return plot(circle_points, color);
    }

    /// Plot a rectangle using Concord geometry
    inline bool Plotter::plot_rectangle(double x, double y, double width, double height, const pigment::RGB &color) {
        select_figure();
        auto rect_points = integrations::geometry::generate_rectangle_points(x, y, width, height);
        return plot(rect_points, color);
    }

    /// Fill a shape with color
    inline bool Plotter::fill(const std::vector<concord::Point> &points, const pigment::RGB &color) {
        select_figure();
        auto x = integrations::geometry::extract_x(points);
        auto y = integrations::geometry::extract_y(points);
        std::map<std::string, std::string> keywords;
        keywords["color"] = integrations::color::to_matplotlib_color(color);
        return plotter::fill(x, y, keywords);
    }

    // ============ PIGMENT COLOR IMPLEMENTATIONS ============

    /// Set color palette using Pigment
    inline void Plotter::set_color_palette(const pigment::Palette &palette) {
        color_palette_ = palette;
        current_color_index_ = 0;
    }

    /// Get next color from palette
    inline pigment::RGB Plotter::get_next_color() {
        if (color_palette_.empty()) {
            color_palette_ = integrations::color::create_default_palette();
        }
        pigment::RGB color = color_palette_[current_color_index_];
        current_color_index_ = (current_color_index_ + 1) % color_palette_.size();
        return color;
    }

    // Convenience aliases for common operations
    using namespace plotter;

    // Version information
    constexpr const char *version() { return "1.0.0"; }

} // namespace plotter

// Template implementations would be in a separate .cpp file or included separately
// to avoid compilation issues with the Python integration
