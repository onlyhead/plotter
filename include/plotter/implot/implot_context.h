#pragma once

#include "implot_defines.h"
#include "implot_types.h"

// Forward declarations
struct ImGuiContext;

namespace ImPlot {

    //-----------------------------------------------------------------------------
    // Context Management
    //-----------------------------------------------------------------------------

    // Sets the current ImGui context. This is OPTIONAL and only needed if you are compiling
    // ImPlot as a DLL (not recommended) or if you want to multiple ImGui contexts.
    IMPLOT_API void SetImGuiContext(ImGuiContext *ctx);

    // Creates a new ImPlot context. Call this after ImGui::CreateContext() and before any other ImPlot function.
    // ImPlot will use the current ImGui context if available.
    IMPLOT_API ImPlotContext *CreateContext();

    // Destroys an ImPlot context. NULL = destroy current context.
    IMPLOT_API void DestroyContext(ImPlotContext *ctx = nullptr);

    // Returns the current ImPlot context. NULL if no context has been set.
    IMPLOT_API ImPlotContext *GetCurrentContext();

    // Sets the current ImPlot context.
    IMPLOT_API void SetCurrentContext(ImPlotContext *ctx);

    // Initializes an ImPlot context (automatically called by CreateContext).
    IMPLOT_API void Initialize(ImPlotContext *ctx);

} // namespace ImPlot

//-----------------------------------------------------------------------------
// IMPLEMENTATION
//-----------------------------------------------------------------------------

#ifdef IMPLOT_IMPLEMENTATION

#ifndef GImPlot
namespace ImPlot {
    extern ImPlotContext *GImPlot;
}
#endif

namespace ImPlot {

    inline void SetImGuiContext(ImGuiContext *ctx) { ImGui::SetCurrentContext(ctx); }

    inline ImPlotContext *CreateContext() {
        ImPlotContext *ctx = IM_NEW(ImPlotContext)();
        Initialize(ctx);
        if (GImPlot == nullptr)
            SetCurrentContext(ctx);
        return ctx;
    }

    inline void DestroyContext(ImPlotContext *ctx) {
        if (ctx == nullptr)
            ctx = GImPlot;
        if (GImPlot == ctx)
            SetCurrentContext(nullptr);
        IM_DELETE(ctx);
    }

    inline ImPlotContext *GetCurrentContext() { return GImPlot; }

    inline void SetCurrentContext(ImPlotContext *ctx) { GImPlot = ctx; }

    inline void ResetCtxForNextPlot(ImPlotContext *ctx) {
        // reset the next plot/item data
        ctx->NextPlotData.Reset();
        ctx->NextItemData.Reset();
        // reset labels
        ctx->Annotations.Reset();
        ctx->Tags.Reset();
        // reset extents/fit
        ctx->OpenContextThisFrame = false;
        // reset digital plot items count
        ctx->DigitalPlotItemCnt = 0;
        ctx->DigitalPlotOffset = 0;
        // nullify plot
        ctx->CurrentPlot = nullptr;
        ctx->CurrentItem = nullptr;
        ctx->PreviousItem = nullptr;
    }

    inline void ResetCtxForNextAlignedPlots(ImPlotContext *ctx) {
        ctx->CurrentAlignmentH = nullptr;
        ctx->CurrentAlignmentV = nullptr;
    }

    inline void ResetCtxForNextSubplot(ImPlotContext *ctx) {
        ctx->CurrentSubplot = nullptr;
        ctx->CurrentAlignmentH = nullptr;
        ctx->CurrentAlignmentV = nullptr;
    }

#define IMPLOT_APPEND_CMAP(name, qual) ctx->ColormapData.Append(#name, name, sizeof(name) / sizeof(ImU32), qual)
#define IM_RGB(r, g, b) IM_COL32(r, g, b, 255)

    inline void Initialize(ImPlotContext *ctx) {
        ResetCtxForNextPlot(ctx);
        ResetCtxForNextAlignedPlots(ctx);
        ResetCtxForNextSubplot(ctx);

        const ImU32 Deep[] = {4289753676, 4283598045, 4285048917, 4283584196, 4289950337,
                              4284512403, 4291005402, 4287401100, 4285839820, 4291671396};
        const ImU32 Dark[] = {4280031972, 4290281015, 4283084621, 4288892568, 4278222847,
                              4281597951, 4280833702, 4290740727, 4288256409};
        const ImU32 Pastel[] = {4289639675, 4293119411, 4291161036, 4293184478, 4289124862,
                                4291624959, 4290631909, 4293712637, 4294111986};
        const ImU32 Paired[] = {4293119554, 4290017311, 4287291314, 4281114675, 4288256763, 4280031971,
                                4285513725, 4278222847, 4292260554, 4288298346, 4288282623, 4280834481};
        const ImU32 Viridis[] = {4283695428, 4285867080, 4287054913, 4287455029, 4287526954, 4287402273,
                                 4286883874, 4285579076, 4283552122, 4280737725, 4280674301};
        const ImU32 Plasma[] = {4287039501, 4288480321, 4289200234, 4288941455, 4287638193, 4286072780,
                                4284638433, 4283139314, 4281771772, 4280667900, 4280416752};
        const ImU32 Hot[] = {4278190144, 4278190208, 4278190271, 4278190335, 4278206719, 4278223103,
                             4278239231, 4278255615, 4283826175, 4289396735, 4294967295};
        const ImU32 Cool[] = {4294967040, 4294960666, 4294954035, 4294947661, 4294941030, 4294934656,
                              4294928025, 4294921651, 4294915020, 4294908646, 4294902015};
        const ImU32 Pink[] = {4278190154, 4282532475, 4284308894, 4285690554, 4286879686, 4287870160,
                              4288794330, 4289651940, 4291685869, 4293392118, 4294967295};
        const ImU32 Jet[] = {4289331200, 4294901760, 4294923520, 4294945280, 4294967040, 4289396565,
                             4283826090, 4278255615, 4278233855, 4278212095, 4278190335};
        const ImU32 Twilight[] = {IM_RGB(226, 217, 226), IM_RGB(166, 191, 202), IM_RGB(109, 144, 192),
                                  IM_RGB(95, 88, 176),   IM_RGB(83, 30, 124),   IM_RGB(47, 20, 54),
                                  IM_RGB(100, 25, 75),   IM_RGB(159, 60, 80),   IM_RGB(192, 117, 94),
                                  IM_RGB(208, 179, 158), IM_RGB(226, 217, 226)};
        const ImU32 RdBu[] = {IM_RGB(103, 0, 31),    IM_RGB(178, 24, 43),   IM_RGB(214, 96, 77),
                              IM_RGB(244, 165, 130), IM_RGB(253, 219, 199), IM_RGB(247, 247, 247),
                              IM_RGB(209, 229, 240), IM_RGB(146, 197, 222), IM_RGB(67, 147, 195),
                              IM_RGB(33, 102, 172),  IM_RGB(5, 48, 97)};
        const ImU32 BrBG[] = {IM_RGB(84, 48, 5),     IM_RGB(140, 81, 10),   IM_RGB(191, 129, 45),
                              IM_RGB(223, 194, 125), IM_RGB(246, 232, 195), IM_RGB(245, 245, 245),
                              IM_RGB(199, 234, 229), IM_RGB(128, 205, 193), IM_RGB(53, 151, 143),
                              IM_RGB(1, 102, 94),    IM_RGB(0, 60, 48)};
        const ImU32 PiYG[] = {IM_RGB(142, 1, 82),    IM_RGB(197, 27, 125),  IM_RGB(222, 119, 174),
                              IM_RGB(241, 182, 218), IM_RGB(253, 224, 239), IM_RGB(247, 247, 247),
                              IM_RGB(230, 245, 208), IM_RGB(184, 225, 134), IM_RGB(127, 188, 65),
                              IM_RGB(77, 146, 33),   IM_RGB(39, 100, 25)};
        const ImU32 Spectral[] = {IM_RGB(158, 1, 66),    IM_RGB(213, 62, 79),   IM_RGB(244, 109, 67),
                                  IM_RGB(253, 174, 97),  IM_RGB(254, 224, 139), IM_RGB(255, 255, 191),
                                  IM_RGB(230, 245, 152), IM_RGB(171, 221, 164), IM_RGB(102, 194, 165),
                                  IM_RGB(50, 136, 189),  IM_RGB(94, 79, 162)};
        const ImU32 Greys[] = {IM_COL32_WHITE, IM_COL32_BLACK};

        IMPLOT_APPEND_CMAP(Deep, true);
        IMPLOT_APPEND_CMAP(Dark, true);
        IMPLOT_APPEND_CMAP(Pastel, true);
        IMPLOT_APPEND_CMAP(Paired, true);
        IMPLOT_APPEND_CMAP(Viridis, false);
        IMPLOT_APPEND_CMAP(Plasma, false);
        IMPLOT_APPEND_CMAP(Hot, false);
        IMPLOT_APPEND_CMAP(Cool, false);
        IMPLOT_APPEND_CMAP(Pink, false);
        IMPLOT_APPEND_CMAP(Jet, false);
        IMPLOT_APPEND_CMAP(Twilight, false);
        IMPLOT_APPEND_CMAP(RdBu, false);
        IMPLOT_APPEND_CMAP(BrBG, false);
        IMPLOT_APPEND_CMAP(PiYG, false);
        IMPLOT_APPEND_CMAP(Spectral, false);
        IMPLOT_APPEND_CMAP(Greys, false);
    }

#undef IMPLOT_APPEND_CMAP
#undef IM_RGB

} // namespace ImPlot

#endif // IMPLOT_IMPLEMENTATION
