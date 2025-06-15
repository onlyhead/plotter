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

        /// Select this figure as current
        void select_figure();

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

        /// Plot a line through the given x and y data points
        template <typename NumericX, typename NumericY>
        bool plot(const std::vector<NumericX> &x, const std::vector<NumericY> &y);

        /// Plot a line with format string
        template <typename NumericX, typename NumericY>
        bool plot(const std::vector<NumericX> &x, const std::vector<NumericY> &y, const char *format);

        /// Plot a line with only y data (x will be 0, 1, 2, ...)
        template <typename Numeric> bool plot(const std::vector<Numeric> &y);

        /// Plot with format string
        template <typename Numeric> bool plot(const std::vector<Numeric> &y, const char *format);

        /// Scatter plot
        template <typename NumericX, typename NumericY>
        bool scatter(const std::vector<NumericX> &x, const std::vector<NumericY> &y);

        /// Scatter plot with size
        template <typename NumericX, typename NumericY>
        bool scatter(const std::vector<NumericX> &x, const std::vector<NumericY> &y, double s);

        /// Bar plot
        template <typename Numeric> bool bar(const std::vector<Numeric> &y);

        // ============ CONCORD INTEGRATION FUNCTIONS ============

        /// Plot points using Concord Point objects
        bool plot(const std::vector<concord::Point> &points);

        /// Plot points with Pigment color
        bool plot(const std::vector<concord::Point> &points, const pigment::RGB &color);

        /// Plot points with format string
        bool plot(const std::vector<concord::Point> &points, const char *format);

        /// Scatter plot using Concord Points
        bool scatter(const std::vector<concord::Point> &points);

        /// Scatter plot using Concord Points with Pigment color
        bool scatter(const std::vector<concord::Point> &points, const pigment::RGB &color);

        /// Scatter plot using Concord Points with size and color
        bool scatter(const std::vector<concord::Point> &points, double s, const pigment::RGB &color);

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

        /// Clear the current figure
        void clf();

        /// Set figure size
        void figure_size(int width, int height);

        /// Set x-axis limits
        template <typename Numeric> void xlim(Numeric left, Numeric right);

        /// Set y-axis limits
        template <typename Numeric> void ylim(Numeric bottom, Numeric top);

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
    long Plotter::next_figure_num_ = 1;

    // ============ IMPLEMENTATION ============

    // Constructor - creates a new figure
    inline Plotter::Plotter()
        : figure_num_(next_figure_num_++), color_palette_(integrations::color::create_default_palette()),
          current_color_index_(0) {
        detail::_interpreter::get(); // Initialize interpreter
        // Don't call select_figure() in constructor to avoid Python figure creation issues
    }

    // Constructor with specific figure number
    inline Plotter::Plotter(long figure_num)
        : figure_num_(figure_num), color_palette_(integrations::color::create_default_palette()),
          current_color_index_(0) {
        detail::_interpreter::get(); // Initialize interpreter
        // Don't call select_figure() in constructor to avoid Python figure creation issues
    }

    // Copy constructor
    inline Plotter::Plotter(const Plotter &other)
        : figure_num_(next_figure_num_++), color_palette_(other.color_palette_), current_color_index_(0) {
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

    template <typename NumericX, typename NumericY>
    inline bool Plotter::plot(const std::vector<NumericX> &x, const std::vector<NumericY> &y) {
        select_figure();
        return plotter::plot(x, y);
    }

    template <typename NumericX, typename NumericY>
    inline bool Plotter::plot(const std::vector<NumericX> &x, const std::vector<NumericY> &y, const char *format) {
        select_figure();
        return plotter::plot(x, y, std::string(format));
    }

    template <typename Numeric> inline bool Plotter::plot(const std::vector<Numeric> &y) {
        select_figure();
        return plotter::plot(y);
    }

    template <typename Numeric> inline bool Plotter::plot(const std::vector<Numeric> &y, const char *format) {
        select_figure();
        return plotter::plot(y, std::string(format));
    }

    template <typename NumericX, typename NumericY>
    inline bool Plotter::scatter(const std::vector<NumericX> &x, const std::vector<NumericY> &y) {
        select_figure();
        return plotter::scatter(x, y);
    }

    template <typename NumericX, typename NumericY>
    inline bool Plotter::scatter(const std::vector<NumericX> &x, const std::vector<NumericY> &y, double s) {
        select_figure();
        return plotter::scatter(x, y, s);
    }

    template <typename Numeric> inline bool Plotter::bar(const std::vector<Numeric> &y) {
        select_figure();
        return plotter::bar(y);
    }

    template <typename Numeric> inline void Plotter::xlim(Numeric left, Numeric right) {
        select_figure();
        plotter::xlim(left, right);
    }

    template <typename Numeric> inline void Plotter::ylim(Numeric bottom, Numeric top) {
        select_figure();
        plotter::ylim(bottom, top);
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

    // ============ CONCORD INTEGRATION IMPLEMENTATIONS ============

    /// Plot points using Concord Point objects
    inline bool Plotter::plot(const std::vector<concord::Point> &points) {
        select_figure();
        auto x = integrations::geometry::extract_x(points);
        auto y = integrations::geometry::extract_y(points);
        return plotter::plot(x, y);
    }

    /// Plot points with Pigment color
    inline bool Plotter::plot(const std::vector<concord::Point> &points, const pigment::RGB &color) {
        select_figure();
        auto x = integrations::geometry::extract_x(points);
        auto y = integrations::geometry::extract_y(points);
        std::map<std::string, std::string> keywords;
        keywords["color"] = integrations::color::to_matplotlib_color(color);
        return plotter::plot(x, y, keywords);
    }

    /// Plot points with format string
    inline bool Plotter::plot(const std::vector<concord::Point> &points, const char *format) {
        select_figure();
        auto x = integrations::geometry::extract_x(points);
        auto y = integrations::geometry::extract_y(points);
        return plotter::plot(x, y, std::string(format));
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
