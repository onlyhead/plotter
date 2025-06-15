#pragma once

// Plotter - A C++ plotting library with Concord and Pigment integration
// This is the main public header - only include this in your projects

/**
 * Public API for the Plotter library
 *
 * Main classes to use:
 * - plotter::Plotter - The main plotting class
 * - concord::Point - Geometric points
 * - pigment::RGB, pigment::HSL, pigment::HSV - Color types
 * - pigment::Palette - Color palettes
 *
 * Example usage:
 * ```cpp
 * #include <plotter.hpp>
 *
 * int main() {
 *     plotter::Plotter plt;
 *
 *     // Plot with traditional vectors
 *     std::vector<double> x = {1, 2, 3, 4};
 *     std::vector<double> y = {1, 4, 2, 3};
 *     plt.plot(x, y);
 *
 *     // Plot with Concord points and Pigment colors
 *     std::vector<concord::Point> points;
 *     points.emplace_back(1, 2, 0);
 *     points.emplace_back(2, 3, 0);
 *     plt.plot(points, pigment::RGB::red());
 *
 *     plt.save("output.png");
 * }
 * ```
 */

// Include the full implementation
#include "plotter/plotter.hpp"
