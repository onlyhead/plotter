#pragma once

#include "implot_enums.h"

namespace ImPlot {

    //-----------------------------------------------------------------------------
    // [SECTION] Colormaps
    //-----------------------------------------------------------------------------

    // Item styling is based on colormaps when the relevant ImPlotCol_XXX is set to
    // IMPLOT_AUTO_COL (default). Several built-in colormaps are available. You can
    // add and then push/pop your own colormaps as well. To permanently set a colormap,
    // modify the Colormap index member of your ImPlotStyle.

    // Colormap data will be ignored and a custom color will be used if you have done one of the following:
    //     1) Modified an item style color in your ImPlotStyle to anything other than IMPLOT_AUTO_COL.
    //     2) Pushed an item style color using PushStyleColor().
    //     3) Set the next item style with a SetNextXXXStyle function.

    // Add a new colormap. The color data will be copied. The colormap can be used by pushing either the returned index
    // or the string name with PushColormap. The colormap name must be unique and the size must be greater than 1. You
    // will receive an assert otherwise! By default colormaps are considered to be qualitative (i.e. discrete). If you
    // want to create a continuous colormap, set #qual=false. This will treat the colors you provide as keys, and ImPlot
    // will build a linearly interpolated lookup table. The memory footprint of this table will be exactly
    // ((size-1)*255+1)*4 bytes.
    IMPLOT_API ImPlotColormap AddColormap(const char *name, const ImVec4 *cols, int size, bool qual = true);
    IMPLOT_API ImPlotColormap AddColormap(const char *name, const ImU32 *cols, int size, bool qual = true);

    // Returns the number of available colormaps (i.e. the built-in + user-added count).
    IMPLOT_API int GetColormapCount();
    // Returns a null terminated string name for a colormap given an index. Returns nullptr if index is invalid.
    IMPLOT_API const char *GetColormapName(ImPlotColormap cmap);
    // Returns an index number for a colormap given a valid string name. Returns -1 if name is invalid.
    IMPLOT_API ImPlotColormap GetColormapIndex(const char *name);

    // Temporarily switch to one of the built-in (i.e. ImPlotColormap_XXX) or user-added colormaps (i.e. a return value
    // of AddColormap). Don't forget to call PopColormap!
    IMPLOT_API void PushColormap(ImPlotColormap cmap);
    // Push a colormap by string name. Use built-in names such as "Default", "Deep", "Jet", etc. or a string you
    // provided to AddColormap. Don't forget to call PopColormap!
    IMPLOT_API void PushColormap(const char *name);
    // Undo temporary colormap modification(s). Undo multiple pushes at once by increasing count.
    IMPLOT_API void PopColormap(int count = 1);

    // Returns the next color from the current colormap and advances the colormap for the current plot.
    // Can also be used with no return value to skip colors if desired. You need to call this between Begin/EndPlot!
    IMPLOT_API ImVec4 NextColormapColor();

    // Colormap utils. If cmap = IMPLOT_AUTO (default), the current colormap is assumed.
    // Pass an explicit colormap index (built-in or user-added) to specify otherwise.

    // Returns the size of a colormap.
    IMPLOT_API int GetColormapSize(ImPlotColormap cmap = IMPLOT_AUTO);
    // Returns a color from a colormap given an index >= 0 (modulo will be performed).
    IMPLOT_API ImVec4 GetColormapColor(int idx, ImPlotColormap cmap = IMPLOT_AUTO);
    // Sample a color from the current colormap given t between 0 and 1.
    IMPLOT_API ImVec4 SampleColormap(float t, ImPlotColormap cmap = IMPLOT_AUTO);

    // Shows a vertical color scale with linear spaced ticks using the specified color map. Use double hashes to hide
    // label (e.g. "##NoLabel"). If scale_min > scale_max, the scale to color mapping will be reversed.
    IMPLOT_API void ColormapScale(const char *label, double scale_min, double scale_max,
                                  const ImVec2 &size = ImVec2(0, 0), const char *format = "%g",
                                  ImPlotColormapScaleFlags flags = 0, ImPlotColormap cmap = IMPLOT_AUTO);
    // Shows a horizontal slider with a colormap gradient background. Optionally returns the color sampled at t in [0
    // 1].
    IMPLOT_API bool ColormapSlider(const char *label, float *t, ImVec4 *out = nullptr, const char *format = "",
                                   ImPlotColormap cmap = IMPLOT_AUTO);
    // Shows a button with a colormap gradient brackground.
    IMPLOT_API bool ColormapButton(const char *label, const ImVec2 &size = ImVec2(0, 0),
                                   ImPlotColormap cmap = IMPLOT_AUTO);

    // When items in a plot sample their color from a colormap, the color is cached and does not change
    // unless explicitly overriden. Therefore, if you change the colormap after the item has already been plotted,
    // item colors will NOT update. If you need item colors to resample the new colormap, then use this
    // function to bust the cached colors. If #plot_title_id is nullptr, then every item in EVERY existing plot
    // will be cache busted. Otherwise only the plot specified by #plot_title_id will be busted. For the
    // latter, this function must be called in the same ImGui ID scope that the plot is in. You should rarely if ever
    // need this function, but it is available for applications that require runtime colormap swaps (e.g. Heatmaps
    // demo).
    IMPLOT_API void BustColorCache(const char *plot_title_id = nullptr);

} // namespace ImPlot
