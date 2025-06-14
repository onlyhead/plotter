#pragma once

#include "core.hpp"

namespace plotter {

    /// Create subplots
    inline void subplot(long nrows, long ncols, long plot_number);

    /// Create subplot with grid specification
    template <typename Numeric>
    void subplot2grid(const std::pair<Numeric, Numeric> &shape, const std::pair<Numeric, Numeric> &loc,
                      const std::pair<Numeric, Numeric> &rowspan_colspan = std::make_pair(1, 1));

    /// Set axis limits
    template <typename Numeric> void xlim(Numeric left, Numeric right);

    template <typename Numeric> void ylim(Numeric left, Numeric right);

    /// Get axis limits
    inline std::array<double, 2> xlim();
    inline std::array<double, 2> ylim();

    /// Set axis labels
    inline void xlabel(const std::string &str, const std::map<std::string, std::string> &keywords = {});
    inline void ylabel(const std::string &str, const std::map<std::string, std::string> &keywords = {});

    /// Set plot title
    inline void title(const std::string &titlestr, const std::map<std::string, std::string> &keywords = {});

    /// Set super title
    inline void suptitle(const std::string &suptitlestr, const std::map<std::string, std::string> &keywords = {});

    /// Add legend
    inline void legend();
    inline void legend(const std::map<std::string, std::string> &keywords);

    /// Set axis properties
    inline void axis(const std::string &axisstr);

    /// Set tick parameters
    inline void tick_params(const std::map<std::string, std::string> &keywords);

    /// Set ticks
    template <typename Numeric>
    void xticks(const std::vector<Numeric> &ticks, const std::vector<std::string> &labels = {},
                const std::map<std::string, std::string> &keywords = {});

    template <typename Numeric>
    void yticks(const std::vector<Numeric> &ticks, const std::vector<std::string> &labels = {},
                const std::map<std::string, std::string> &keywords = {});

    /// Set margins
    template <typename Numeric> void margins(Numeric margin);

    template <typename Numeric> void margins(Numeric mx, Numeric my);

    /// Add grid
    inline void grid(bool flag, const std::map<std::string, std::string> &keywords = {});

    /// Add horizontal/vertical lines
    template <typename Numeric> void axhline(Numeric y, const std::map<std::string, std::string> &keywords = {});

    template <typename Numeric> void axvline(Numeric x, const std::map<std::string, std::string> &keywords = {});

    /// Add vertical span
    template <typename Numeric>
    void axvspan(Numeric xmin, Numeric xmax, const std::map<std::string, std::string> &keywords = {});

    /// Add text
    template <typename Numeric>
    void text(Numeric x, Numeric y, const std::string &s, const std::map<std::string, std::string> &keywords = {});

    /// Get current axes
    inline long gca();

    /// Get mouse input
    inline std::vector<std::array<double, 2>> ginput(const int numClicks = 1,
                                                     const std::map<std::string, std::string> &keywords = {});

} // namespace plotter
