#pragma once

#include "core.hpp"

namespace plotter {

    /// Create bar charts
    template <typename Numeric>
    bool bar(const std::vector<Numeric> &x, const std::vector<Numeric> &heights, std::string ec = "black",
             std::string ls = "-", double lw = 1.0, const std::map<std::string, std::string> &keywords = {});

    /// Create horizontal bar charts
    template <typename Numeric>
    bool barh(const std::vector<Numeric> &y, const std::vector<Numeric> &widths, std::string ec = "black",
              std::string ls = "-", double lw = 1.0, const std::map<std::string, std::string> &keywords = {});

    /// Create box plots
    template <typename Numeric>
    void boxplot(const std::vector<std::vector<Numeric>> &data, const std::vector<std::string> &labels = {},
                 const std::map<std::string, std::string> &keywords = {});

} // namespace plotter
