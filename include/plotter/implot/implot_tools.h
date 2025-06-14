#pragma once

#include "implot_enums.h"
#include <stdarg.h>

namespace ImPlot {

    //-----------------------------------------------------------------------------
    // [SECTION] Plot Tools
    //-----------------------------------------------------------------------------

    // The following can be used to render interactive elements and/or annotations.
    // Like the item plotting functions above, they apply to the current x and y
    // axes, which can be changed with `SetAxis/SetAxes`. These functions return true
    // when user interaction causes the provided coordinates to change. Additional
    // user interactions can be retrieved through the optional output parameters.

    // Shows a draggable point at x,y. #col defaults to ImGuiCol_Text.
    IMPLOT_API bool DragPoint(int id, double *x, double *y, const ImVec4 &col, float size = 4,
                              ImPlotDragToolFlags flags = 0, bool *out_clicked = nullptr, bool *out_hovered = nullptr,
                              bool *held = nullptr);
    // Shows a draggable vertical guide line at an x-value. #col defaults to ImGuiCol_Text.
    IMPLOT_API bool DragLineX(int id, double *x, const ImVec4 &col, float thickness = 1, ImPlotDragToolFlags flags = 0,
                              bool *out_clicked = nullptr, bool *out_hovered = nullptr, bool *held = nullptr);
    // Shows a draggable horizontal guide line at a y-value. #col defaults to ImGuiCol_Text.
    IMPLOT_API bool DragLineY(int id, double *y, const ImVec4 &col, float thickness = 1, ImPlotDragToolFlags flags = 0,
                              bool *out_clicked = nullptr, bool *out_hovered = nullptr, bool *held = nullptr);
    // Shows a draggable and resizeable rectangle.
    IMPLOT_API bool DragRect(int id, double *x1, double *y1, double *x2, double *y2, const ImVec4 &col,
                             ImPlotDragToolFlags flags = 0, bool *out_clicked = nullptr, bool *out_hovered = nullptr,
                             bool *held = nullptr);

    // Shows an annotation callout at a chosen point. Clamping keeps annotations in the plot area. Annotations are
    // always rendered on top.
    IMPLOT_API void Annotation(double x, double y, const ImVec4 &col, const ImVec2 &pix_offset, bool clamp,
                               bool round = false);
    IMPLOT_API void Annotation(double x, double y, const ImVec4 &col, const ImVec2 &pix_offset, bool clamp,
                               const char *fmt, ...) IM_FMTARGS(6);
    IMPLOT_API void AnnotationV(double x, double y, const ImVec4 &col, const ImVec2 &pix_offset, bool clamp,
                                const char *fmt, va_list args) IM_FMTLIST(6);

    // Shows a x-axis tag at the specified coordinate value.
    IMPLOT_API void TagX(double x, const ImVec4 &col, bool round = false);
    IMPLOT_API void TagX(double x, const ImVec4 &col, const char *fmt, ...) IM_FMTARGS(3);
    IMPLOT_API void TagXV(double x, const ImVec4 &col, const char *fmt, va_list args) IM_FMTLIST(3);

    // Shows a y-axis tag at the specified coordinate value.
    IMPLOT_API void TagY(double y, const ImVec4 &col, bool round = false);
    IMPLOT_API void TagY(double y, const ImVec4 &col, const char *fmt, ...) IM_FMTARGS(3);
    IMPLOT_API void TagYV(double y, const ImVec4 &col, const char *fmt, va_list args) IM_FMTLIST(3);

} // namespace ImPlot
