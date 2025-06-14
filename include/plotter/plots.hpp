#pragma once

#include "core.hpp"

namespace plotter {

    /// Plot a line through the given x and y data points.
    template <typename Numeric>
    bool plot(const std::vector<Numeric> &x, const std::vector<Numeric> &y,
              const std::map<std::string, std::string> &keywords = {});

    /// Plot a line with only y data (x will be 0, 1, 2, ...)
    template <typename Numeric>
    bool plot(const std::vector<Numeric> &y, const std::string &format = "",
              const std::map<std::string, std::string> &keywords = {});

    /// Plot a 3D surface
    template <typename Numeric>
    void plot_surface(const std::vector<::std::vector<Numeric>> &x, const std::vector<::std::vector<Numeric>> &y,
                      const std::vector<::std::vector<Numeric>> &z,
                      const std::map<std::string, std::string> &keywords = {});

    /// Create a contour plot
    template <typename Numeric>
    void contour(const std::vector<::std::vector<Numeric>> &x, const std::vector<::std::vector<Numeric>> &y,
                 const std::vector<::std::vector<Numeric>> &z, const std::map<std::string, std::string> &keywords = {});

    /// Create a spy plot (visualize sparsity pattern)
    template <typename Numeric>
    void spy(const std::vector<::std::vector<Numeric>> &x, const std::map<std::string, std::string> &keywords = {});

    /// Plot 3D lines
    template <typename Numeric>
    void plot3(const std::vector<Numeric> &x, const std::vector<Numeric> &y, const std::vector<Numeric> &z,
               const std::map<std::string, std::string> &keywords = {});

    /// Create a stem plot
    template <typename Numeric>
    bool stem(const std::vector<Numeric> &x, const std::vector<Numeric> &y,
              const std::map<std::string, std::string> &keywords = {});

    /// Fill area between curve and x-axis
    template <typename Numeric>
    bool fill(const std::vector<Numeric> &x, const std::vector<Numeric> &y,
              const std::map<std::string, std::string> &keywords = {});

    /// Fill area between two curves
    template <typename Numeric>
    bool fill_between(const std::vector<Numeric> &x, const std::vector<Numeric> &y1, const std::vector<Numeric> &y2,
                      const std::map<std::string, std::string> &keywords = {});

    /// Create an arrow
    template <typename Numeric>
    bool arrow(Numeric x, Numeric y, Numeric end_x, Numeric end_y, const std::string &fc = "r",
               const std::string &ec = "r", const double head_width = 1.0, const double head_length = 1.0);

    /// Create a histogram
    template <typename Numeric>
    bool hist(const std::vector<Numeric> &y, long bins = 10, std::string color = "b", double alpha = 1.0,
              bool cumulative = false);

    /// Semi-log plots
    template <typename Numeric>
    bool semilogx(const std::vector<Numeric> &x, const std::vector<Numeric> &y, const std::string &s = "");

    template <typename Numeric>
    bool semilogy(const std::vector<Numeric> &x, const std::vector<Numeric> &y, const std::string &s = "");

    template <typename Numeric>
    bool loglog(const std::vector<Numeric> &x, const std::vector<Numeric> &y, const std::string &s = "");

    /// Error bars
    template <typename Numeric>
    bool errorbar(const std::vector<Numeric> &x, const std::vector<Numeric> &y, const std::vector<Numeric> &yerr,
                  const std::map<std::string, std::string> &keywords = {});

} // namespace plotter
