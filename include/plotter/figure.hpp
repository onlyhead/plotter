#pragma once

#include "core.hpp"

namespace plotter {

    /// Display the plot
    inline void show(bool block = true);

    /// Save the plot to file
    inline void save(const std::string &filename, int dpi = 100);

    /// Create a new figure
    inline long figure(long number = -1);

    /// Check if figure exists
    inline bool fignum_exists(long number);

    /// Clear the current figure
    inline void clf();

    /// Clear the current axes
    inline void cla();

    /// Close figure(s)
    inline void close();
    inline void close(long fignum);

    /// Enable interactive mode
    inline void ion();

    /// Disable interactive mode
    inline void ioff();

    /// Draw and update the plot
    inline void draw();

    /// Pause execution
    inline void pause(double interval);

    /// Enable xkcd style
    inline void xkcd();

    /// Tight layout
    inline void tight_layout();

    /// Adjust subplot parameters
    inline void subplots_adjust(const std::map<std::string, std::string> &keywords = {});

} // namespace plotter
