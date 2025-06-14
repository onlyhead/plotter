// MIT License

// Copyright (c) 2023 Evan Pezent

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

// ImPlot - Header-Only Plotting Library
// Version 0.17
// https://github.com/epezent/implot

// HEADER-ONLY LIBRARY USAGE:
// Define IMPLOT_IMPLEMENTATION in exactly one C++ file before including this header:
//
//   #define IMPLOT_IMPLEMENTATION
//   #include "implot.h"
//
// All implementation is contained in the headers. No separate .cpp files needed!

// API VERSION
#define IMPLOT_VERSION_NUM 17000
#define IMPLOT_VERSION "0.17.0"

// Include all ImPlot modular headers
#include "implot_callbacks.h"
#include "implot_colormaps.h"
#include "implot_context.h"
#include "implot_core.h"
#include "implot_defines.h"
#include "implot_enums.h"
#include "implot_globals.h"
#include "implot_input.h"
#include "implot_items.h"
#include "implot_misc.h"
#include "implot_obsolete.h"
#include "implot_setup.h"
#include "implot_styling.h"
#include "implot_tools.h"
#include "implot_types.h"
#include "implot_utils.h"

//-----------------------------------------------------------------------------
// FORWARD DECLARATIONS
//-----------------------------------------------------------------------------

struct ImDrawList;
struct ImFont;
struct ImGuiInputTextCallbackData;
struct ImGuiContext;
struct ImRect;
struct ImVec2;
struct ImVec4;

namespace ImPlot {

    // Main context structure is defined in implot_types.h
    struct ImPlotContext;

    // All API functions are declared in their respective modular headers.
    // This main header simply includes everything to provide the complete ImPlot API.

} // namespace ImPlot

//-----------------------------------------------------------------------------
// IMPLEMENTATION NOTES
//-----------------------------------------------------------------------------
/*

This is a header-only library. All implementation is contained within the headers
under the IMPLOT_IMPLEMENTATION guard. To use:

1. Include this header in your project
2. In exactly ONE C++ file, define IMPLOT_IMPLEMENTATION before including:

    #define IMPLOT_IMPLEMENTATION
    #include "implot.h"

3. Link with ImGui (this library depends on Dear ImGui)

The library has been refactored from the original monolithic implot.h/implot.cpp
into a modular header-only structure for better organization and maintenance.

All original functionality is preserved. The API remains the same.

*/
