#pragma once

#include "core.hpp"

namespace plotter {

    /// Create a scatter plot
    template <typename NumericX, typename NumericY>
    bool scatter(const std::vector<NumericX> &x, const std::vector<NumericY> &y,
                 const std::map<std::string, std::string> &keywords = {});

    /// Create a colored scatter plot
    template <typename NumericX, typename NumericY, typename NumericC>
    bool scatter_colored(const std::vector<NumericX> &x, const std::vector<NumericY> &y, const std::vector<NumericC> &c,
                         const std::map<std::string, std::string> &keywords = {});

    /// Create a 3D scatter plot
    template <typename NumericX, typename NumericY, typename NumericZ>
    bool scatter(const std::vector<NumericX> &x, const std::vector<NumericY> &y, const std::vector<NumericZ> &z,
                 const std::map<std::string, std::string> &keywords = {});

} // namespace plotter
