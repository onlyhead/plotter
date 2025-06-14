#pragma once

#include "implot.h"

// Forward declarations
struct ImPlotContext;
struct ImPlotStyleVarInfo;

// Global plot context (defined in implot_context.cpp)
#ifndef GImPlot
extern ImPlotContext *GImPlot;
#endif

// Internal initialization functions
void Initialize(ImPlotContext *ctx);
void ResetCtxForNextPlot(ImPlotContext *ctx);
void ResetCtxForNextAlignedPlots(ImPlotContext *ctx);
void ResetCtxForNextSubplot(ImPlotContext *ctx);

// Style helpers
ImVec4 GetAutoColor(ImPlotCol idx);
const ImPlotStyleVarInfo *GetPlotStyleVarInfo(ImPlotStyleVar idx);

// Text rendering helpers
void AddTextVertical(ImDrawList *DrawList, ImVec2 pos, ImU32 col, const char *text_begin,
                     const char *text_end = nullptr);
void AddTextCentered(ImDrawList *DrawList, ImVec2 top_center, ImU32 col, const char *text_begin,
                     const char *text_end = nullptr);

// Version compatibility
#if (IMGUI_VERSION_NUM < 18102) && !defined(ImDrawFlags_RoundCornersAll)
#define ImDrawFlags_RoundCornersAll ImDrawCornerFlags_All
#endif

#if (IMGUI_VERSION_NUM < 18966)
#define ImGuiButtonFlags_AllowOverlap ImGuiButtonFlags_AllowItemOverlap
#endif
