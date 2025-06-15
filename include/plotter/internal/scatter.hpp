#pragma once

#include "core.hpp"
#include <cassert>

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

// ============ IMPLEMENTATIONS ============

namespace plotter {

    /// Create a scatter plot - implementation
    template <typename NumericX, typename NumericY>
    bool scatter(const std::vector<NumericX> &x, const std::vector<NumericY> &y,
                 const std::map<std::string, std::string> &keywords) {
        assert(x.size() == y.size());

        detail::_interpreter::get();

        PyObject *xarray = detail::get_array(x);
        PyObject *yarray = detail::get_array(y);

        // construct positional args
        PyObject *args = PyTuple_New(2);
        PyTuple_SetItem(args, 0, xarray);
        PyTuple_SetItem(args, 1, yarray);

        // construct keyword args
        PyObject *kwargs = PyDict_New();
        for (const auto &kw : keywords) {
            PyDict_SetItemString(kwargs, kw.first.c_str(), PyString_FromString(kw.second.c_str()));
        }

        PyObject *res = PyObject_Call(detail::_interpreter::get().s_python_function_scatter, args, kwargs);

        Py_DECREF(args);
        Py_DECREF(kwargs);
        if (res)
            Py_DECREF(res);

        return res;
    }

    /// Create a colored scatter plot - implementation
    template <typename NumericX, typename NumericY, typename NumericC>
    bool scatter_colored(const std::vector<NumericX> &x, const std::vector<NumericY> &y, const std::vector<NumericC> &c,
                         const std::map<std::string, std::string> &keywords) {
        assert(x.size() == y.size() && x.size() == c.size());

        detail::_interpreter::get();

        PyObject *xarray = detail::get_array(x);
        PyObject *yarray = detail::get_array(y);
        PyObject *carray = detail::get_array(c);

        // construct positional args
        PyObject *args = PyTuple_New(3);
        PyTuple_SetItem(args, 0, xarray);
        PyTuple_SetItem(args, 1, yarray);
        PyTuple_SetItem(args, 2, carray);

        // construct keyword args
        PyObject *kwargs = PyDict_New();
        for (const auto &kw : keywords) {
            PyDict_SetItemString(kwargs, kw.first.c_str(), PyString_FromString(kw.second.c_str()));
        }

        PyObject *res = PyObject_Call(detail::_interpreter::get().s_python_function_scatter, args, kwargs);

        Py_DECREF(args);
        Py_DECREF(kwargs);
        if (res)
            Py_DECREF(res);

        return res;
    }

    /// Create a 3D scatter plot - implementation
    template <typename NumericX, typename NumericY, typename NumericZ>
    bool scatter(const std::vector<NumericX> &x, const std::vector<NumericY> &y, const std::vector<NumericZ> &z,
                 const std::map<std::string, std::string> &keywords) {
        assert(x.size() == y.size() && x.size() == z.size());

        detail::_interpreter::get();

        PyObject *xarray = detail::get_array(x);
        PyObject *yarray = detail::get_array(y);
        PyObject *zarray = detail::get_array(z);

        // construct positional args
        PyObject *args = PyTuple_New(3);
        PyTuple_SetItem(args, 0, xarray);
        PyTuple_SetItem(args, 1, yarray);
        PyTuple_SetItem(args, 2, zarray);

        // construct keyword args
        PyObject *kwargs = PyDict_New();
        for (const auto &kw : keywords) {
            PyDict_SetItemString(kwargs, kw.first.c_str(), PyString_FromString(kw.second.c_str()));
        }

        PyObject *res = PyObject_Call(detail::_interpreter::get().s_python_function_scatter, args, kwargs);

        Py_DECREF(args);
        Py_DECREF(kwargs);
        if (res)
            Py_DECREF(res);

        return res;
    }

}
