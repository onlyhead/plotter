#pragma once

#include <pigment/pigment.hpp>
#include <string>
#include <vector>

namespace plotter {

    using Color = pigment::RGB;

    // Operation structure for plotting data
    struct Operation {
        std::vector<double> xs, ys;
        Color c;
    };

    // Forward declarations
    struct Theme;
    struct Subplot;

} // namespace plotter
