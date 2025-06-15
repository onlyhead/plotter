#pragma once

#include "core.hpp"

namespace plotter {

/// Display image data
#ifndef WITHOUT_NUMPY
    void imshow(const unsigned char *ptr, const int rows, const int columns, const int colors,
                const std::map<std::string, std::string> &keywords = {}, PyObject **out = nullptr);

    void imshow(const float *ptr, const int rows, const int columns, const int colors,
                const std::map<std::string, std::string> &keywords = {}, PyObject **out = nullptr);

    template <typename Numeric>
    void imshow(const std::vector<std::vector<Numeric>> &image,
                const std::map<std::string, std::string> &keywords = {});
#endif

    /// Quiver plot (vector field visualization)
    template <typename Numeric>
    bool quiver(const std::vector<Numeric> &x, const std::vector<Numeric> &y, const std::vector<Numeric> &u,
                const std::vector<Numeric> &v, const std::map<std::string, std::string> &keywords = {});

} // namespace plotter

// ============ IMPLEMENTATIONS ============

namespace plotter {

#ifndef WITHOUT_NUMPY
    /// Implementation for unsigned char imshow
    inline void imshow(const unsigned char *ptr, const int rows, const int columns, const int colors,
                const std::map<std::string, std::string> &keywords, PyObject **out) {
        detail::_interpreter::get();

        // Create numpy array from data
        npy_intp dims[3] = {rows, columns, colors};
        int nd = (colors == 1) ? 2 : 3;
        
        PyObject *array = PyArray_SimpleNewFromData(nd, dims, NPY_UINT8, (void*)ptr);
        if (!array) {
            throw std::runtime_error("Failed to create numpy array for imshow");
        }

        // Create arguments
        PyObject *args = PyTuple_New(1);
        PyTuple_SetItem(args, 0, array);

        // Create keyword arguments
        PyObject *kwargs = PyDict_New();
        for (const auto &kw : keywords) {
            PyDict_SetItemString(kwargs, kw.first.c_str(), PyString_FromString(kw.second.c_str()));
        }

        // Call imshow
        PyObject *res = PyObject_Call(detail::_interpreter::get().s_python_function_imshow, args, kwargs);
        
        if (!res) {
            Py_DECREF(args);
            Py_DECREF(kwargs);
            throw std::runtime_error("Call to imshow() failed.");
        }

        if (out) {
            *out = res;
        } else {
            Py_DECREF(res);
        }
        
        Py_DECREF(args);
        Py_DECREF(kwargs);
    }

    /// Implementation for float imshow
    inline void imshow(const float *ptr, const int rows, const int columns, const int colors,
                const std::map<std::string, std::string> &keywords, PyObject **out) {
        detail::_interpreter::get();

        // Create numpy array from data
        npy_intp dims[3] = {rows, columns, colors};
        int nd = (colors == 1) ? 2 : 3;
        
        PyObject *array = PyArray_SimpleNewFromData(nd, dims, NPY_FLOAT32, (void*)ptr);
        if (!array) {
            throw std::runtime_error("Failed to create numpy array for imshow");
        }

        // Create arguments
        PyObject *args = PyTuple_New(1);
        PyTuple_SetItem(args, 0, array);

        // Create keyword arguments
        PyObject *kwargs = PyDict_New();
        for (const auto &kw : keywords) {
            PyDict_SetItemString(kwargs, kw.first.c_str(), PyString_FromString(kw.second.c_str()));
        }

        // Call imshow
        PyObject *res = PyObject_Call(detail::_interpreter::get().s_python_function_imshow, args, kwargs);
        
        if (!res) {
            Py_DECREF(args);
            Py_DECREF(kwargs);
            throw std::runtime_error("Call to imshow() failed.");
        }

        if (out) {
            *out = res;
        } else {
            Py_DECREF(res);
        }
        
        Py_DECREF(args);
        Py_DECREF(kwargs);
    }

    /// Implementation for vector<vector<Numeric>> imshow
    template <typename Numeric>
    void imshow(const std::vector<std::vector<Numeric>> &image,
                const std::map<std::string, std::string> &keywords) {
        if (image.empty() || image[0].empty()) {
            throw std::runtime_error("imshow: empty image data");
        }

        detail::_interpreter::get();

        int rows = static_cast<int>(image.size());
        int cols = static_cast<int>(image[0].size());

        // Convert to flat array
        std::vector<Numeric> flat_data;
        flat_data.reserve(rows * cols);
        
        for (const auto &row : image) {
            if (static_cast<int>(row.size()) != cols) {
                throw std::runtime_error("imshow: inconsistent row sizes");
            }
            flat_data.insert(flat_data.end(), row.begin(), row.end());
        }

        // Create numpy array
        PyObject *array = detail::get_2darray(flat_data, rows, cols);
        if (!array) {
            throw std::runtime_error("Failed to create numpy array for imshow");
        }

        // Create arguments
        PyObject *args = PyTuple_New(1);
        PyTuple_SetItem(args, 0, array);

        // Create keyword arguments
        PyObject *kwargs = PyDict_New();
        for (const auto &kw : keywords) {
            PyDict_SetItemString(kwargs, kw.first.c_str(), PyString_FromString(kw.second.c_str()));
        }

        // Call imshow
        PyObject *res = PyObject_Call(detail::_interpreter::get().s_python_function_imshow, args, kwargs);
        
        if (!res) {
            Py_DECREF(args);
            Py_DECREF(kwargs);
            throw std::runtime_error("Call to imshow() failed.");
        }

        Py_DECREF(res);
        Py_DECREF(args);
        Py_DECREF(kwargs);
    }
#endif

    /// Implementation for quiver plot
    template <typename Numeric>
    bool quiver(const std::vector<Numeric> &x, const std::vector<Numeric> &y, const std::vector<Numeric> &u,
                const std::vector<Numeric> &v, const std::map<std::string, std::string> &keywords) {
        if (x.size() != y.size() || x.size() != u.size() || x.size() != v.size()) {
            throw std::runtime_error("quiver: all input vectors must have the same size");
        }

        detail::_interpreter::get();

        PyObject *xarray = detail::get_array(x);
        PyObject *yarray = detail::get_array(y);
        PyObject *uarray = detail::get_array(u);
        PyObject *varray = detail::get_array(v);

        // Create arguments
        PyObject *args = PyTuple_New(4);
        PyTuple_SetItem(args, 0, xarray);
        PyTuple_SetItem(args, 1, yarray);
        PyTuple_SetItem(args, 2, uarray);
        PyTuple_SetItem(args, 3, varray);

        // Create keyword arguments
        PyObject *kwargs = PyDict_New();
        for (const auto &kw : keywords) {
            PyDict_SetItemString(kwargs, kw.first.c_str(), PyString_FromString(kw.second.c_str()));
        }

        PyObject *res = PyObject_Call(detail::_interpreter::get().s_python_function_quiver, args, kwargs);

        Py_DECREF(args);
        Py_DECREF(kwargs);
        if (res)
            Py_DECREF(res);

        return res;
    }

}
