#pragma once

#include "implot_defines.h"
#include "implot_types.h"

namespace ImPlot {

    //-----------------------------------------------------------------------------
    // Styling and Colors
    //-----------------------------------------------------------------------------

    // Gets the name string for an ImPlotCol.
    IMPLOT_API const char *GetStyleColorName(ImPlotCol col);

    // Gets the name string for an ImPlotMarker.
    IMPLOT_API const char *GetMarkerName(ImPlotMarker marker);

    // Gets an automatic color from the current colormap
    IMPLOT_API ImVec4 GetAutoColor(ImPlotCol idx);

} // namespace ImPlot

//-----------------------------------------------------------------------------
// IMPLEMENTATION
//-----------------------------------------------------------------------------

#ifdef IMPLOT_IMPLEMENTATION

namespace ImPlot {

    struct ImPlotStyleVarInfo {
        ImGuiDataType Type;
        ImU32 Count;
        ImU32 Offset;
        void *GetVarPtr(ImPlotStyle *style) const { return (void *)((unsigned char *)style + Offset); }
    };

    static const ImPlotStyleVarInfo GPlotStyleVarInfo[] = {
        {ImGuiDataType_Float, 1, (ImU32)offsetof(ImPlotStyle, LineWeight)},       // ImPlotStyleVar_LineWeight
        {ImGuiDataType_S32, 1, (ImU32)offsetof(ImPlotStyle, Marker)},             // ImPlotStyleVar_Marker
        {ImGuiDataType_Float, 1, (ImU32)offsetof(ImPlotStyle, MarkerSize)},       // ImPlotStyleVar_MarkerSize
        {ImGuiDataType_Float, 1, (ImU32)offsetof(ImPlotStyle, MarkerWeight)},     // ImPlotStyleVar_MarkerWeight
        {ImGuiDataType_Float, 1, (ImU32)offsetof(ImPlotStyle, FillAlpha)},        // ImPlotStyleVar_FillAlpha
        {ImGuiDataType_Float, 1, (ImU32)offsetof(ImPlotStyle, ErrorBarSize)},     // ImPlotStyleVar_ErrorBarSize
        {ImGuiDataType_Float, 1, (ImU32)offsetof(ImPlotStyle, ErrorBarWeight)},   // ImPlotStyleVar_ErrorBarWeight
        {ImGuiDataType_Float, 1, (ImU32)offsetof(ImPlotStyle, DigitalBitHeight)}, // ImPlotStyleVar_DigitalBitHeight
        {ImGuiDataType_Float, 1, (ImU32)offsetof(ImPlotStyle, DigitalBitGap)},    // ImPlotStyleVar_DigitalBitGap

        {ImGuiDataType_Float, 1, (ImU32)offsetof(ImPlotStyle, PlotBorderSize)},     // ImPlotStyleVar_PlotBorderSize
        {ImGuiDataType_Float, 1, (ImU32)offsetof(ImPlotStyle, MinorAlpha)},         // ImPlotStyleVar_MinorAlpha
        {ImGuiDataType_Float, 2, (ImU32)offsetof(ImPlotStyle, MajorTickLen)},       // ImPlotStyleVar_MajorTickLen
        {ImGuiDataType_Float, 2, (ImU32)offsetof(ImPlotStyle, MinorTickLen)},       // ImPlotStyleVar_MinorTickLen
        {ImGuiDataType_Float, 2, (ImU32)offsetof(ImPlotStyle, MajorTickSize)},      // ImPlotStyleVar_MajorTickSize
        {ImGuiDataType_Float, 2, (ImU32)offsetof(ImPlotStyle, MinorTickSize)},      // ImPlotStyleVar_MinorTickSize
        {ImGuiDataType_Float, 2, (ImU32)offsetof(ImPlotStyle, MajorGridSize)},      // ImPlotStyleVar_MajorGridSize
        {ImGuiDataType_Float, 2, (ImU32)offsetof(ImPlotStyle, MinorGridSize)},      // ImPlotStyleVar_MinorGridSize
        {ImGuiDataType_Float, 2, (ImU32)offsetof(ImPlotStyle, PlotPadding)},        // ImPlotStyleVar_PlotPadding
        {ImGuiDataType_Float, 2, (ImU32)offsetof(ImPlotStyle, LabelPadding)},       // ImPlotStyleVar_LabelPaddine
        {ImGuiDataType_Float, 2, (ImU32)offsetof(ImPlotStyle, LegendPadding)},      // ImPlotStyleVar_LegendPadding
        {ImGuiDataType_Float, 2, (ImU32)offsetof(ImPlotStyle, LegendInnerPadding)}, // ImPlotStyleVar_LegendInnerPadding
        {ImGuiDataType_Float, 2, (ImU32)offsetof(ImPlotStyle, LegendSpacing)},      // ImPlotStyleVar_LegendSpacing

        {ImGuiDataType_Float, 2, (ImU32)offsetof(ImPlotStyle, MousePosPadding)},   // ImPlotStyleVar_MousePosPadding
        {ImGuiDataType_Float, 2, (ImU32)offsetof(ImPlotStyle, AnnotationPadding)}, // ImPlotStyleVar_AnnotationPadding
        {ImGuiDataType_Float, 2, (ImU32)offsetof(ImPlotStyle, FitPadding)},        // ImPlotStyleVar_FitPadding
        {ImGuiDataType_Float, 2, (ImU32)offsetof(ImPlotStyle, PlotDefaultSize)},   // ImPlotStyleVar_PlotDefaultSize
        {ImGuiDataType_Float, 2, (ImU32)offsetof(ImPlotStyle, PlotMinSize)}        // ImPlotStyleVar_PlotMinSize
    };

    static const ImPlotStyleVarInfo *GetPlotStyleVarInfo(ImPlotStyleVar idx) {
        IM_ASSERT(idx >= 0 && idx < ImPlotStyleVar_COUNT);
        IM_ASSERT(IM_ARRAYSIZE(GPlotStyleVarInfo) == ImPlotStyleVar_COUNT);
        return &GPlotStyleVarInfo[idx];
    }

    inline const char *GetStyleColorName(ImPlotCol col) {
        static const char *col_names[ImPlotCol_COUNT] = {
            "Line",       "Fill",     "MarkerOutline", "MarkerFill",    "ErrorBar",     "FrameBg",   "PlotBg",
            "PlotBorder", "LegendBg", "LegendBorder",  "LegendText",    "TitleText",    "InlayText", "AxisText",
            "AxisGrid",   "AxisTick", "AxisBg",        "AxisBgHovered", "AxisBgActive", "Selection", "Crosshairs"};
        return col_names[col];
    }

    inline const char *GetMarkerName(ImPlotMarker marker) {
        switch (marker) {
        case ImPlotMarker_None:
            return "None";
        case ImPlotMarker_Circle:
            return "Circle";
        case ImPlotMarker_Square:
            return "Square";
        case ImPlotMarker_Diamond:
            return "Diamond";
        case ImPlotMarker_Up:
            return "Up";
        case ImPlotMarker_Down:
            return "Down";
        case ImPlotMarker_Left:
            return "Left";
        case ImPlotMarker_Right:
            return "Right";
        case ImPlotMarker_Cross:
            return "Cross";
        case ImPlotMarker_Plus:
            return "Plus";
        case ImPlotMarker_Asterisk:
            return "Asterisk";
        default:
            return "";
        }
    }

    inline ImVec4 GetAutoColor(ImPlotCol idx) {
        ImVec4 col(0, 0, 0, 1);
        switch (idx) {
        case ImPlotCol_Line:
            return col; // these are plot dependent!
        case ImPlotCol_Fill:
            return col; // these are plot dependent!
        case ImPlotCol_MarkerOutline:
            return col; // these are plot dependent!
        case ImPlotCol_MarkerFill:
            return col; // these are plot dependent!
        case ImPlotCol_ErrorBar:
            return ImGui::GetStyleColorVec4(ImGuiCol_Text);
        case ImPlotCol_FrameBg:
            return ImGui::GetStyleColorVec4(ImGuiCol_FrameBg);
        case ImPlotCol_PlotBg:
            return ImGui::GetStyleColorVec4(ImGuiCol_WindowBg);
        case ImPlotCol_PlotBorder:
            return ImGui::GetStyleColorVec4(ImGuiCol_Border);
        case ImPlotCol_LegendBg:
            return ImGui::GetStyleColorVec4(ImGuiCol_PopupBg);
        case ImPlotCol_LegendBorder:
            return GetStyleColorVec4(ImPlotCol_PlotBorder);
        case ImPlotCol_LegendText:
            return GetStyleColorVec4(ImPlotCol_InlayText);
        case ImPlotCol_TitleText:
            return ImGui::GetStyleColorVec4(ImGuiCol_Text);
        case ImPlotCol_InlayText:
            return ImGui::GetStyleColorVec4(ImGuiCol_Text);
        case ImPlotCol_AxisText:
            return ImGui::GetStyleColorVec4(ImGuiCol_Text);
        case ImPlotCol_AxisGrid:
            return GetStyleColorVec4(ImPlotCol_AxisText) * ImVec4(1, 1, 1, 0.25f);
        case ImPlotCol_AxisTick:
            return GetStyleColorVec4(ImPlotCol_AxisGrid);
        case ImPlotCol_AxisBg:
            return ImVec4(0, 0, 0, 0);
        case ImPlotCol_AxisBgHovered:
            return ImGui::GetStyleColorVec4(ImGuiCol_ButtonHovered);
        case ImPlotCol_AxisBgActive:
            return ImGui::GetStyleColorVec4(ImGuiCol_ButtonActive);
        case ImPlotCol_Selection:
            return ImVec4(1, 1, 0, 1);
        case ImPlotCol_Crosshairs:
            return GetStyleColorVec4(ImPlotCol_PlotBorder);
        default:
            return col;
        }
    }

} // namespace ImPlot

#endif // IMPLOT_IMPLEMENTATION
