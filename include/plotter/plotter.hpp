#pragma once

// Plottly - A modular C++ plotting library
// This is the main header that includes all plotting functionality

#include "axes.hpp"
#include "charts.hpp"
#include "core.hpp"
#include "figure.hpp"
#include "image.hpp"
#include "plots.hpp"
#include "scatter.hpp"

namespace plotter {

    // Convenience aliases for common operations
    using namespace plotter;

    // Version information
    constexpr const char *version() { return "1.0.0"; }

} // namespace plotter
