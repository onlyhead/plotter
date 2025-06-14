#pragma once

#include "implot_defines.h"

namespace ImPlot {
    // Forward declaration
    struct ImPlotContext;

    // Global context variable - this needs to be defined exactly once
    extern ImPlotContext *GImPlot;
} // namespace ImPlot

// Implementation - this will be included when IMPLOT_IMPLEMENTATION is defined
#ifdef IMPLOT_IMPLEMENTATION
namespace ImPlot {
    ImPlotContext *GImPlot = nullptr;
}
#endif
