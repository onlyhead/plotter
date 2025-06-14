#pragma once

#include "implot_callbacks.h"

namespace ImPlot {

    //-----------------------------------------------------------------------------
    // [SECTION] Setup
    //-----------------------------------------------------------------------------

    // The following API allows you to setup and customize various aspects of the
    // current plot. The functions should be called immediately after BeginPlot
    // and before any other API calls. Typical usage is as follows:

    // if (BeginPlot(...)) {                     1) begin a new plot
    //     SetupAxis(ImAxis_X1, "My X-Axis");    2) make Setup calls
    //     SetupAxis(ImAxis_Y1, "My Y-Axis");
    //     SetupLegend(ImPlotLocation_North);
    //     ...
    //     SetupFinish();                        3) [optional] explicitly finish setup
    //     PlotLine(...);                        4) plot items
    //     ...
    //     EndPlot();                            5) end the plot
    // }
    //
    // Important notes:
    //
    // - Always call Setup code at the top of your BeginPlot conditional statement.
    // - Setup is locked once you start plotting or explicitly call SetupFinish.
    //   Do NOT call Setup code after you begin plotting or after you make
    //   any non-Setup API calls (e.g. utils like PlotToPixels also lock Setup)
    // - Calling SetupFinish is OPTIONAL, but probably good practice. If you do not
    //   call it yourself, then the first subsequent plotting or utility function will
    //   call it for you.

    // Enables an axis or sets the label and/or flags for an existing axis. Leave #label = nullptr for no label.
    IMPLOT_API void SetupAxis(ImAxis axis, const char *label = nullptr, ImPlotAxisFlags flags = 0);
    // Sets an axis range limits. If ImPlotCond_Always is used, the axes limits will be locked. Inversion with v_min >
    // v_max is not supported; use SetupAxisLimits instead.
    IMPLOT_API void SetupAxisLimits(ImAxis axis, double v_min, double v_max, ImPlotCond cond = ImPlotCond_Once);
    // Links an axis range limits to external values. Set to nullptr for no linkage. The pointer data must remain valid
    // until EndPlot.
    IMPLOT_API void SetupAxisLinks(ImAxis axis, double *link_min, double *link_max);
    // Sets the format of numeric axis labels via formater specifier (default="%g"). Formated values will be double
    // (i.e. use %f).
    IMPLOT_API void SetupAxisFormat(ImAxis axis, const char *fmt);
    // Sets the format of numeric axis labels via formatter callback. Given #value, write a label into #buff. Optionally
    // pass user data.
    IMPLOT_API void SetupAxisFormat(ImAxis axis, ImPlotFormatter formatter, void *data = nullptr);
    // Sets an axis' ticks and optionally the labels. To keep the default ticks, set #keep_default=true.
    IMPLOT_API void SetupAxisTicks(ImAxis axis, const double *values, int n_ticks, const char *const labels[] = nullptr,
                                   bool keep_default = false);
    // Sets an axis' ticks and optionally the labels for the next plot. To keep the default ticks, set
    // #keep_default=true.
    IMPLOT_API void SetupAxisTicks(ImAxis axis, double v_min, double v_max, int n_ticks,
                                   const char *const labels[] = nullptr, bool keep_default = false);
    // Sets an axis' scale using built-in options.
    IMPLOT_API void SetupAxisScale(ImAxis axis, ImPlotScale scale);
    // Sets an axis' scale using user supplied forward and inverse transfroms.
    IMPLOT_API void SetupAxisScale(ImAxis axis, ImPlotTransform forward, ImPlotTransform inverse, void *data = nullptr);
    // Sets an axis' limits constraints.
    IMPLOT_API void SetupAxisLimitsConstraints(ImAxis axis, double v_min, double v_max);
    // Sets an axis' zoom constraints.
    IMPLOT_API void SetupAxisZoomConstraints(ImAxis axis, double z_min, double z_max);

    // Sets the label and/or flags for primary X and Y axes (shorthand for two calls to SetupAxis).
    IMPLOT_API void SetupAxes(const char *x_label, const char *y_label, ImPlotAxisFlags x_flags = 0,
                              ImPlotAxisFlags y_flags = 0);
    // Sets the primary X and Y axes range limits. If ImPlotCond_Always is used, the axes limits will be locked
    // (shorthand for two calls to SetupAxisLimits).
    IMPLOT_API void SetupAxesLimits(double x_min, double x_max, double y_min, double y_max,
                                    ImPlotCond cond = ImPlotCond_Once);

    // Sets up the plot legend. This can also be called immediately after BeginSubplots when using
    // ImPlotSubplotFlags_ShareItems.
    IMPLOT_API void SetupLegend(ImPlotLocation location, ImPlotLegendFlags flags = 0);
    // Set the location of the current plot's mouse position text (default = South|East).
    IMPLOT_API void SetupMouseText(ImPlotLocation location, ImPlotMouseTextFlags flags = 0);

    // Explicitly finalize plot setup. Once you call this, you cannot make anymore Setup calls for the current plot!
    // Note that calling this function is OPTIONAL; it will be called by the first subsequent setup-locking API call.
    IMPLOT_API void SetupFinish();

    //-----------------------------------------------------------------------------
    // [SECTION] SetNext
    //-----------------------------------------------------------------------------

    // Though you should default to the `Setup` API above, there are some scenarios
    // where (re)configuring a plot or axis before `BeginPlot` is needed (e.g. if
    // using a preceding button or slider widget to change the plot limits). In
    // this case, you can use the `SetNext` API below. While this is not as feature
    // rich as the Setup API, most common needs are provided. These functions can be
    // called anwhere except for inside of `Begin/EndPlot`. For example:

    // if (ImGui::Button("Center Plot"))
    //     ImPlot::SetNextPlotLimits(-1,1,-1,1);
    // if (ImPlot::BeginPlot(...)) {
    //     ...
    //     ImPlot::EndPlot();
    // }
    //
    // Important notes:
    //
    // - You must still enable non-default axes with SetupAxis for these functions
    //   to work properly.

    // Sets an upcoming axis range limits. If ImPlotCond_Always is used, the axes limits will be locked.
    IMPLOT_API void SetNextAxisLimits(ImAxis axis, double v_min, double v_max, ImPlotCond cond = ImPlotCond_Once);
    // Links an upcoming axis range limits to external values. Set to nullptr for no linkage. The pointer data must
    // remain valid until EndPlot!
    IMPLOT_API void SetNextAxisLinks(ImAxis axis, double *link_min, double *link_max);
    // Set an upcoming axis to auto fit to its data.
    IMPLOT_API void SetNextAxisToFit(ImAxis axis);

    // Sets the upcoming primary X and Y axes range limits. If ImPlotCond_Always is used, the axes limits will be locked
    // (shorthand for two calls to SetupAxisLimits).
    IMPLOT_API void SetNextAxesLimits(double x_min, double x_max, double y_min, double y_max,
                                      ImPlotCond cond = ImPlotCond_Once);
    // Sets all upcoming axes to auto fit to their data.
    IMPLOT_API void SetNextAxesToFit();

} // namespace ImPlot
