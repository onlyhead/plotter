#pragma once

#include "implot_types.h"

namespace ImPlot {

    //-----------------------------------------------------------------------------
    // [SECTION] Miscellaneous
    //-----------------------------------------------------------------------------

    // Render icons similar to those that appear in legends (nifty for data lists).
    IMPLOT_API void ItemIcon(const ImVec4 &col);
    IMPLOT_API void ItemIcon(ImU32 col);
    IMPLOT_API void ColormapIcon(ImPlotColormap cmap);

    // Get the plot draw list for custom rendering to the current plot area. Call between Begin/EndPlot.
    IMPLOT_API ImDrawList *GetPlotDrawList();
    // Push clip rect for rendering to current plot area. The rect can be expanded or contracted by #expand pixels. Call
    // between Begin/EndPlot.
    IMPLOT_API void PushPlotClipRect(float expand = 0);
    // Pop plot clip rect. Call between Begin/EndPlot.
    IMPLOT_API void PopPlotClipRect();

    // Shows ImPlot style selector dropdown menu.
    IMPLOT_API bool ShowStyleSelector(const char *label);
    // Shows ImPlot colormap selector dropdown menu.
    IMPLOT_API bool ShowColormapSelector(const char *label);
    // Shows ImPlot input map selector dropdown menu.
    IMPLOT_API bool ShowInputMapSelector(const char *label);
    // Shows ImPlot style editor block (not a window).
    IMPLOT_API void ShowStyleEditor(ImPlotStyle *ref = nullptr);
    // Add basic help/info block for end users (not a window).
    IMPLOT_API void ShowUserGuide();
    // Shows ImPlot metrics/debug information window.
    IMPLOT_API void ShowMetricsWindow(bool *p_popen = nullptr);

} // namespace ImPlot
