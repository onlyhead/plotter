#pragma once

#include <pigment/pigment.hpp>
#include <string>
#include <vector>

namespace plotter {

    using Color = pigment::RGB;

    // Operation types
    enum class OperationType { PLOT, TEXT };

    // Text rendering enums
    enum class TextAlign { LEFT, CENTER, RIGHT };
    enum class TextBaseline { TOP, MIDDLE, BOTTOM };

    // Operation structure for plotting data and text
    struct Operation {
        OperationType type = OperationType::PLOT;
        std::vector<double> xs, ys;
        Color c;

        // Text-specific fields
        std::string text;
        std::string font_name;                             // Font name for text operations
        double font_size = 12.0;                           // Font size for text operations
        TextAlign text_align = TextAlign::LEFT;            // Text alignment
        TextBaseline text_baseline = TextBaseline::BOTTOM; // Text baseline
        double x, y;                                       // Text position
        bool use_pixel_coords = false;                     // If true, use pixel coordinates instead of data coordinates
    };

    // Axis configuration
    struct AxisConfig {
        bool show_axis = true;
        bool auto_scale = true;
        double min_value = 0.0;
        double max_value = 1.0;
        int num_ticks = 5;
        std::string label = "";
        Color axis_color = {0, 0, 0, 255}; // Black by default
        Color tick_color = {0, 0, 0, 255}; // Black by default
        Color label_color = {0, 0, 0, 255}; // Black by default
        double tick_length = 5.0;
        double font_size = 10.0;
    };

    // Forward declarations
    struct Theme;
    struct Subplot;

} // namespace plotter
