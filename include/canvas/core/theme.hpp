#pragma once

#include "types.hpp"
#include <pigment/named_colors.hpp>
#include <pigment/pigment.hpp>

namespace plotter {

    // Theme definitions
    struct Theme {
        Color background;
        Color grid_color;
        Color text_color;
        Color border_color;
        pigment::Palette plot_colors;

        // Predefined themes using Pigment named colors and palettes
        static Theme light() {
            return {
                pigment::colors::white(),           // white background
                pigment::colors::lightgray(),       // light gray grid
                pigment::colors::black(),           // black text
                pigment::colors::silver(),          // silver border
                pigment::Palette::material_design() // material design palette
            };
        }

        static Theme dark() {
            return {
                pigment::colors::darkslategray(), // dark gray background
                pigment::colors::dimgray(),       // medium gray grid
                pigment::colors::white(),         // white text
                pigment::colors::gray(),          // gray border
                pigment::Palette::cool()          // cool color palette for dark theme
            };
        }

        static Theme vibrant() {
            return {
                pigment::colors::black(),    // black background
                pigment::colors::darkgray(), // dark gray grid
                pigment::colors::white(),    // white text
                pigment::colors::silver(),   // silver border
                pigment::Palette::vibrant(6) // vibrant colors
            };
        }
    };

} // namespace plotter
