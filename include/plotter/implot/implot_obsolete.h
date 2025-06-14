#pragma once

#include "implot_enums.h"

//-----------------------------------------------------------------------------
// [SECTION] Obsolete API
//-----------------------------------------------------------------------------

// The following functions will be removed! Keep your copy of implot up to date!
// Occasionally set '#define IMPLOT_DISABLE_OBSOLETE_FUNCTIONS' to stay ahead.
// If you absolutely must use these functions and do not want to receive compiler
// warnings, set '#define IMPLOT_DISABLE_OBSOLETE_WARNINGS'.

#ifndef IMPLOT_DISABLE_OBSOLETE_FUNCTIONS

#ifndef IMPLOT_DISABLE_DEPRECATED_WARNINGS
#if __cplusplus > 201402L
#define IMPLOT_DEPRECATED(method) [[deprecated]] method
#elif defined(__GNUC__) && !defined(__INTEL_COMPILER) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1))
#define IMPLOT_DEPRECATED(method) method __attribute__((deprecated))
#elif defined(_MSC_VER)
#define IMPLOT_DEPRECATED(method) __declspec(deprecated) method
#else
#define IMPLOT_DEPRECATED(method) method
#endif
#else
#define IMPLOT_DEPRECATED(method) method
#endif

enum ImPlotFlagsObsolete_ {
    ImPlotFlags_YAxis2 = 1 << 20,
    ImPlotFlags_YAxis3 = 1 << 21,
};

namespace ImPlot {

    // OBSOLETED in v0.13 -> PLANNED REMOVAL in v1.0
    IMPLOT_DEPRECATED(IMPLOT_API bool BeginPlot(const char *title_id,
                                                const char *x_label, // = nullptr,
                                                const char *y_label, // = nullptr,
                                                const ImVec2 &size = ImVec2(-1, 0),
                                                ImPlotFlags flags = ImPlotFlags_None, ImPlotAxisFlags x_flags = 0,
                                                ImPlotAxisFlags y_flags = 0,
                                                ImPlotAxisFlags y2_flags = ImPlotAxisFlags_AuxDefault,
                                                ImPlotAxisFlags y3_flags = ImPlotAxisFlags_AuxDefault,
                                                const char *y2_label = nullptr, const char *y3_label = nullptr));

} // namespace ImPlot

#endif // #ifndef IMPLOT_DISABLE_OBSOLETE_FUNCTIONS
