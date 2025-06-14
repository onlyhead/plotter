#pragma once

#include "core.hpp"

namespace plotter {

/// Display image data
#ifndef WITHOUT_NUMPY
    void imshow(const unsigned char *ptr, const int rows, const int columns, const int colors,
                const std::map<std::string, std::string> &keywords = {}, PyObject **out = nullptr);

    void imshow(const float *ptr, const int rows, const int columns, const int colors,
                const std::map<std::string, std::string> &keywords = {}, PyObject **out = nullptr);

#ifdef WITH_OPENCV
    void imshow(const cv::Mat &image, const std::map<std::string, std::string> &keywords = {});
#endif

    template <typename Numeric>
    void imshow(const std::vector<std::vector<Numeric>> &image,
                const std::map<std::string, std::string> &keywords = {});
#endif

    /// Quiver plot (vector field visualization)
    template <typename Numeric>
    bool quiver(const std::vector<Numeric> &x, const std::vector<Numeric> &y, const std::vector<Numeric> &u,
                const std::vector<Numeric> &v, const std::map<std::string, std::string> &keywords = {});

} // namespace plotter
