#pragma once

#include "../core/theme.hpp"
#include <pigment/pigment.hpp>

namespace plotter {

    class ThemeManager {
      private:
        Theme current_theme_;

      public:
        ThemeManager() : current_theme_(Theme::light()) {}

        void set_theme(const Theme &theme) { current_theme_ = theme; }

        void set_dark_theme() { set_theme(Theme::dark()); }

        void set_light_theme() { set_theme(Theme::light()); }

        void set_vibrant_theme() { set_theme(Theme::vibrant()); }

        const Theme &get_theme() const { return current_theme_; }

        // Palette management
        void set_palette(const pigment::Palette &palette) { current_theme_.plot_colors = palette; }

        void set_material_design_palette() { set_palette(pigment::Palette::material_design()); }

        void set_warm_palette() { set_palette(pigment::Palette::warm()); }

        void set_cool_palette() { set_palette(pigment::Palette::cool()); }

        void set_vibrant_palette(size_t count = 8) { set_palette(pigment::Palette::vibrant(count)); }

        Color get_background_color() const { return current_theme_.background; }

        Color get_border_color() const { return current_theme_.border_color; }

        Color get_next_plot_color(size_t index) const {
            if (current_theme_.plot_colors.size() == 0) {
                return pigment::colors::blue(); // fallback
            }
            return current_theme_.plot_colors[index % current_theme_.plot_colors.size()];
        }
    };

} // namespace plotter
