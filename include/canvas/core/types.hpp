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

    // Forward declarations
    struct Theme;
    struct Subplot;

} // namespace plotter
