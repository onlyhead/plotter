#pragma once

#include "implot_enums.h"

namespace ImPlot {

    //-----------------------------------------------------------------------------
    // [SECTION] Begin/End Plot
    //-----------------------------------------------------------------------------

    // Starts a 2D plotting context. If this function returns true, EndPlot() MUST
    // be called! You are encouraged to use the following convention:
    //
    // if (BeginPlot(...)) {
    //     PlotLine(...);
    //     ...
    //     EndPlot();
    // }
    //
    // Important notes:
    //
    // - #title_id must be unique to the current ImGui ID scope. If you need to avoid ID
    //   collisions or don't want to display a title in the plot, use double hashes
    //   (e.g. "MyPlot##HiddenIdText" or "##NoTitle").
    // - #size is the **frame** size of the plot widget, not the plot area. The default
    //   size of plots (i.e. when ImVec2(0,0)) can be modified in your ImPlotStyle.
    IMPLOT_API bool BeginPlot(const char *title_id, const ImVec2 &size = ImVec2(-1, 0), ImPlotFlags flags = 0);

    // Only call EndPlot() if BeginPlot() returns true! Typically called at the end
    // of an if statement conditioned on BeginPlot(). See example above.
    IMPLOT_API void EndPlot();

    //-----------------------------------------------------------------------------
    // [SECTION] Begin/End Subplots
    //-----------------------------------------------------------------------------

    // Starts a subdivided plotting context. If the function returns true,
    // EndSubplots() MUST be called! Call BeginPlot/EndPlot AT MOST [rows*cols]
    // times in  between the begining and end of the subplot context. Plots are
    // added in row major order.
    //
    // Example:
    //
    // if (BeginSubplots("My Subplot",2,3,ImVec2(800,400)) {
    //     for (int i = 0; i < 6; ++i) {
    //         if (BeginPlot(...)) {
    //             ImPlot::PlotLine(...);
    //             ...
    //             EndPlot();
    //         }
    //     }
    //     EndSubplots();
    // }
    //
    // Produces:
    //
    // [0] | [1] | [2]
    // ----|-----|----
    // [3] | [4] | [5]
    //
    // Important notes:
    //
    // - #title_id must be unique to the current ImGui ID scope. If you need to avoid ID
    //   collisions or don't want to display a title in the plot, use double hashes
    //   (e.g. "MySubplot##HiddenIdText" or "##NoTitle").
    // - #rows and #cols must be greater than 0.
    // - #size is the size of the entire grid of subplots, not the individual plots
    // - #row_ratios and #col_ratios must have AT LEAST #rows and #cols elements,
    //   respectively. These are the sizes of the rows and columns expressed in ratios.
    //   If the user adjusts the dimensions, the arrays are updated with new ratios.
    //
    // Important notes regarding BeginPlot from inside of BeginSubplots:
    //
    // - The #title_id parameter of _BeginPlot_ (see above) does NOT have to be
    //   unique when called inside of a subplot context. Subplot IDs are hashed
    //   for your convenience so you don't have call PushID or generate unique title
    //   strings. Simply pass an empty string to BeginPlot unless you want to title
    //   each subplot.
    // - The #size parameter of _BeginPlot_ (see above) is ignored when inside of a
    //   subplot context. The actual size of the subplot will be based on the
    //   #size value you pass to _BeginSubplots_ and #row/#col_ratios if provided.

    IMPLOT_API bool BeginSubplots(const char *title_id, int rows, int cols, const ImVec2 &size,
                                  ImPlotSubplotFlags flags = 0, float *row_ratios = nullptr,
                                  float *col_ratios = nullptr);

    // Only call EndSubplots() if BeginSubplots() returns true! Typically called at the end
    // of an if statement conditioned on BeginSublots(). See example above.
    IMPLOT_API void EndSubplots();

} // namespace ImPlot
