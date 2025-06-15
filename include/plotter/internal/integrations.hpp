#pragma once

#include <concord/concord.hpp>
#include <pigment/pigment.hpp>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace plotter {
    namespace integrations {

        /// Color utilities using Pigment
        namespace color {
            /// Convert a Pigment RGB color to a matplotlib color string
            inline std::string to_matplotlib_color(const pigment::RGB& rgb) {
                // Convert RGB to hex string format for matplotlib
                std::ostringstream oss;
                oss << "#" << std::hex << std::setfill('0') 
                    << std::setw(2) << rgb.r 
                    << std::setw(2) << rgb.g 
                    << std::setw(2) << rgb.b;
                return oss.str();
            }

            /// Convert HSV color to matplotlib color string
            inline std::string to_matplotlib_color(const pigment::HSV& hsv) {
                return to_matplotlib_color(hsv.toRGB());
            }

            /// Convert HSL color to matplotlib color string
            inline std::string to_matplotlib_color(const pigment::HSL& hsl) {
                return to_matplotlib_color(hsl.to_rgb());
            }

            /// Get a color from a predefined palette
            inline pigment::RGB get_palette_color(const pigment::Palette& palette, size_t index) {
                return palette[index];
            }

            /// Create a default plotting palette
            inline pigment::Palette create_default_palette() {
                return pigment::Palette{
                    pigment::RGB("#1f77b4"), // blue
                    pigment::RGB("#ff7f0e"), // orange
                    pigment::RGB("#2ca02c"), // green
                    pigment::RGB("#d62728"), // red
                    pigment::RGB("#9467bd"), // purple
                    pigment::RGB("#8c564b"), // brown
                    pigment::RGB("#e377c2"), // pink
                    pigment::RGB("#7f7f7f"), // gray
                    pigment::RGB("#bcbd22"), // olive
                    pigment::RGB("#17becf")  // cyan
                };
            }
        } // namespace color

        /// Geometry utilities using Concord
        namespace geometry {
            /// Extract x coordinates from a vector of Points
            inline std::vector<double> extract_x(const std::vector<concord::Point>& points) {
                std::vector<double> x_coords;
                x_coords.reserve(points.size());
                for (const auto& point : points) {
                    x_coords.push_back(point.x);
                }
                return x_coords;
            }

            /// Extract y coordinates from a vector of Points
            inline std::vector<double> extract_y(const std::vector<concord::Point>& points) {
                std::vector<double> y_coords;
                y_coords.reserve(points.size());
                for (const auto& point : points) {
                    y_coords.push_back(point.y);
                }
                return y_coords;
            }

            /// Extract z coordinates from a vector of Points
            inline std::vector<double> extract_z(const std::vector<concord::Point>& points) {
                std::vector<double> z_coords;
                z_coords.reserve(points.size());
                for (const auto& point : points) {
                    z_coords.push_back(point.z);
                }
                return z_coords;
            }

            /// Create a vector of Points from x, y coordinates
            inline std::vector<concord::Point> create_points(const std::vector<double>& x, const std::vector<double>& y) {
                if (x.size() != y.size()) {
                    throw std::invalid_argument("x and y vectors must have the same size");
                }
                std::vector<concord::Point> points;
                points.reserve(x.size());
                for (size_t i = 0; i < x.size(); ++i) {
                    points.emplace_back(x[i], y[i], 0.0);
                }
                return points;
            }

            /// Create a vector of Points from x, y, z coordinates
            inline std::vector<concord::Point> create_points(const std::vector<double>& x, 
                                                           const std::vector<double>& y, 
                                                           const std::vector<double>& z) {
                if (x.size() != y.size() || x.size() != z.size()) {
                    throw std::invalid_argument("x, y, and z vectors must have the same size");
                }
                std::vector<concord::Point> points;
                points.reserve(x.size());
                for (size_t i = 0; i < x.size(); ++i) {
                    points.emplace_back(x[i], y[i], z[i]);
                }
                return points;
            }

            /// Generate points for a circle using Concord
            inline std::vector<concord::Point> generate_circle_points(double center_x, double center_y, double radius, int num_points = 100) {
                std::vector<concord::Point> points;
                points.reserve(num_points);
                
                for (int i = 0; i < num_points; ++i) {
                    double angle = 2.0 * M_PI * i / num_points;
                    double x = center_x + radius * std::cos(angle);
                    double y = center_y + radius * std::sin(angle);
                    points.emplace_back(x, y, 0.0);
                }
                // Close the circle
                if (!points.empty()) {
                    points.push_back(points[0]);
                }
                return points;
            }

            /// Generate points for a rectangle using Concord
            inline std::vector<concord::Point> generate_rectangle_points(double x, double y, double width, double height) {
                return {
                    concord::Point{x, y, 0.0},
                    concord::Point{x + width, y, 0.0},
                    concord::Point{x + width, y + height, 0.0},
                    concord::Point{x, y + height, 0.0},
                    concord::Point{x, y, 0.0} // Close the rectangle
                };
            }

        } // namespace geometry

    } // namespace integrations
} // namespace plotter
