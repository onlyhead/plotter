#pragma once

#define STB_TRUETYPE_IMPLEMENTATION
#include "../core/types.hpp"
#include "../io/font.hpp"
#include <cmath>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace canvas {

    // Text rendering enums (use ones from plotter namespace)
    using TextAlign = plotter::TextAlign;
    using TextBaseline = plotter::TextBaseline;

    // Font weight options
    enum class FontWeight { NORMAL, BOLD };

    // Text style configuration
    struct TextStyle {
        double font_size = 12.0;
        plotter::Color color = {0, 0, 0, 255}; // Black by default
        FontWeight weight = FontWeight::NORMAL;
        TextAlign align = TextAlign::LEFT;
        TextBaseline baseline = TextBaseline::BOTTOM;
        double rotation = 0.0; // Rotation in degrees
    };

    // Font metrics
    struct FontMetrics {
        int ascent;
        int descent;
        int line_gap;
        double scale;
    };

    // Text bounding box
    struct TextBounds {
        double x, y, width, height;
    };

    class TextRenderer {
      private:
        struct FontData {
            std::unique_ptr<unsigned char[]> font_buffer;
            stbtt_fontinfo font_info;
            size_t buffer_size;
            bool is_valid = false;
        };

        std::map<std::string, FontData> loaded_fonts_;
        std::string default_font_name_;

        // Built-in font data (basic monospace font)
        static const unsigned char *get_default_font_data();
        static size_t get_default_font_size();

        // TrueType rendering helpers
        void render_truetype_text(std::vector<uint8_t> &canvas_data, int canvas_width, int canvas_height,
                                  const std::string &text, double x, double y, const TextStyle &style,
                                  FontData *font_data);

      public:
        TextRenderer();
        ~TextRenderer() = default;

        // Font management
        bool load_font(const std::string &font_name, const std::string &font_path);
        bool load_font_from_memory(const std::string &font_name, const unsigned char *data, size_t size);
        void set_default_font(const std::string &font_name);

        // Text measurement
        TextBounds measure_text(const std::string &text, const TextStyle &style, const std::string &font_name = "");
        FontMetrics get_font_metrics(const TextStyle &style, const std::string &font_name = "");

        // Text rendering to bitmap
        void render_text(std::vector<uint8_t> &canvas_data, int canvas_width, int canvas_height,
                         const std::string &text, double x, double y, const TextStyle &style,
                         const std::string &font_name = "");

        // Utility functions
        double text_width(const std::string &text, const TextStyle &style, const std::string &font_name = "");
        double text_height(const TextStyle &style, const std::string &font_name = "");

      private:
        FontData *get_font(const std::string &font_name);
        void render_char_to_canvas(std::vector<uint8_t> &canvas_data, int canvas_width, int canvas_height, int ch,
                                   double x, double y, const TextStyle &style, FontData *font);
        void blend_pixel(std::vector<uint8_t> &canvas_data, int canvas_width, int canvas_height, int x, int y,
                         const plotter::Color &color, uint8_t alpha);
    };

    // Default font implementation (simple 8x8 bitmap font)
    class DefaultFont {
      public:
        // Get bitmap for a character (returns 8x8 bitmap as uint64_t)
        static uint64_t get_char_bitmap(char c);

        // Render character to canvas using bitmap font
        static void render_char(std::vector<uint8_t> &canvas_data, int canvas_width, int canvas_height, char c, int x,
                                int y, const plotter::Color &color);

        // Constants
        static int char_width() { return 8; }
        static int char_height() { return 8; }
    };

    // ============================================================================
    // IMPLEMENTATION (Header-only)
    // ============================================================================

    // Default 8x8 bitmap font implementation
    inline uint64_t DefaultFont::get_char_bitmap(char c) {
        // Very simple 8x8 bitmap font - manually created patterns
        switch (c) {
        case 'A':
            return 0x18244242FF424200ULL;
        case 'B':
            return 0xFC42427C427E7C00ULL;
        case 'C':
            return 0x3C4240404040423CULL;
        case 'D':
            return 0x7844444444447800ULL;
        case 'E':
            return 0x7E40407C40407E00ULL;
        case 'F':
            return 0x7E40407C40404000ULL;
        case 'G':
            return 0x3C42404E4242423CULL;
        case 'H':
            return 0x424242FF42424200ULL;
        case 'I':
            return 0x3810101010103800ULL;
        case 'J':
            return 0x0808080808483000ULL;
        case 'K':
            return 0x4248507048444200ULL;
        case 'L':
            return 0x4040404040407E00ULL;
        case 'M':
            return 0x4266665A5A424200ULL;
        case 'N':
            return 0x4262525A4E424200ULL;
        case 'O':
            return 0x3C4242424242423CULL;
        case 'P':
            return 0x7C42427C40404000ULL;
        case 'Q':
            return 0x3C4242424A443A00ULL;
        case 'R':
            return 0x7C42427C44424200ULL;
        case 'S':
            return 0x3C42403C02423C00ULL;
        case 'T':
            return 0xFE10101010101000ULL;
        case 'U':
            return 0x4242424242423C00ULL;
        case 'V':
            return 0x4242424224181000ULL;
        case 'W':
            return 0x414141495555222CULL;
        case 'X':
            return 0x4224181824424200ULL;
        case 'Y':
            return 0x4242422418101000ULL;
        case 'Z':
            return 0x7E02040810207E00ULL;
        case 'a':
            return 0x003C023E42423E00ULL;
        case 'b':
            return 0x40407C424242BC00ULL;
        case 'c':
            return 0x003C4240404040FULL;
        case 'd':
            return 0x02023E424242BE00ULL;
        case 'e':
            return 0x003C427E40423C00ULL;
        case 'f':
            return 0x1C20207C20202000ULL;
        case 'g':
            return 0x003E42423E023C00ULL;
        case 'h':
            return 0x40407C424242424ULL;
        case 'i':
            return 0x1000301010103800ULL;
        case 'j':
            return 0x0800180808084800ULL;
        case 'k':
            return 0x4040444870484400ULL;
        case 'l':
            return 0x3010101010103800ULL;
        case 'm':
            return 0x00FC565656565600ULL;
        case 'n':
            return 0x005C624242424200ULL;
        case 'o':
            return 0x003C424242423C00ULL;
        case 'p':
            return 0x005C62627C404000ULL;
        case 'q':
            return 0x003E42423E020200ULL;
        case 'r':
            return 0x005C624040404000ULL;
        case 's':
            return 0x003E403C02027C00ULL;
        case 't':
            return 0x10107C1010101000ULL;
        case 'u':
            return 0x004242424242BE00ULL;
        case 'v':
            return 0x0042424224181000ULL;
        case 'w':
            return 0x0041495555222200ULL;
        case 'x':
            return 0x0042241818244200ULL;
        case 'y':
            return 0x0042423E02023C00ULL;
        case 'z':
            return 0x007E040810207E00ULL;
        case '0':
            return 0x3C4646525A623C00ULL;
        case '1':
            return 0x1030101010103800ULL;
        case '2':
            return 0x3C420204081020FCULL;
        case '3':
            return 0x3C42020C0202423CULL;
        case '4':
            return 0x0408182848FC0800ULL;
        case '5':
            return 0xFC40407C0202423CULL;
        case '6':
            return 0x3C42407C42423C00ULL;
        case '7':
            return 0x7E0204081020204ULL;
        case '8':
            return 0x3C42423C42423C00ULL;
        case '9':
            return 0x3C42423E02423C00ULL;
        case '!':
            return 0x1010101010001000ULL;
        case '?':
            return 0x3C42040810001000ULL;
        case '.':
            return 0x0000000000001800ULL;
        case ',':
            return 0x0000000000181000ULL;
        case ':':
            return 0x0000180000180000ULL;
        case ';':
            return 0x0000180000181000ULL;
        case '\'':
            return 0x1010000000000000ULL;
        case '"':
            return 0x2828000000000000ULL;
        case '-':
            return 0x0000007C00000000ULL;
        case '(':
            return 0x0C10202020100C00ULL;
        case ')':
            return 0x3008040404083000ULL;
        case ' ':
            return 0x0000000000000000ULL;
        default:
            return 0x3C4242424242423CULL; // Default to 'O' shape
        }
    }

    inline void DefaultFont::render_char(std::vector<uint8_t> &canvas_data, int canvas_width, int canvas_height, char c,
                                         int x, int y, const plotter::Color &color) {
        uint64_t bitmap = get_char_bitmap(c);

        for (int py = 0; py < 8; py++) {
            for (int px = 0; px < 8; px++) {
                // Use the same bit reading logic as in our debug function
                int bit_pos = py * 8 + px;
                bool bit_set = (bitmap >> (63 - bit_pos)) & 1;

                if (bit_set) {
                    int canvas_x = x + px;
                    int canvas_y = y + py;

                    if (canvas_x >= 0 && canvas_x < canvas_width && canvas_y >= 0 && canvas_y < canvas_height) {
                        int idx = (canvas_y * canvas_width + canvas_x) * 4;
                        if (idx + 3 < static_cast<int>(canvas_data.size())) {
                            canvas_data[idx] = color.r;
                            canvas_data[idx + 1] = color.g;
                            canvas_data[idx + 2] = color.b;
                            canvas_data[idx + 3] = color.a;
                        }
                    }
                }
            }
        }
    }

    // TextRenderer implementation
    inline const unsigned char *TextRenderer::get_default_font_data() {
        // Return null - we'll use the DefaultFont bitmap implementation
        return nullptr;
    }

    inline size_t TextRenderer::get_default_font_size() { return 0; }

    inline TextRenderer::TextRenderer() { default_font_name_ = "default"; }

    inline bool TextRenderer::load_font(const std::string &font_name, const std::string &font_path) {
        std::ifstream file(font_path, std::ios::binary | std::ios::ate);
        if (!file.is_open()) {
            return false;
        }

        size_t file_size = file.tellg();
        file.seekg(0, std::ios::beg);

        auto font_data = std::make_unique<unsigned char[]>(file_size);
        if (!file.read(reinterpret_cast<char *>(font_data.get()), file_size)) {
            return false;
        }

        return load_font_from_memory(font_name, font_data.get(), file_size);
    }

    inline bool TextRenderer::load_font_from_memory(const std::string &font_name, const unsigned char *data,
                                                    size_t size) {
        FontData font_data;
        font_data.font_buffer = std::make_unique<unsigned char[]>(size);
        font_data.buffer_size = size;

        // Copy the font data
        memcpy(font_data.font_buffer.get(), data, size);

        // Initialize stb_truetype font info
        if (stbtt_InitFont(&font_data.font_info, font_data.font_buffer.get(), 0) == 0) {
            return false;
        }

        font_data.is_valid = true;
        loaded_fonts_[font_name] = std::move(font_data);

        return true;
    }

    inline void TextRenderer::set_default_font(const std::string &font_name) { default_font_name_ = font_name; }

    inline TextBounds TextRenderer::measure_text(const std::string &text, const TextStyle &style,
                                                 const std::string &font_name) {
        std::string actual_font = font_name.empty() ? default_font_name_ : font_name;

        // Check if we have a TrueType font loaded
        auto it = loaded_fonts_.find(actual_font);
        if (it != loaded_fonts_.end() && it->second.is_valid) {
            float scale = stbtt_ScaleForPixelHeight(&it->second.font_info, static_cast<float>(style.font_size));

            int ascent, descent, line_gap;
            stbtt_GetFontVMetrics(&it->second.font_info, &ascent, &descent, &line_gap);

            double height = (ascent - descent) * scale;
            double width = 0;

            for (char c : text) {
                int advance, left_bearing;
                stbtt_GetCodepointHMetrics(&it->second.font_info, c, &advance, &left_bearing);
                width += advance * scale;
            }

            return {0, 0, width, height};
        }

        // Fallback to bitmap font
        double width = text.length() * DefaultFont::char_width();
        double height = DefaultFont::char_height();
        return {0, 0, width, height};
    }

    inline FontMetrics TextRenderer::get_font_metrics(const TextStyle &style, const std::string &font_name) {
        std::string actual_font = font_name.empty() ? default_font_name_ : font_name;

        // Check if we have a TrueType font loaded
        auto it = loaded_fonts_.find(actual_font);
        if (it != loaded_fonts_.end() && it->second.is_valid) {
            float scale = stbtt_ScaleForPixelHeight(&it->second.font_info, static_cast<float>(style.font_size));

            int ascent, descent, line_gap;
            stbtt_GetFontVMetrics(&it->second.font_info, &ascent, &descent, &line_gap);

            return {
                static_cast<int>((ascent - descent) * scale), // height
                static_cast<int>(descent * scale),            // baseline
                static_cast<int>(line_gap * scale),           // line_gap
                static_cast<double>(scale)                    // scale_factor
            };
        }

        // Fallback to bitmap font
        return {DefaultFont::char_height(), 0, 2, 1.0};
    }

    inline void TextRenderer::render_text(std::vector<uint8_t> &canvas_data, int canvas_width, int canvas_height,
                                          const std::string &text, double x, double y, const TextStyle &style,
                                          const std::string &font_name) {
        std::string actual_font = font_name.empty() ? default_font_name_ : font_name;

        // Check if we have a TrueType font loaded
        auto it = loaded_fonts_.find(actual_font);
        if (it != loaded_fonts_.end() && it->second.is_valid) {
            render_truetype_text(canvas_data, canvas_width, canvas_height, text, x, y, style, &it->second);
            return;
        }

        // Fallback to bitmap font rendering
        double current_x = x;

        // Apply alignment
        if (style.align != TextAlign::LEFT) {
            double text_width = text.length() * DefaultFont::char_width();
            if (style.align == TextAlign::CENTER) {
                current_x -= text_width / 2.0;
            } else if (style.align == TextAlign::RIGHT) {
                current_x -= text_width;
            }
        }

        // Apply baseline
        double render_y = y;
        if (style.baseline == TextBaseline::MIDDLE) {
            render_y -= DefaultFont::char_height() / 2.0;
        } else if (style.baseline == TextBaseline::TOP) {
            render_y -= DefaultFont::char_height();
        }

        // Render each character
        for (char c : text) {
            DefaultFont::render_char(canvas_data, canvas_width, canvas_height, c, static_cast<int>(current_x),
                                     static_cast<int>(render_y), style.color);
            current_x += DefaultFont::char_width();
        }
    }

    inline double TextRenderer::text_width(const std::string &text, const TextStyle &style,
                                           const std::string &font_name) {
        std::string actual_font = font_name.empty() ? default_font_name_ : font_name;

        // Check if we have a TrueType font loaded
        auto it = loaded_fonts_.find(actual_font);
        if (it != loaded_fonts_.end() && it->second.is_valid) {
            float scale = stbtt_ScaleForPixelHeight(&it->second.font_info, static_cast<float>(style.font_size));

            double width = 0;
            for (char c : text) {
                int advance, left_bearing;
                stbtt_GetCodepointHMetrics(&it->second.font_info, c, &advance, &left_bearing);
                width += advance * scale;
            }
            return width;
        }

        // Fallback to bitmap font
        return text.length() * DefaultFont::char_width();
    }

    inline double TextRenderer::text_height(const TextStyle &style, const std::string &font_name) {
        std::string actual_font = font_name.empty() ? default_font_name_ : font_name;

        // Check if we have a TrueType font loaded
        auto it = loaded_fonts_.find(actual_font);
        if (it != loaded_fonts_.end() && it->second.is_valid) {
            float scale = stbtt_ScaleForPixelHeight(&it->second.font_info, static_cast<float>(style.font_size));

            int ascent, descent;
            stbtt_GetFontVMetrics(&it->second.font_info, &ascent, &descent, nullptr);
            return (ascent - descent) * scale;
        }

        // Fallback to bitmap font
        return DefaultFont::char_height();
    }

    inline TextRenderer::FontData *TextRenderer::get_font(const std::string &font_name) {
        return nullptr; // Use bitmap font for now
    }

    inline void TextRenderer::render_truetype_text(std::vector<uint8_t> &canvas_data, int canvas_width,
                                                   int canvas_height, const std::string &text, double x, double y,
                                                   const TextStyle &style, FontData *font_data) {
        float scale = stbtt_ScaleForPixelHeight(&font_data->font_info, static_cast<float>(style.font_size));

        int ascent, descent;
        stbtt_GetFontVMetrics(&font_data->font_info, &ascent, &descent, nullptr);

        double current_x = x;
        double baseline_y = y;

        // Apply baseline adjustment
        if (style.baseline == TextBaseline::TOP) {
            baseline_y += ascent * scale;
        } else if (style.baseline == TextBaseline::MIDDLE) {
            baseline_y += (ascent - descent) * scale * 0.5;
        }

        // Apply alignment
        if (style.align != TextAlign::LEFT) {
            double text_width = 0;
            for (char c : text) {
                int advance, left_bearing;
                stbtt_GetCodepointHMetrics(&font_data->font_info, c, &advance, &left_bearing);
                text_width += advance * scale;
            }

            if (style.align == TextAlign::CENTER) {
                current_x -= text_width / 2.0;
            } else if (style.align == TextAlign::RIGHT) {
                current_x -= text_width;
            }
        }

        // Render each character
        for (char c : text) {
            render_char_to_canvas(canvas_data, canvas_width, canvas_height, c, current_x, baseline_y, style, font_data);

            int advance, left_bearing;
            stbtt_GetCodepointHMetrics(&font_data->font_info, c, &advance, &left_bearing);
            current_x += advance * scale;
        }
    }

    inline void TextRenderer::render_char_to_canvas(std::vector<uint8_t> &canvas_data, int canvas_width,
                                                    int canvas_height, int ch, double x, double y,
                                                    const TextStyle &style, FontData *font_data) {
        float scale = stbtt_ScaleForPixelHeight(&font_data->font_info, static_cast<float>(style.font_size));

        int width, height, xoff, yoff;
        unsigned char *bitmap =
            stbtt_GetCodepointBitmap(&font_data->font_info, 0, scale, ch, &width, &height, &xoff, &yoff);

        if (bitmap) {
            int render_x = static_cast<int>(x) + xoff;
            int render_y = static_cast<int>(y) + yoff;

            for (int py = 0; py < height; py++) {
                for (int px = 0; px < width; px++) {
                    int pixel_x = render_x + px;
                    int pixel_y = render_y + py;

                    if (pixel_x >= 0 && pixel_x < canvas_width && pixel_y >= 0 && pixel_y < canvas_height) {
                        uint8_t alpha = bitmap[py * width + px];
                        if (alpha > 0) {
                            blend_pixel(canvas_data, canvas_width, canvas_height, pixel_x, pixel_y, style.color, alpha);
                        }
                    }
                }
            }

            stbtt_FreeBitmap(bitmap, nullptr);
        }
    }

    inline void TextRenderer::blend_pixel(std::vector<uint8_t> &canvas_data, int canvas_width, int canvas_height, int x,
                                          int y, const plotter::Color &color, uint8_t alpha) {
        if (x >= 0 && x < canvas_width && y >= 0 && y < canvas_height) {
            int idx = (y * canvas_width + x) * 4;
            if (idx + 3 < static_cast<int>(canvas_data.size())) {
                // Simple alpha blending
                float a = alpha / 255.0f;
                canvas_data[idx] = static_cast<uint8_t>(canvas_data[idx] * (1 - a) + color.r * a);
                canvas_data[idx + 1] = static_cast<uint8_t>(canvas_data[idx + 1] * (1 - a) + color.g * a);
                canvas_data[idx + 2] = static_cast<uint8_t>(canvas_data[idx + 2] * (1 - a) + color.b * a);
                canvas_data[idx + 3] = 255; // Keep opaque
            }
        }
    }

} // namespace canvas
