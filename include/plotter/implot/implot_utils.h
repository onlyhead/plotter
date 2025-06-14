#pragma once

#include "implot_defines.h"
#include "implot_types.h"

namespace ImPlot {

    //-----------------------------------------------------------------------------
    // Utility Functions
    //-----------------------------------------------------------------------------

    // Adds vertical text to a draw list
    IMPLOT_API void AddTextVertical(ImDrawList *DrawList, ImVec2 pos, ImU32 col, const char *text_begin,
                                    const char *text_end = nullptr);

    // Adds centered text to a draw list
    IMPLOT_API void AddTextCentered(ImDrawList *DrawList, ImVec2 top_center, ImU32 col, const char *text_begin,
                                    const char *text_end = nullptr);

    // Calculate a nice number for axis labeling
    IMPLOT_API double NiceNum(double x, bool round);

    // Get plot utils
    IMPLOT_API ImPlotPlot *GetPlot(const char *title);
    IMPLOT_API ImPlotPlot *GetCurrentPlot();
    IMPLOT_API void BustPlotCache();

    // Legend utils
    IMPLOT_API ImVec2 GetLocationPos(const ImRect &outer_rect, const ImVec2 &inner_size, ImPlotLocation loc,
                                     const ImVec2 &pad);
    IMPLOT_API ImVec2 CalcLegendSize(ImPlotItemGroup &items, const ImVec2 &pad, const ImVec2 &spacing, bool vertical);
    IMPLOT_API bool ClampLegendRect(ImRect &legend_rect, const ImRect &outer_rect, const ImVec2 &pad);

} // namespace ImPlot

//-----------------------------------------------------------------------------
// IMPLEMENTATION
//-----------------------------------------------------------------------------

#ifdef IMPLOT_IMPLEMENTATION

namespace ImPlot {

    inline void AddTextVertical(ImDrawList *DrawList, ImVec2 pos, ImU32 col, const char *text_begin,
                                const char *text_end) {
        // the code below is based loosely on ImFont::RenderText
        if (!text_end)
            text_end = text_begin + strlen(text_begin);
        ImGuiContext &g = *GImGui;
#ifdef IMGUI_HAS_TEXTURES
        ImFontBaked *font = g.Font->GetFontBaked(g.FontSize);
        const float scale = g.FontSize / font->Size;
#else
        ImFont *font = g.Font;
        const float scale = g.FontSize / font->FontSize;
#endif
        // Align to be pixel perfect
        pos.x = ImFloor(pos.x);
        pos.y = ImFloor(pos.y);
        const char *s = text_begin;
        int chars_exp = (int)(text_end - s);
        int chars_rnd = 0;
        const int vtx_count_max = chars_exp * 4;
        const int idx_count_max = chars_exp * 6;
        DrawList->PrimReserve(idx_count_max, vtx_count_max);
        while (s < text_end) {
            unsigned int c = (unsigned int)*s;
            if (c < 0x80) {
                s += 1;
            } else {
                s += ImTextCharFromUtf8(&c, s, text_end);
                if (c == 0) // Malformed UTF-8?
                    break;
            }
            const ImFontGlyph *glyph = font->FindGlyph((ImWchar)c);
            if (glyph == nullptr) {
                continue;
            }
            DrawList->PrimQuadUV(
                pos + ImVec2(glyph->Y0, -glyph->X0) * scale, pos + ImVec2(glyph->Y0, -glyph->X1) * scale,
                pos + ImVec2(glyph->Y1, -glyph->X1) * scale, pos + ImVec2(glyph->Y1, -glyph->X0) * scale,
                ImVec2(glyph->U0, glyph->V0), ImVec2(glyph->U1, glyph->V0), ImVec2(glyph->U1, glyph->V1),
                ImVec2(glyph->U0, glyph->V1), col);
            pos.y -= glyph->AdvanceX * scale;
            chars_rnd++;
        }
        // Give back unused vertices
        int chars_skp = chars_exp - chars_rnd;
        DrawList->PrimUnreserve(chars_skp * 6, chars_skp * 4);
    }

    inline void AddTextCentered(ImDrawList *DrawList, ImVec2 top_center, ImU32 col, const char *text_begin,
                                const char *text_end) {
        float txt_ht = ImGui::GetTextLineHeight();
        const char *title_end = ImGui::FindRenderedTextEnd(text_begin, text_end);
        ImVec2 text_size;
        float y = 0;
        while (const char *tmp = (const char *)memchr(text_begin, '\n', title_end - text_begin)) {
            text_size = ImGui::CalcTextSize(text_begin, tmp, true);
            DrawList->AddText(ImVec2(top_center.x - text_size.x * 0.5f, top_center.y + y), col, text_begin, tmp);
            text_begin = tmp + 1;
            y += txt_ht;
        }
        text_size = ImGui::CalcTextSize(text_begin, title_end, true);
        DrawList->AddText(ImVec2(top_center.x - text_size.x * 0.5f, top_center.y + y), col, text_begin, title_end);
    }

    inline double NiceNum(double x, bool round) {
        double f;
        double nf;
        int expv = (int)floor(ImLog10(x));
        f = x / ImPow(10.0, (double)expv);
        if (round)
            if (f < 1.5)
                nf = 1;
            else if (f < 3)
                nf = 2;
            else if (f < 7)
                nf = 5;
            else
                nf = 10;
        else if (f <= 1)
            nf = 1;
        else if (f <= 2)
            nf = 2;
        else if (f <= 5)
            nf = 5;
        else
            nf = 10;
        return nf * ImPow(10.0, expv);
    }

    inline ImPlotPlot *GetPlot(const char *title) {
        ImGuiWindow *Window = GImGui->CurrentWindow;
        const ImGuiID ID = Window->GetID(title);
        return GImPlot->Plots.GetByKey(ID);
    }

    inline ImPlotPlot *GetCurrentPlot() { return GImPlot->CurrentPlot; }

    inline void BustPlotCache() {
        ImPlotContext &gp = *GImPlot;
        gp.Plots.Clear();
        gp.Subplots.Clear();
    }

    inline ImVec2 GetLocationPos(const ImRect &outer_rect, const ImVec2 &inner_size, ImPlotLocation loc,
                                 const ImVec2 &pad) {
        ImVec2 pos;
        if (ImHasFlag(loc, ImPlotLocation_West) && !ImHasFlag(loc, ImPlotLocation_East))
            pos.x = outer_rect.Min.x + pad.x;
        else if (!ImHasFlag(loc, ImPlotLocation_West) && ImHasFlag(loc, ImPlotLocation_East))
            pos.x = outer_rect.Max.x - pad.x - inner_size.x;
        else
            pos.x = outer_rect.GetCenter().x - inner_size.x * 0.5f;
        // legend reference point y
        if (ImHasFlag(loc, ImPlotLocation_North) && !ImHasFlag(loc, ImPlotLocation_South))
            pos.y = outer_rect.Min.y + pad.y;
        else if (!ImHasFlag(loc, ImPlotLocation_North) && ImHasFlag(loc, ImPlotLocation_South))
            pos.y = outer_rect.Max.y - pad.y - inner_size.y;
        else
            pos.y = outer_rect.GetCenter().y - inner_size.y * 0.5f;
        pos.x = IM_ROUND(pos.x);
        pos.y = IM_ROUND(pos.y);
        return pos;
    }

    inline ImVec2 CalcLegendSize(ImPlotItemGroup &items, const ImVec2 &pad, const ImVec2 &spacing, bool vertical) {
        // vars
        const int nItems = items.GetLegendCount();
        const float txt_ht = ImGui::GetTextLineHeight();
        const float icon_size = txt_ht;
        // get label max width
        float max_label_width = 0;
        float sum_label_width = 0;
        for (int i = 0; i < nItems; ++i) {
            const char *label = items.GetLegendLabel(i);
            const float label_width = ImGui::CalcTextSize(label, nullptr, true).x;
            max_label_width = label_width > max_label_width ? label_width : max_label_width;
            sum_label_width += label_width;
        }
        // calc legend size
        const ImVec2 legend_size =
            vertical ? ImVec2(pad.x * 2 + icon_size + max_label_width,
                              pad.y * 2 + nItems * txt_ht + (nItems - 1) * spacing.y)
                     : ImVec2(pad.x * 2 + icon_size * nItems + sum_label_width + (nItems - 1) * spacing.x,
                              pad.y * 2 + txt_ht);
        return legend_size;
    }

    inline bool ClampLegendRect(ImRect &legend_rect, const ImRect &outer_rect, const ImVec2 &pad) {
        bool clamped = false;
        ImRect outer_rect_pad(outer_rect.Min + pad, outer_rect.Max - pad);
        if (legend_rect.Min.x < outer_rect_pad.Min.x) {
            legend_rect.Max.x = outer_rect_pad.Min.x + legend_rect.GetWidth();
            legend_rect.Min.x = outer_rect_pad.Min.x;
            clamped = true;
        }
        if (legend_rect.Max.x > outer_rect_pad.Max.x) {
            legend_rect.Min.x = outer_rect_pad.Max.x - legend_rect.GetWidth();
            legend_rect.Max.x = outer_rect_pad.Max.x;
            clamped = true;
        }
        if (legend_rect.Min.y < outer_rect_pad.Min.y) {
            legend_rect.Max.y = outer_rect_pad.Min.y + legend_rect.GetHeight();
            legend_rect.Min.y = outer_rect_pad.Min.y;
            clamped = true;
        }
        if (legend_rect.Max.y > outer_rect_pad.Max.y) {
            legend_rect.Min.y = outer_rect_pad.Max.y - legend_rect.GetHeight();
            legend_rect.Max.y = outer_rect_pad.Max.y;
            clamped = true;
        }
        return clamped;
    }

} // namespace ImPlot

#endif // IMPLOT_IMPLEMENTATION
