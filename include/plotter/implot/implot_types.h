#pragma once

#include "imgui.h"
#include "implot_enums.h"

//-----------------------------------------------------------------------------
// [SECTION] Types and Structs
//-----------------------------------------------------------------------------

// Double precision version of ImVec2 used by ImPlot. Extensible by end users.
IM_MSVC_RUNTIME_CHECKS_OFF
struct ImPlotPoint {
    double x, y;
    constexpr ImPlotPoint() : x(0.0), y(0.0) {}
    constexpr ImPlotPoint(double _x, double _y) : x(_x), y(_y) {}
    constexpr ImPlotPoint(const ImVec2 &p) : x((double)p.x), y((double)p.y) {}
    double &operator[](size_t idx) {
        IM_ASSERT(idx == 0 || idx == 1);
        return ((double *)(void *)(char *)this)[idx];
    }
    double operator[](size_t idx) const {
        IM_ASSERT(idx == 0 || idx == 1);
        return ((const double *)(const void *)(const char *)this)[idx];
    }
#ifdef IMPLOT_POINT_CLASS_EXTRA
    IMPLOT_POINT_CLASS_EXTRA // Define additional constructors and implicit cast operators in imconfig.h
                             // to convert back and forth between your math types and ImPlotPoint.
#endif
};
IM_MSVC_RUNTIME_CHECKS_RESTORE

// Range defined by a min/max value.
struct ImPlotRange {
    double Min, Max;
    constexpr ImPlotRange() : Min(0.0), Max(0.0) {}
    constexpr ImPlotRange(double _min, double _max) : Min(_min), Max(_max) {}
    bool Contains(double value) const { return value >= Min && value <= Max; }
    double Size() const { return Max - Min; }
    double Clamp(double value) const { return (value < Min) ? Min : (value > Max) ? Max : value; }
};

// Combination of two range limits for X and Y axes. Also an AABB defined by Min()/Max().
struct ImPlotRect {
    ImPlotRange X, Y;
    constexpr ImPlotRect() : X(0.0, 0.0), Y(0.0, 0.0) {}
    constexpr ImPlotRect(double x_min, double x_max, double y_min, double y_max) : X(x_min, x_max), Y(y_min, y_max) {}
    bool Contains(const ImPlotPoint &p) const { return Contains(p.x, p.y); }
    bool Contains(double x, double y) const { return X.Contains(x) && Y.Contains(y); }
    ImPlotPoint Size() const { return ImPlotPoint(X.Size(), Y.Size()); }
    ImPlotPoint Clamp(const ImPlotPoint &p) { return Clamp(p.x, p.y); }
    ImPlotPoint Clamp(double x, double y) { return ImPlotPoint(X.Clamp(x), Y.Clamp(y)); }
    ImPlotPoint Min() const { return ImPlotPoint(X.Min, Y.Min); }
    ImPlotPoint Max() const { return ImPlotPoint(X.Max, Y.Max); }
};

// Plot style structure
struct ImPlotStyle {
    // item styling variables
    float LineWeight;       // = 1,      item line weight in pixels
    int Marker;             // = ImPlotMarker_None, marker specification
    float MarkerSize;       // = 4,      marker size in pixels (roughly the marker's "radius")
    float MarkerWeight;     // = 1,      outline weight of markers in pixels
    float FillAlpha;        // = 1,      alpha modifier applied to plot fills
    float ErrorBarSize;     // = 5,      error bar whisker width in pixels
    float ErrorBarWeight;   // = 1.5,    error bar whisker weight in pixels
    float DigitalBitHeight; // = 8,      digital channels bit height (at y = 1.0f) in pixels
    float DigitalBitGap;    // = 4,      digital channels bit padding gap in pixels
    // plot styling variables
    float PlotBorderSize; // = 1,      line thickness of border around plot area
    float MinorAlpha;     // = 0.25    alpha multiplier applied to minor axis grid lines
    ImVec2 MajorTickLen;  // = 10,10   major tick lengths for X and Y axes
    ImVec2 MinorTickLen;  // = 5,5     minor tick lengths for X and Y axes
    ImVec2 MajorTickSize; // = 1,1     line thickness of major ticks
    ImVec2 MinorTickSize; // = 1,1     line thickness of minor ticks
    ImVec2 MajorGridSize; // = 1,1     line thickness of major grid lines
    ImVec2 MinorGridSize; // = 1,1     line thickness of minor grid lines
    ImVec2 PlotPadding;   // = 10,10   padding between widget frame and plot area, labels, or outside legends (i.e. main
                          // padding)
    ImVec2 LabelPadding;  // = 5,5     padding between axes labels, tick labels, and plot edge
    ImVec2 LegendPadding; // = 10,10   legend padding from plot edges
    ImVec2 LegendInnerPadding; // = 5,5     legend inner padding from legend edges
    ImVec2 LegendSpacing;      // = 5,0     spacing between legend entries
    ImVec2 MousePosPadding;    // = 10,10   padding between plot edge and interior mouse location text
    ImVec2 AnnotationPadding;  // = 2,2     text padding around annotation labels
    ImVec2 FitPadding; // = 0,0     additional fit padding as a percentage of the fit extents (e.g. ImVec2(0.1f,0.1f)
                       // adds 10% to the fit extents of X and Y)
    ImVec2 PlotDefaultSize; // = 400,300 default size used when ImVec2(0,0) is passed to BeginPlot
    ImVec2 PlotMinSize;     // = 200,150 minimum size plot frame can be when shrunk
    // style colors
    ImVec4 Colors[ImPlotCol_COUNT]; // Array of styling colors. Indexable with ImPlotCol_ enums.
    // colormap
    ImPlotColormap Colormap; // The current colormap. Set this to either an ImPlotColormap_ enum or an index returned by
                             // AddColormap.
    // settings/flags
    bool UseLocalTime; // = false,  axis labels will be formatted for your timezone when ImPlotAxisFlag_Time is enabled
    bool UseISO8601;   // = false,  dates will be formatted according to ISO 8601 where applicable (e.g. YYYY-MM-DD,
                       // YYYY-MM, --MM-DD, etc.)
    bool Use24HourClock; // = false,  times will be formatted using a 24 hour clock
    IMPLOT_API ImPlotStyle();
};

// Input mapping structure. Default values listed. See also MapInputDefault, MapInputReverse.
struct ImPlotInputMap {
    ImGuiMouseButton Pan;          // LMB    enables panning when held,
    int PanMod;                    // none   optional modifier that must be held for panning/fitting
    ImGuiMouseButton Fit;          // LMB    initiates fit when double clicked
    ImGuiMouseButton Select;       // RMB    begins box selection when pressed and confirms selection when released
    ImGuiMouseButton SelectCancel; // LMB    cancels active box selection when pressed; cannot be same as Select
    int SelectMod;                 // none   optional modifier that must be held for box selection
    int SelectHorzMod;             // Alt    expands active box selection horizontally to plot edge when held
    int SelectVertMod;             // Shift  expands active box selection vertically to plot edge when held
    ImGuiMouseButton Menu;         // RMB    opens context menus (if enabled) when clicked
    int OverrideMod;               // Ctrl   when held, all input is ignored; used to enable axis/plots as DND sources
    int ZoomMod;                   // none   optional modifier that must be held for scroll wheel zooming
    float ZoomRate; // 0.1f   zoom rate for scroll (e.g. 0.1f = 10% plot range every scroll click); make negative to
                    // invert
    IMPLOT_API ImPlotInputMap();
};

//-----------------------------------------------------------------------------
// [SECTION] Implementation
//-----------------------------------------------------------------------------

#ifdef IMPLOT_IMPLEMENTATION

// Constructor implementations
inline ImPlotInputMap::ImPlotInputMap() {
    Pan = ImGuiMouseButton_Left;
    Fit = ImGuiMouseButton_Left;
    Select = ImGuiMouseButton_Right;
    SelectCancel = ImGuiMouseButton_Left;
    Menu = ImGuiMouseButton_Right;
    PanMod = ImGuiMod_None;
    SelectMod = ImGuiMod_None;
    SelectHorzMod = ImGuiMod_Alt;
    SelectVertMod = ImGuiMod_Shift;
    OverrideMod = ImGuiMod_Ctrl;
    ZoomMod = ImGuiMod_None;
    ZoomRate = 0.1f;
}

inline ImPlotStyle::ImPlotStyle() {
    LineWeight = 1;
    Marker = ImPlotMarker_None;
    MarkerSize = 4;
    MarkerWeight = 1;
    FillAlpha = 1;
    ErrorBarSize = 5;
    ErrorBarWeight = 1.5f;
    DigitalBitHeight = 8;
    DigitalBitGap = 4;

    PlotBorderSize = 1;
    MinorAlpha = 0.25f;
    MajorTickLen = ImVec2(10, 10);
    MinorTickLen = ImVec2(5, 5);
    MajorTickSize = ImVec2(1, 1);
    MinorTickSize = ImVec2(1, 1);
    MajorGridSize = ImVec2(1, 1);
    MinorGridSize = ImVec2(1, 1);
    PlotPadding = ImVec2(10, 10);
    LabelPadding = ImVec2(5, 5);
    LegendPadding = ImVec2(10, 10);
    LegendInnerPadding = ImVec2(5, 5);
    LegendSpacing = ImVec2(5, 0);
    MousePosPadding = ImVec2(10, 10);
    AnnotationPadding = ImVec2(2, 2);
    FitPadding = ImVec2(0, 0);
    PlotDefaultSize = ImVec2(400, 300);
    PlotMinSize = ImVec2(200, 150);

    // Set default colors - simplified for header-only
    for (int i = 0; i < ImPlotCol_COUNT; i++) {
        Colors[i] = IMPLOT_AUTO_COL;
    }

    Colormap = ImPlotColormap_Deep;

    UseLocalTime = false;
    Use24HourClock = false;
    UseISO8601 = false;
}

#endif // IMPLOT_IMPLEMENTATION
