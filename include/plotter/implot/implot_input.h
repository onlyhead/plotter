#pragma once

#include "implot_types.h"

namespace ImPlot {

    //-----------------------------------------------------------------------------
    // [SECTION] Input Mapping
    //-----------------------------------------------------------------------------

    // Provides access to input mapping structure for permanant modifications to controls for pan, select, etc.
    IMPLOT_API ImPlotInputMap &GetInputMap();

    // Default input mapping: pan = LMB drag, box select = RMB drag, fit = LMB double click, context menu = RMB click,
    // zoom = scroll.
    IMPLOT_API void MapInputDefault(ImPlotInputMap *dst = nullptr);
    // Reverse input mapping: pan = RMB drag, box select = LMB drag, fit = LMB double click, context menu = RMB click,
    // zoom = scroll.
    IMPLOT_API void MapInputReverse(ImPlotInputMap *dst = nullptr);

} // namespace ImPlot
