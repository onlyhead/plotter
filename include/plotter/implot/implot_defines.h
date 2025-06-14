#pragma once

//-----------------------------------------------------------------------------
// [SECTION] Macros and Defines
//-----------------------------------------------------------------------------

// Define attributes of all API symbols declarations (e.g. for DLL under Windows)
// Using ImPlot via a shared library is not recommended, because we don't guarantee
// backward nor forward ABI compatibility and also function call overhead. If you
// do use ImPlot as a DLL, be sure to call SetImGuiContext (see Miscellanous section).
#ifndef IMPLOT_API
#define IMPLOT_API
#endif

// ImPlot version string.
#define IMPLOT_VERSION "0.17"
// Indicates variable should deduced automatically.
#define IMPLOT_AUTO -1
// Special color used to indicate that a color should be deduced automatically.
#define IMPLOT_AUTO_COL ImVec4(0, 0, 0, -1)
// Macro for templated plotting functions; keeps header clean.
#define IMPLOT_TMP template <typename T> IMPLOT_API

// Support for legacy versions
#if (IMGUI_VERSION_NUM < 18716) // Renamed in 1.88
#define ImGuiMod_None 0
#define ImGuiMod_Ctrl ImGuiKeyModFlags_Ctrl
#define ImGuiMod_Shift ImGuiKeyModFlags_Shift
#define ImGuiMod_Alt ImGuiKeyModFlags_Alt
#define ImGuiMod_Super ImGuiKeyModFlags_Super
#elif (IMGUI_VERSION_NUM < 18823) // Renamed in 1.89, sorry
#define ImGuiMod_None 0
#define ImGuiMod_Ctrl ImGuiModFlags_Ctrl
#define ImGuiMod_Shift ImGuiModFlags_Shift
#define ImGuiMod_Alt ImGuiModFlags_Alt
#define ImGuiMod_Super ImGuiModFlags_Super
#endif
