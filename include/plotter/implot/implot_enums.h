#pragma once

#include "imgui.h"
#include "implot_defines.h"

//-----------------------------------------------------------------------------
// [SECTION] Enums and Types
//-----------------------------------------------------------------------------

// Forward declarations
struct ImPlotContext; // ImPlot context (opaque struct, see implot_internal.h)

// Enums/Flags
typedef int ImAxis;                   // -> enum ImAxis_
typedef int ImPlotFlags;              // -> enum ImPlotFlags_
typedef int ImPlotAxisFlags;          // -> enum ImPlotAxisFlags_
typedef int ImPlotSubplotFlags;       // -> enum ImPlotSubplotFlags_
typedef int ImPlotLegendFlags;        // -> enum ImPlotLegendFlags_
typedef int ImPlotMouseTextFlags;     // -> enum ImPlotMouseTextFlags_
typedef int ImPlotDragToolFlags;      // -> ImPlotDragToolFlags_
typedef int ImPlotColormapScaleFlags; // -> ImPlotColormapScaleFlags_

typedef int ImPlotItemFlags;      // -> ImPlotItemFlags_
typedef int ImPlotLineFlags;      // -> ImPlotLineFlags_
typedef int ImPlotScatterFlags;   // -> ImPlotScatterFlags
typedef int ImPlotStairsFlags;    // -> ImPlotStairsFlags_
typedef int ImPlotShadedFlags;    // -> ImPlotShadedFlags_
typedef int ImPlotBarsFlags;      // -> ImPlotBarsFlags_
typedef int ImPlotBarGroupsFlags; // -> ImPlotBarGroupsFlags_
typedef int ImPlotErrorBarsFlags; // -> ImPlotErrorBarsFlags_
typedef int ImPlotStemsFlags;     // -> ImPlotStemsFlags_
typedef int ImPlotInfLinesFlags;  // -> ImPlotInfLinesFlags_
typedef int ImPlotPieChartFlags;  // -> ImPlotPieChartFlags_
typedef int ImPlotHeatmapFlags;   // -> ImPlotHeatmapFlags_
typedef int ImPlotHistogramFlags; // -> ImPlotHistogramFlags_
typedef int ImPlotDigitalFlags;   // -> ImPlotDigitalFlags_
typedef int ImPlotImageFlags;     // -> ImPlotImageFlags_
typedef int ImPlotTextFlags;      // -> ImPlotTextFlags_
typedef int ImPlotDummyFlags;     // -> ImPlotDummyFlags_

typedef int ImPlotCond;     // -> enum ImPlotCond_
typedef int ImPlotCol;      // -> enum ImPlotCol_
typedef int ImPlotStyleVar; // -> enum ImPlotStyleVar_
typedef int ImPlotScale;    // -> enum ImPlotScale_
typedef int ImPlotMarker;   // -> enum ImPlotMarker_
typedef int ImPlotColormap; // -> enum ImPlotColormap_
typedef int ImPlotLocation; // -> enum ImPlotLocation_
typedef int ImPlotBin;      // -> enum ImPlotBin_

// Axis indices. The values assigned may change; NEVER hardcode these.
enum ImAxis_ {
    // horizontal axes
    ImAxis_X1 = 0, // enabled by default
    ImAxis_X2,     // disabled by default
    ImAxis_X3,     // disabled by default
    // vertical axes
    ImAxis_Y1, // enabled by default
    ImAxis_Y2, // disabled by default
    ImAxis_Y3, // disabled by default
    // bookeeping
    ImAxis_COUNT
};

// Options for plots (see BeginPlot).
enum ImPlotFlags_ {
    ImPlotFlags_None = 0,         // default
    ImPlotFlags_NoTitle = 1 << 0, // the plot title will not be displayed (titles are also hidden if preceeded by double
                                  // hashes, e.g. "##MyPlot")
    ImPlotFlags_NoLegend = 1 << 1, // the legend will not be displayed
    ImPlotFlags_NoMouseText =
        1 << 2,                    // the mouse position, in plot coordinates, will not be displayed inside of the plot
    ImPlotFlags_NoInputs = 1 << 3, // the user will not be able to interact with the plot
    ImPlotFlags_NoMenus = 1 << 4,  // the user will not be able to open context menus
    ImPlotFlags_NoBoxSelect = 1 << 5, // the user will not be able to box-select
    ImPlotFlags_NoFrame = 1 << 6,     // the ImGui frame will not be rendered
    ImPlotFlags_Equal = 1 << 7,       // x and y axes pairs will be constrained to have the same units/pixel
    ImPlotFlags_Crosshairs = 1 << 8,  // the default mouse cursor will be replaced with a crosshair when hovered
    ImPlotFlags_CanvasOnly = ImPlotFlags_NoTitle | ImPlotFlags_NoLegend | ImPlotFlags_NoMenus |
                             ImPlotFlags_NoBoxSelect | ImPlotFlags_NoMouseText
};

// Options for plot axes (see SetupAxis).
enum ImPlotAxisFlags_ {
    ImPlotAxisFlags_None = 0,              // default
    ImPlotAxisFlags_NoLabel = 1 << 0,      // the axis label will not be displayed (axis labels are also hidden if the
                                           // supplied string name is nullptr)
    ImPlotAxisFlags_NoGridLines = 1 << 1,  // no grid lines will be displayed
    ImPlotAxisFlags_NoTickMarks = 1 << 2,  // no tick marks will be displayed
    ImPlotAxisFlags_NoTickLabels = 1 << 3, // no text labels will be displayed
    ImPlotAxisFlags_NoInitialFit = 1 << 4, // axis will not be initially fit to data extents on the first rendered frame
    ImPlotAxisFlags_NoMenus = 1 << 5,      // the user will not be able to open context menus with right-click
    ImPlotAxisFlags_NoSideSwitch = 1 << 6, // the user will not be able to switch the axis side by dragging it
    ImPlotAxisFlags_NoHighlight = 1 << 7,  // the axis will not have its background highlighted when hovered or held
    ImPlotAxisFlags_Opposite =
        1 << 8, // axis ticks and labels will be rendered on the conventionally opposite side (i.e, right or top)
    ImPlotAxisFlags_Foreground =
        1 << 9, // grid lines will be displayed in the foreground (i.e. on top of data) instead of the background
    ImPlotAxisFlags_Invert = 1 << 10,  // the axis will be inverted
    ImPlotAxisFlags_AutoFit = 1 << 11, // axis will be auto-fitting to data extents
    ImPlotAxisFlags_RangeFit =
        1 << 12, // axis will only fit points if the point is in the visible range of the **orthogonal** axis
    ImPlotAxisFlags_PanStretch =
        1 << 13, // panning in a locked or constrained state will cause the axis to stretch if possible
    ImPlotAxisFlags_LockMin = 1 << 14, // the axis minimum value will be locked when panning/zooming
    ImPlotAxisFlags_LockMax = 1 << 15, // the axis maximum value will be locked when panning/zooming
    ImPlotAxisFlags_Lock = ImPlotAxisFlags_LockMin | ImPlotAxisFlags_LockMax,
    ImPlotAxisFlags_NoDecorations = ImPlotAxisFlags_NoLabel | ImPlotAxisFlags_NoGridLines |
                                    ImPlotAxisFlags_NoTickMarks | ImPlotAxisFlags_NoTickLabels,
    ImPlotAxisFlags_AuxDefault = ImPlotAxisFlags_NoGridLines | ImPlotAxisFlags_Opposite
};

// Options for subplots (see BeginSubplot)
enum ImPlotSubplotFlags_ {
    ImPlotSubplotFlags_None = 0,         // default
    ImPlotSubplotFlags_NoTitle = 1 << 0, // the subplot title will not be displayed (titles are also hidden if preceeded
                                         // by double hashes, e.g. "##MySubplot")
    ImPlotSubplotFlags_NoLegend =
        1 << 1, // the legend will not be displayed (only applicable if ImPlotSubplotFlags_ShareItems is enabled)
    ImPlotSubplotFlags_NoMenus = 1 << 2,  // the user will not be able to open context menus with right-click
    ImPlotSubplotFlags_NoResize = 1 << 3, // resize splitters between subplot cells will be not be provided
    ImPlotSubplotFlags_NoAlign = 1 << 4,  // subplot edges will not be aligned vertically or horizontally
    ImPlotSubplotFlags_ShareItems =
        1 << 5, // items across all subplots will be shared and rendered into a single legend entry
    ImPlotSubplotFlags_LinkRows =
        1 << 6, // link the y-axis limits of all plots in each row (does not apply to auxiliary axes)
    ImPlotSubplotFlags_LinkCols =
        1 << 7, // link the x-axis limits of all plots in each column (does not apply to auxiliary axes)
    ImPlotSubplotFlags_LinkAllX =
        1 << 8, // link the x-axis limits in every plot in the subplot (does not apply to auxiliary axes)
    ImPlotSubplotFlags_LinkAllY =
        1 << 9, // link the y-axis limits in every plot in the subplot (does not apply to auxiliary axes)
    ImPlotSubplotFlags_ColMajor =
        1 << 10 // subplots are added in column major order instead of the default row major order
};

// Options for legends (see SetupLegend)
enum ImPlotLegendFlags_ {
    ImPlotLegendFlags_None = 0,                 // default
    ImPlotLegendFlags_NoButtons = 1 << 0,       // legend icons will not function as hide/show buttons
    ImPlotLegendFlags_NoHighlightItem = 1 << 1, // plot items will not be highlighted when their legend entry is hovered
    ImPlotLegendFlags_NoHighlightAxis =
        1 << 2, // axes will not be highlighted when legend entries are hovered (only relevant if x/y-axis count > 1)
    ImPlotLegendFlags_NoMenus = 1 << 3,    // the user will not be able to open context menus with right-click
    ImPlotLegendFlags_Outside = 1 << 4,    // legend will be rendered outside of the plot area
    ImPlotLegendFlags_Horizontal = 1 << 5, // legend entries will be displayed horizontally
    ImPlotLegendFlags_Sort = 1 << 6,       // legend entries will be displayed in alphabetical order
};

// Options for mouse hover text (see SetupMouseText)
enum ImPlotMouseTextFlags_ {
    ImPlotMouseTextFlags_None = 0,            // default
    ImPlotMouseTextFlags_NoAuxAxes = 1 << 0,  // only show the mouse position for primary axes
    ImPlotMouseTextFlags_NoFormat = 1 << 1,   // axes label formatters won't be used to render text
    ImPlotMouseTextFlags_ShowAlways = 1 << 2, // always display mouse position even if plot not hovered
};

// Options for DragPoint, DragLine, DragRect
enum ImPlotDragToolFlags_ {
    ImPlotDragToolFlags_None = 0,           // default
    ImPlotDragToolFlags_NoCursors = 1 << 0, // drag tools won't change cursor icons when hovered or held
    ImPlotDragToolFlags_NoFit = 1 << 1,     // the drag tool won't be considered for plot fits
    ImPlotDragToolFlags_NoInputs = 1 << 2,  // lock the tool from user inputs
    ImPlotDragToolFlags_Delayed =
        1 << 3, // tool rendering will be delayed one frame; useful when applying position-constraints
};

// Flags for ColormapScale
enum ImPlotColormapScaleFlags_ {
    ImPlotColormapScaleFlags_None = 0,          // default
    ImPlotColormapScaleFlags_NoLabel = 1 << 0,  // the colormap axis label will not be displayed
    ImPlotColormapScaleFlags_Opposite = 1 << 1, // render the colormap label and tick labels on the opposite side
    ImPlotColormapScaleFlags_Invert = 1 << 2, // invert the colormap bar and axis scale (this only affects rendering; if
                                              // you only want to reverse the scale mapping, make scale_min > scale_max)
};

// Flags for ANY PlotX function
enum ImPlotItemFlags_ {
    ImPlotItemFlags_None = 0,
    ImPlotItemFlags_NoLegend = 1 << 0, // the item won't have a legend entry displayed
    ImPlotItemFlags_NoFit = 1 << 1,    // the item won't be considered for plot fits
};

// Flags for PlotLine
enum ImPlotLineFlags_ {
    ImPlotLineFlags_None = 0,           // default
    ImPlotLineFlags_Segments = 1 << 10, // a line segment will be rendered from every two consecutive points
    ImPlotLineFlags_Loop = 1 << 11,     // the last and first point will be connected to form a closed loop
    ImPlotLineFlags_SkipNaN = 1 << 12,  // NaNs values will be skipped instead of rendered as missing data
    ImPlotLineFlags_NoClip = 1 << 13,   // markers (if displayed) on the edge of a plot will not be clipped
    ImPlotLineFlags_Shaded = 1 << 14,   // a filled region between the line and horizontal origin will be rendered; use
                                        // PlotShaded for more advanced cases
};

// Flags for PlotScatter
enum ImPlotScatterFlags_ {
    ImPlotScatterFlags_None = 0,         // default
    ImPlotScatterFlags_NoClip = 1 << 10, // markers on the edge of a plot will not be clipped
};

// Flags for PlotStairs
enum ImPlotStairsFlags_ {
    ImPlotStairsFlags_None = 0,          // default
    ImPlotStairsFlags_PreStep = 1 << 10, // the y value is continued constantly to the left from every x position, i.e.
                                         // the interval (x[i-1], x[i]] has the value y[i]
    ImPlotStairsFlags_Shaded = 1 << 11 // a filled region between the stairs and horizontal origin will be rendered; use
                                       // PlotShaded for more advanced cases
};

// Flags for PlotShaded (placeholder)
enum ImPlotShadedFlags_ {
    ImPlotShadedFlags_None = 0 // default
};

// Flags for PlotBars
enum ImPlotBarsFlags_ {
    ImPlotBarsFlags_None = 0,             // default
    ImPlotBarsFlags_Horizontal = 1 << 10, // bars will be rendered horizontally on the current y-axis
};

// Flags for PlotBarGroups
enum ImPlotBarGroupsFlags_ {
    ImPlotBarGroupsFlags_None = 0,             // default
    ImPlotBarGroupsFlags_Horizontal = 1 << 10, // bar groups will be rendered horizontally on the current y-axis
    ImPlotBarGroupsFlags_Stacked = 1 << 11,    // items in a group will be stacked on top of each other
};

// Flags for PlotErrorBars
enum ImPlotErrorBarsFlags_ {
    ImPlotErrorBarsFlags_None = 0,             // default
    ImPlotErrorBarsFlags_Horizontal = 1 << 10, // error bars will be rendered horizontally on the current y-axis
};

// Flags for PlotStems
enum ImPlotStemsFlags_ {
    ImPlotStemsFlags_None = 0,             // default
    ImPlotStemsFlags_Horizontal = 1 << 10, // stems will be rendered horizontally on the current y-axis
};

// Flags for PlotInfLines
enum ImPlotInfLinesFlags_ {
    ImPlotInfLinesFlags_None = 0,            // default
    ImPlotInfLinesFlags_Horizontal = 1 << 10 // lines will be rendered horizontally on the current y-axis
};

// Flags for PlotPieChart
enum ImPlotPieChartFlags_ {
    ImPlotPieChartFlags_None = 0, // default
    ImPlotPieChartFlags_Normalize =
        1 << 10, // force normalization of pie chart values (i.e. always make a full circle if sum < 0)
    ImPlotPieChartFlags_IgnoreHidden =
        1 << 11, // ignore hidden slices when drawing the pie chart (as if they were not there)
    ImPlotPieChartFlags_Exploding = 1 << 12 // Explode legend-hovered slice
};

// Flags for PlotHeatmap
enum ImPlotHeatmapFlags_ {
    ImPlotHeatmapFlags_None = 0,           // default
    ImPlotHeatmapFlags_ColMajor = 1 << 10, // data will be read in column major order
};

// Flags for PlotHistogram and PlotHistogram2D
enum ImPlotHistogramFlags_ {
    ImPlotHistogramFlags_None = 0, // default
    ImPlotHistogramFlags_Horizontal =
        1 << 10, // histogram bars will be rendered horizontally (not supported by PlotHistogram2D)
    ImPlotHistogramFlags_Cumulative = 1 << 11, // each bin will contain its count plus the counts of all previous bins
                                               // (not supported by PlotHistogram2D)
    ImPlotHistogramFlags_Density = 1 << 12,    // counts will be normalized, i.e. the PDF will be visualized, or the CDF
                                               // will be visualized if Cumulative is also set
    ImPlotHistogramFlags_NoOutliers = 1 << 13, // exclude values outside the specifed histogram range from the count
                                               // toward normalizing and cumulative counts
    ImPlotHistogramFlags_ColMajor = 1 << 14 // data will be read in column major order (not supported by PlotHistogram)
};

// Flags for PlotDigital (placeholder)
enum ImPlotDigitalFlags_ {
    ImPlotDigitalFlags_None = 0 // default
};

// Flags for PlotImage (placeholder)
enum ImPlotImageFlags_ {
    ImPlotImageFlags_None = 0 // default
};

// Flags for PlotText
enum ImPlotTextFlags_ {
    ImPlotTextFlags_None = 0,          // default
    ImPlotTextFlags_Vertical = 1 << 10 // text will be rendered vertically
};

// Flags for PlotDummy (placeholder)
enum ImPlotDummyFlags_ {
    ImPlotDummyFlags_None = 0 // default
};

// Represents a condition for SetupAxisLimits etc. (same as ImGuiCond, but we only support a subset of those enums)
enum ImPlotCond_ {
    ImPlotCond_None = ImGuiCond_None,     // No condition (always set the variable), same as _Always
    ImPlotCond_Always = ImGuiCond_Always, // No condition (always set the variable)
    ImPlotCond_Once = ImGuiCond_Once, // Set the variable once per runtime session (only the first call will succeed)
};

// Plot styling colors.
enum ImPlotCol_ {
    // item styling colors
    ImPlotCol_Line,          // plot line/outline color (defaults to next unused color in current colormap)
    ImPlotCol_Fill,          // plot fill color for bars (defaults to the current line color)
    ImPlotCol_MarkerOutline, // marker outline color (defaults to the current line color)
    ImPlotCol_MarkerFill,    // marker fill color (defaults to the current line color)
    ImPlotCol_ErrorBar,      // error bar color (defaults to ImGuiCol_Text)
    // plot styling colors
    ImPlotCol_FrameBg,       // plot frame background color (defaults to ImGuiCol_FrameBg)
    ImPlotCol_PlotBg,        // plot area background color (defaults to ImGuiCol_WindowBg)
    ImPlotCol_PlotBorder,    // plot area border color (defaults to ImGuiCol_Border)
    ImPlotCol_LegendBg,      // legend background color (defaults to ImGuiCol_PopupBg)
    ImPlotCol_LegendBorder,  // legend border color (defaults to ImPlotCol_PlotBorder)
    ImPlotCol_LegendText,    // legend text color (defaults to ImPlotCol_InlayText)
    ImPlotCol_TitleText,     // plot title text color (defaults to ImGuiCol_Text)
    ImPlotCol_InlayText,     // color of text appearing inside of plots (defaults to ImGuiCol_Text)
    ImPlotCol_AxisText,      // axis label and tick lables color (defaults to ImGuiCol_Text)
    ImPlotCol_AxisGrid,      // axis grid color (defaults to 25% ImPlotCol_AxisText)
    ImPlotCol_AxisTick,      // axis tick color (defaults to AxisGrid)
    ImPlotCol_AxisBg,        // background color of axis hover region (defaults to transparent)
    ImPlotCol_AxisBgHovered, // axis hover color (defaults to ImGuiCol_ButtonHovered)
    ImPlotCol_AxisBgActive,  // axis active color (defaults to ImGuiCol_ButtonActive)
    ImPlotCol_Selection,     // box-selection color (defaults to yellow)
    ImPlotCol_Crosshairs,    // crosshairs color (defaults to ImPlotCol_PlotBorder)
    ImPlotCol_COUNT
};

// Plot styling variables.
enum ImPlotStyleVar_ {
    // item styling variables
    ImPlotStyleVar_LineWeight,       // float,  plot item line weight in pixels
    ImPlotStyleVar_Marker,           // int,    marker specification
    ImPlotStyleVar_MarkerSize,       // float,  marker size in pixels (roughly the marker's "radius")
    ImPlotStyleVar_MarkerWeight,     // float,  plot outline weight of markers in pixels
    ImPlotStyleVar_FillAlpha,        // float,  alpha modifier applied to all plot item fills
    ImPlotStyleVar_ErrorBarSize,     // float,  error bar whisker width in pixels
    ImPlotStyleVar_ErrorBarWeight,   // float,  error bar whisker weight in pixels
    ImPlotStyleVar_DigitalBitHeight, // float,  digital channels bit height (at 1) in pixels
    ImPlotStyleVar_DigitalBitGap,    // float,  digital channels bit padding gap in pixels
    // plot styling variables
    ImPlotStyleVar_PlotBorderSize, // float,  thickness of border around plot area
    ImPlotStyleVar_MinorAlpha,     // float,  alpha multiplier applied to minor axis grid lines
    ImPlotStyleVar_MajorTickLen,   // ImVec2, major tick lengths for X and Y axes
    ImPlotStyleVar_MinorTickLen,   // ImVec2, minor tick lengths for X and Y axes
    ImPlotStyleVar_MajorTickSize,  // ImVec2, line thickness of major ticks
    ImPlotStyleVar_MinorTickSize,  // ImVec2, line thickness of minor ticks
    ImPlotStyleVar_MajorGridSize,  // ImVec2, line thickness of major grid lines
    ImPlotStyleVar_MinorGridSize,  // ImVec2, line thickness of minor grid lines
    ImPlotStyleVar_PlotPadding,  // ImVec2, padding between widget frame and plot area, labels, or outside legends (i.e.
                                 // main padding)
    ImPlotStyleVar_LabelPadding, // ImVec2, padding between axes labels, tick labels, and plot edge
    ImPlotStyleVar_LegendPadding,      // ImVec2, legend padding from plot edges
    ImPlotStyleVar_LegendInnerPadding, // ImVec2, legend inner padding from legend edges
    ImPlotStyleVar_LegendSpacing,      // ImVec2, spacing between legend entries
    ImPlotStyleVar_MousePosPadding,    // ImVec2, padding between plot edge and interior info text
    ImPlotStyleVar_AnnotationPadding,  // ImVec2, text padding around annotation labels
    ImPlotStyleVar_FitPadding,         // ImVec2, additional fit padding as a percentage of the fit extents (e.g.
                                       // ImVec2(0.1f,0.1f) adds 10% to the fit extents of X and Y)
    ImPlotStyleVar_PlotDefaultSize,    // ImVec2, default size used when ImVec2(0,0) is passed to BeginPlot
    ImPlotStyleVar_PlotMinSize,        // ImVec2, minimum size plot frame can be when shrunk
    ImPlotStyleVar_COUNT
};

// Axis scale
enum ImPlotScale_ {
    ImPlotScale_Linear = 0, // default linear scale
    ImPlotScale_Time,       // date/time scale
    ImPlotScale_Log10,      // base 10 logartithmic scale
    ImPlotScale_SymLog,     // symmetric log scale
};

// Marker specifications.
enum ImPlotMarker_ {
    ImPlotMarker_None = -1, // no marker
    ImPlotMarker_Circle,    // a circle marker (default)
    ImPlotMarker_Square,    // a square maker
    ImPlotMarker_Diamond,   // a diamond marker
    ImPlotMarker_Up,        // an upward-pointing triangle marker
    ImPlotMarker_Down,      // an downward-pointing triangle marker
    ImPlotMarker_Left,      // an leftward-pointing triangle marker
    ImPlotMarker_Right,     // an rightward-pointing triangle marker
    ImPlotMarker_Cross,     // a cross marker (not fillable)
    ImPlotMarker_Plus,      // a plus marker (not fillable)
    ImPlotMarker_Asterisk,  // a asterisk marker (not fillable)
    ImPlotMarker_COUNT
};

// Built-in colormaps
enum ImPlotColormap_ {
    ImPlotColormap_Deep = 0,      // a.k.a. seaborn deep             (qual=true,  n=10) (default)
    ImPlotColormap_Dark = 1,      // a.k.a. matplotlib "Set1"        (qual=true,  n=9 )
    ImPlotColormap_Pastel = 2,    // a.k.a. matplotlib "Pastel1"     (qual=true,  n=9 )
    ImPlotColormap_Paired = 3,    // a.k.a. matplotlib "Paired"      (qual=true,  n=12)
    ImPlotColormap_Viridis = 4,   // a.k.a. matplotlib "viridis"     (qual=false, n=11)
    ImPlotColormap_Plasma = 5,    // a.k.a. matplotlib "plasma"      (qual=false, n=11)
    ImPlotColormap_Hot = 6,       // a.k.a. matplotlib/MATLAB "hot"  (qual=false, n=11)
    ImPlotColormap_Cool = 7,      // a.k.a. matplotlib/MATLAB "cool" (qual=false, n=11)
    ImPlotColormap_Pink = 8,      // a.k.a. matplotlib/MATLAB "pink" (qual=false, n=11)
    ImPlotColormap_Jet = 9,       // a.k.a. MATLAB "jet"             (qual=false, n=11)
    ImPlotColormap_Twilight = 10, // a.k.a. matplotlib "twilight"    (qual=false, n=11)
    ImPlotColormap_RdBu = 11,     // red/blue, Color Brewer          (qual=false, n=11)
    ImPlotColormap_BrBG = 12,     // brown/blue-green, Color Brewer  (qual=false, n=11)
    ImPlotColormap_PiYG = 13,     // pink/yellow-green, Color Brewer (qual=false, n=11)
    ImPlotColormap_Spectral = 14, // color spectrum, Color Brewer    (qual=false, n=11)
    ImPlotColormap_Greys = 15,    // white/black                     (qual=false, n=2 )
};

// Used to position items on a plot (e.g. legends, labels, etc.)
enum ImPlotLocation_ {
    ImPlotLocation_Center = 0,                                             // center-center
    ImPlotLocation_North = 1 << 0,                                         // top-center
    ImPlotLocation_South = 1 << 1,                                         // bottom-center
    ImPlotLocation_West = 1 << 2,                                          // center-left
    ImPlotLocation_East = 1 << 3,                                          // center-right
    ImPlotLocation_NorthWest = ImPlotLocation_North | ImPlotLocation_West, // top-left
    ImPlotLocation_NorthEast = ImPlotLocation_North | ImPlotLocation_East, // top-right
    ImPlotLocation_SouthWest = ImPlotLocation_South | ImPlotLocation_West, // bottom-left
    ImPlotLocation_SouthEast = ImPlotLocation_South | ImPlotLocation_East  // bottom-right
};

// Enums for different automatic histogram binning methods (k = bin count or w = bin width)
enum ImPlotBin_ {
    ImPlotBin_Sqrt = -1,    // k = sqrt(n)
    ImPlotBin_Sturges = -2, // k = 1 + log2(n)
    ImPlotBin_Rice = -3,    // k = 2 * cbrt(n)
    ImPlotBin_Scott = -4,   // w = 3.49 * sigma / cbrt(n)
};
