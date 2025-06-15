#pragma once

#include "core.hpp"
#include <cassert>
#include <initializer_list>

namespace plotter {

    /// Plot a line through the given x and y data points.
    template <typename NumericX, typename NumericY>
    inline bool plot(const std::vector<NumericX> &x, const std::vector<NumericY> &y, const std::string &format = "") {
        assert(x.size() == y.size());

        detail::_interpreter::get();

        PyObject *xarray = detail::get_array(x);
        PyObject *yarray = detail::get_array(y);

        PyObject *pystring = PyString_FromString(format.c_str());

        PyObject *plot_args = PyTuple_New(3);
        PyTuple_SetItem(plot_args, 0, xarray);
        PyTuple_SetItem(plot_args, 1, yarray);
        PyTuple_SetItem(plot_args, 2, pystring);

        PyObject *res = PyObject_CallObject(detail::_interpreter::get().s_python_function_plot, plot_args);

        Py_DECREF(plot_args);
        if (res)
            Py_DECREF(res);

        return res;
    }

    /// Plot a line with x and y data points and keywords
    template <typename NumericX, typename NumericY>
    inline bool plot(const std::vector<NumericX> &x, const std::vector<NumericY> &y,
                     const std::map<std::string, std::string> &keywords) {
        assert(x.size() == y.size());

        detail::_interpreter::get();

        PyObject *xarray = detail::get_array(x);
        PyObject *yarray = detail::get_array(y);

        // construct positional args
        PyObject *plot_args = PyTuple_New(2);
        PyTuple_SetItem(plot_args, 0, xarray);
        PyTuple_SetItem(plot_args, 1, yarray);

        // construct keyword args
        PyObject *kwargs = PyDict_New();
        for (std::map<std::string, std::string>::const_iterator it = keywords.begin(); it != keywords.end(); ++it) {
            PyDict_SetItemString(kwargs, it->first.c_str(), PyString_FromString(it->second.c_str()));
        }

        PyObject *res = PyObject_Call(detail::_interpreter::get().s_python_function_plot, plot_args, kwargs);

        Py_DECREF(plot_args);
        Py_DECREF(kwargs);
        if (res)
            Py_DECREF(res);

        return res;
    }

    /// Plot a line with only y data (x will be 0, 1, 2, ...)
    template <typename Numeric> bool plot(const std::vector<Numeric> &y, const std::string &format = "") {
        std::vector<Numeric> x(y.size());
        for (size_t i = 0; i < x.size(); ++i)
            x.at(i) = i;
        return plot(x, y, format);
    }

    /// Plot a line with initializer list (x will be 0, 1, 2, ...)
    template <typename Numeric> bool plot(const std::initializer_list<Numeric> &y, const std::string &format = "") {
        std::vector<Numeric> y_vec(y);
        return plot(y_vec, format);
    }

    /// Plot with y data and keywords
    template <typename Numeric>
    inline bool plot(const std::vector<Numeric> &y, const std::map<std::string, std::string> &keywords) {
        std::vector<Numeric> x(y.size());
        for (size_t i = 0; i < x.size(); ++i)
            x.at(i) = i;
        return plot(x, y, keywords);
    }

    /// Named plot (for legend)
    template <typename NumericX, typename NumericY>
    inline bool named_plot(const std::string &name, const std::vector<NumericX> &x, const std::vector<NumericY> &y,
                           const std::string &format = "") {
        std::map<std::string, std::string> keywords;
        keywords["label"] = name;
        return plot(x, y, keywords);
    }

    /// Create a 3D surface plot
    template <typename Numeric>
    inline void plot_surface(const std::vector<::std::vector<Numeric>> &x, const std::vector<::std::vector<Numeric>> &y,
                             const std::vector<::std::vector<Numeric>> &z,
                             const std::map<std::string, std::string> &keywords = {}) {
        detail::_interpreter::get();

        // We need to import mpl_toolkits for 3D plotting
        static PyObject *mpl_toolkitsmod = nullptr, *axis3dmod = nullptr;
        if (!mpl_toolkitsmod) {
            PyObject *mpl_toolkits = PyString_FromString("mpl_toolkits");
            PyObject *axis3d = PyString_FromString("mpl_toolkits.mplot3d");
            if (!mpl_toolkits || !axis3d) {
                throw std::runtime_error("couldnt create string");
            }

            mpl_toolkitsmod = PyImport_Import(mpl_toolkits);
            Py_DECREF(mpl_toolkits);
            if (!mpl_toolkitsmod) {
                throw std::runtime_error("Error loading module mpl_toolkits!");
            }

            axis3dmod = PyImport_Import(axis3d);
            Py_DECREF(axis3d);
            if (!axis3dmod) {
                throw std::runtime_error("Error loading module mpl_toolkits.mplot3d!");
            }
        }

        PyObject *xarray = detail::get_2darray(x);
        PyObject *yarray = detail::get_2darray(y);
        PyObject *zarray = detail::get_2darray(z);

        // construct positional args
        PyObject *args = PyTuple_New(3);
        PyTuple_SetItem(args, 0, xarray);
        PyTuple_SetItem(args, 1, yarray);
        PyTuple_SetItem(args, 2, zarray);

        // Build up the kw args.
        PyObject *kwargs = PyDict_New();
        for (std::map<std::string, std::string>::const_iterator it = keywords.begin(); it != keywords.end(); ++it) {
            PyDict_SetItemString(kwargs, it->first.c_str(), PyString_FromString(it->second.c_str()));
        }

        PyObject *fig = PyObject_CallObject(detail::_interpreter::get().s_python_function_figure,
                                            detail::_interpreter::get().s_python_empty_tuple);
        if (!fig)
            throw std::runtime_error("Call to figure() failed.");

        PyObject *gca_kwargs = PyDict_New();
        PyDict_SetItemString(gca_kwargs, "projection", PyString_FromString("3d"));

        PyObject *gca = PyObject_GetAttrString(fig, "gca");
        if (!gca)
            throw std::runtime_error("No gca");
        Py_INCREF(gca);
        PyObject *axis = PyObject_Call(gca, detail::_interpreter::get().s_python_empty_tuple, gca_kwargs);

        if (!axis)
            throw std::runtime_error("No axis");
        Py_INCREF(axis);

        Py_DECREF(gca);
        Py_DECREF(gca_kwargs);

        PyObject *plot_surface = PyObject_GetAttrString(axis, "plot_surface");
        if (!plot_surface)
            throw std::runtime_error("No 3D surface plot");
        Py_INCREF(plot_surface);
        PyObject *res = PyObject_Call(plot_surface, args, kwargs);
        if (!res)
            throw std::runtime_error("Failed 3D surface plot");
        Py_DECREF(plot_surface);

        Py_DECREF(axis);
        Py_DECREF(args);
        Py_DECREF(kwargs);
        Py_DECREF(fig);
        if (res)
            Py_DECREF(res);
    }

    /// Create a contour plot
    template <typename Numeric>
    inline void contour(const std::vector<::std::vector<Numeric>> &x, const std::vector<::std::vector<Numeric>> &y,
                        const std::vector<::std::vector<Numeric>> &z,
                        const std::map<std::string, std::string> &keywords = {}) {
        assert(x.size() == y.size() && x.size() == z.size());

        PyObject *xarray = detail::get_2darray(x);
        PyObject *yarray = detail::get_2darray(y);
        PyObject *zarray = detail::get_2darray(z);

        PyObject *plot_args = PyTuple_New(3);
        PyTuple_SetItem(plot_args, 0, xarray);
        PyTuple_SetItem(plot_args, 1, yarray);
        PyTuple_SetItem(plot_args, 2, zarray);

        // construct keyword args
        PyObject *kwargs = PyDict_New();
        for (std::map<std::string, std::string>::const_iterator it = keywords.begin(); it != keywords.end(); ++it) {
            PyDict_SetItemString(kwargs, it->first.c_str(), PyString_FromString(it->second.c_str()));
        }

        PyObject *res = PyObject_Call(detail::_interpreter::get().s_python_function_contour, plot_args, kwargs);

        Py_DECREF(kwargs);
        Py_DECREF(plot_args);
        if (res)
            Py_DECREF(res);
    }

    /// Create a spy plot (visualize sparsity pattern)
    template <typename Numeric>
    inline void spy(const std::vector<::std::vector<Numeric>> &x,
                    const double markersize = -1, // -1 for default matplotlib size
                    const std::map<std::string, std::string> &keywords = {}) {
        detail::_interpreter::get();

        PyObject *xarray = detail::get_2darray(x);

        PyObject *plot_args = PyTuple_New(1);
        PyTuple_SetItem(plot_args, 0, xarray);

        // construct keyword args
        PyObject *kwargs = PyDict_New();
        if (markersize != -1) {
            PyDict_SetItemString(kwargs, "markersize", PyFloat_FromDouble(markersize));
        }
        for (std::map<std::string, std::string>::const_iterator it = keywords.begin(); it != keywords.end(); ++it) {
            PyDict_SetItemString(kwargs, it->first.c_str(), PyString_FromString(it->second.c_str()));
        }

        PyObject *res = PyObject_Call(detail::_interpreter::get().s_python_function_spy, plot_args, kwargs);

        Py_DECREF(kwargs);
        Py_DECREF(plot_args);
        if (res)
            Py_DECREF(res);
    }

    /// Plot 3D lines
    template <typename Numeric>
    inline void plot3(const std::vector<Numeric> &x, const std::vector<Numeric> &y, const std::vector<Numeric> &z,
                      const std::map<std::string, std::string> &keywords = {}) {
        detail::_interpreter::get();

        // We need to import mpl_toolkits for 3D plotting
        static PyObject *mpl_toolkitsmod = nullptr, *axis3dmod = nullptr;
        if (!mpl_toolkitsmod) {
            PyObject *mpl_toolkits = PyString_FromString("mpl_toolkits");
            PyObject *axis3d = PyString_FromString("mpl_toolkits.mplot3d");
            if (!mpl_toolkits || !axis3d) {
                throw std::runtime_error("couldnt create string");
            }

            mpl_toolkitsmod = PyImport_Import(mpl_toolkits);
            Py_DECREF(mpl_toolkits);
            if (!mpl_toolkitsmod) {
                throw std::runtime_error("Error loading module mpl_toolkits!");
            }

            axis3dmod = PyImport_Import(axis3d);
            Py_DECREF(axis3d);
            if (!axis3dmod) {
                throw std::runtime_error("Error loading module mpl_toolkits.mplot3d!");
            }
        }

        assert(x.size() == y.size() && y.size() == z.size());

        PyObject *xarray = detail::get_array(x);
        PyObject *yarray = detail::get_array(y);
        PyObject *zarray = detail::get_array(z);

        // construct positional args
        PyObject *args = PyTuple_New(3);
        PyTuple_SetItem(args, 0, xarray);
        PyTuple_SetItem(args, 1, yarray);
        PyTuple_SetItem(args, 2, zarray);

        // Build up the kw args.
        PyObject *kwargs = PyDict_New();
        for (std::map<std::string, std::string>::const_iterator it = keywords.begin(); it != keywords.end(); ++it) {
            PyDict_SetItemString(kwargs, it->first.c_str(), PyString_FromString(it->second.c_str()));
        }

        PyObject *fig = PyObject_CallObject(detail::_interpreter::get().s_python_function_figure,
                                            detail::_interpreter::get().s_python_empty_tuple);
        if (!fig)
            throw std::runtime_error("Call to figure() failed.");

        PyObject *gca_kwargs = PyDict_New();
        PyDict_SetItemString(gca_kwargs, "projection", PyString_FromString("3d"));

        PyObject *gca = PyObject_GetAttrString(fig, "gca");
        if (!gca)
            throw std::runtime_error("No gca");
        Py_INCREF(gca);
        PyObject *axis = PyObject_Call(gca, detail::_interpreter::get().s_python_empty_tuple, gca_kwargs);

        if (!axis)
            throw std::runtime_error("No axis");
        Py_INCREF(axis);

        Py_DECREF(gca);
        Py_DECREF(gca_kwargs);

        PyObject *plot3 = PyObject_GetAttrString(axis, "plot");
        if (!plot3)
            throw std::runtime_error("No 3D line plot");
        Py_INCREF(plot3);
        PyObject *res = PyObject_Call(plot3, args, kwargs);
        if (!res)
            throw std::runtime_error("Failed 3D line plot");
        Py_DECREF(plot3);

        Py_DECREF(axis);
        Py_DECREF(args);
        Py_DECREF(kwargs);
        Py_DECREF(fig);
        if (res)
            Py_DECREF(res);
    }

    /// Create a stem plot
    template <typename Numeric>
    inline bool stem(const std::vector<Numeric> &x, const std::vector<Numeric> &y,
                     const std::map<std::string, std::string> &keywords = {}) {
        assert(x.size() == y.size());

        detail::_interpreter::get();

        // using numpy arrays
        PyObject *xarray = detail::get_array(x);
        PyObject *yarray = detail::get_array(y);

        // construct positional args
        PyObject *args = PyTuple_New(2);
        PyTuple_SetItem(args, 0, xarray);
        PyTuple_SetItem(args, 1, yarray);

        // construct keyword args
        PyObject *kwargs = PyDict_New();
        for (std::map<std::string, std::string>::const_iterator it = keywords.begin(); it != keywords.end(); ++it) {
            PyDict_SetItemString(kwargs, it->first.c_str(), PyString_FromString(it->second.c_str()));
        }

        PyObject *res = PyObject_Call(detail::_interpreter::get().s_python_function_stem, args, kwargs);

        Py_DECREF(args);
        Py_DECREF(kwargs);
        if (res)
            Py_DECREF(res);

        return res;
    }

    /// Fill area between curve and x-axis
    template <typename Numeric>
    inline bool fill(const std::vector<Numeric> &x, const std::vector<Numeric> &y,
                     const std::map<std::string, std::string> &keywords = {}) {
        assert(x.size() == y.size());

        detail::_interpreter::get();

        // using numpy arrays
        PyObject *xarray = detail::get_array(x);
        PyObject *yarray = detail::get_array(y);

        // construct positional args
        PyObject *args = PyTuple_New(2);
        PyTuple_SetItem(args, 0, xarray);
        PyTuple_SetItem(args, 1, yarray);

        // construct keyword args
        PyObject *kwargs = PyDict_New();
        for (auto it = keywords.begin(); it != keywords.end(); ++it) {
            PyDict_SetItemString(kwargs, it->first.c_str(), PyString_FromString(it->second.c_str()));
        }

        PyObject *res = PyObject_Call(detail::_interpreter::get().s_python_function_fill, args, kwargs);

        Py_DECREF(args);
        Py_DECREF(kwargs);

        if (res)
            Py_DECREF(res);

        return res;
    }

    /// Fill area between two curves
    template <typename Numeric>
    inline bool fill_between(const std::vector<Numeric> &x, const std::vector<Numeric> &y1,
                             const std::vector<Numeric> &y2, const std::map<std::string, std::string> &keywords = {}) {
        assert(x.size() == y1.size());
        assert(x.size() == y2.size());

        detail::_interpreter::get();

        // using numpy arrays
        PyObject *xarray = detail::get_array(x);
        PyObject *y1array = detail::get_array(y1);
        PyObject *y2array = detail::get_array(y2);

        // construct positional args
        PyObject *args = PyTuple_New(3);
        PyTuple_SetItem(args, 0, xarray);
        PyTuple_SetItem(args, 1, y1array);
        PyTuple_SetItem(args, 2, y2array);

        // construct keyword args
        PyObject *kwargs = PyDict_New();
        for (std::map<std::string, std::string>::const_iterator it = keywords.begin(); it != keywords.end(); ++it) {
            PyDict_SetItemString(kwargs, it->first.c_str(), PyString_FromString(it->second.c_str()));
        }

        PyObject *res = PyObject_Call(detail::_interpreter::get().s_python_function_fill_between, args, kwargs);

        Py_DECREF(args);
        Py_DECREF(kwargs);
        if (res)
            Py_DECREF(res);

        return res;
    }

    /// Create an arrow
    template <typename Numeric>
    inline bool arrow(Numeric x, Numeric y, Numeric end_x, Numeric end_y, const std::string &fc = "r",
                      const std::string &ec = "r", const double head_width = 1.0, const double head_length = 1.0) {
        PyObject *obj_x = PyFloat_FromDouble(x);
        PyObject *obj_y = PyFloat_FromDouble(y);
        PyObject *obj_end_x = PyFloat_FromDouble(end_x);
        PyObject *obj_end_y = PyFloat_FromDouble(end_y);

        PyObject *kwargs = PyDict_New();
        PyDict_SetItemString(kwargs, "fc", PyString_FromString(fc.c_str()));
        PyDict_SetItemString(kwargs, "ec", PyString_FromString(ec.c_str()));
        PyDict_SetItemString(kwargs, "head_width", PyFloat_FromDouble(head_width));
        PyDict_SetItemString(kwargs, "head_length", PyFloat_FromDouble(head_length));

        PyObject *plot_args = PyTuple_New(4);
        PyTuple_SetItem(plot_args, 0, obj_x);
        PyTuple_SetItem(plot_args, 1, obj_y);
        PyTuple_SetItem(plot_args, 2, obj_end_x);
        PyTuple_SetItem(plot_args, 3, obj_end_y);

        PyObject *res = PyObject_Call(detail::_interpreter::get().s_python_function_arrow, plot_args, kwargs);

        Py_DECREF(plot_args);
        Py_DECREF(kwargs);
        if (res)
            Py_DECREF(res);

        return res;
    }

    /// Create a histogram
    template <typename Numeric>
    inline bool hist(const std::vector<Numeric> &y, long bins = 10, std::string color = "b", double alpha = 1.0,
                     bool cumulative = false) {
        detail::_interpreter::get();

        PyObject *yarray = detail::get_array(y);

        PyObject *kwargs = PyDict_New();
        PyDict_SetItemString(kwargs, "bins", PyLong_FromLong(bins));
        PyDict_SetItemString(kwargs, "color", PyString_FromString(color.c_str()));
        PyDict_SetItemString(kwargs, "alpha", PyFloat_FromDouble(alpha));
        PyDict_SetItemString(kwargs, "cumulative", cumulative ? Py_True : Py_False);

        PyObject *plot_args = PyTuple_New(1);
        PyTuple_SetItem(plot_args, 0, yarray);

        PyObject *res = PyObject_Call(detail::_interpreter::get().s_python_function_hist, plot_args, kwargs);

        Py_DECREF(plot_args);
        Py_DECREF(kwargs);
        if (res)
            Py_DECREF(res);

        return res;
    }

    /// Semi-log plots
    template <typename Numeric>
    inline bool semilogx(const std::vector<Numeric> &x, const std::vector<Numeric> &y, const std::string &s = "") {
        assert(x.size() == y.size());

        detail::_interpreter::get();

        PyObject *xarray = detail::get_array(x);
        PyObject *yarray = detail::get_array(y);

        PyObject *pystring = PyString_FromString(s.c_str());

        PyObject *plot_args = PyTuple_New(3);
        PyTuple_SetItem(plot_args, 0, xarray);
        PyTuple_SetItem(plot_args, 1, yarray);
        PyTuple_SetItem(plot_args, 2, pystring);

        PyObject *res = PyObject_CallObject(detail::_interpreter::get().s_python_function_semilogx, plot_args);

        Py_DECREF(plot_args);
        if (res)
            Py_DECREF(res);

        return res;
    }

    template <typename Numeric>
    inline bool semilogy(const std::vector<Numeric> &x, const std::vector<Numeric> &y, const std::string &s = "") {
        assert(x.size() == y.size());

        detail::_interpreter::get();

        PyObject *xarray = detail::get_array(x);
        PyObject *yarray = detail::get_array(y);

        PyObject *pystring = PyString_FromString(s.c_str());

        PyObject *plot_args = PyTuple_New(3);
        PyTuple_SetItem(plot_args, 0, xarray);
        PyTuple_SetItem(plot_args, 1, yarray);
        PyTuple_SetItem(plot_args, 2, pystring);

        PyObject *res = PyObject_CallObject(detail::_interpreter::get().s_python_function_semilogy, plot_args);

        Py_DECREF(plot_args);
        if (res)
            Py_DECREF(res);

        return res;
    }

    template <typename Numeric>
    inline bool loglog(const std::vector<Numeric> &x, const std::vector<Numeric> &y, const std::string &s = "") {
        assert(x.size() == y.size());

        detail::_interpreter::get();

        PyObject *xarray = detail::get_array(x);
        PyObject *yarray = detail::get_array(y);

        PyObject *pystring = PyString_FromString(s.c_str());

        PyObject *plot_args = PyTuple_New(3);
        PyTuple_SetItem(plot_args, 0, xarray);
        PyTuple_SetItem(plot_args, 1, yarray);
        PyTuple_SetItem(plot_args, 2, pystring);

        PyObject *res = PyObject_CallObject(detail::_interpreter::get().s_python_function_loglog, plot_args);

        Py_DECREF(plot_args);
        if (res)
            Py_DECREF(res);

        return res;
    }

    /// Error bars
    template <typename Numeric>
    inline bool errorbar(const std::vector<Numeric> &x, const std::vector<Numeric> &y, const std::vector<Numeric> &yerr,
                         const std::map<std::string, std::string> &keywords = {}) {
        assert(x.size() == y.size());

        detail::_interpreter::get();

        PyObject *xarray = detail::get_array(x);
        PyObject *yarray = detail::get_array(y);
        PyObject *yerrarray = detail::get_array(yerr);

        // construct keyword args
        PyObject *kwargs = PyDict_New();
        for (std::map<std::string, std::string>::const_iterator it = keywords.begin(); it != keywords.end(); ++it) {
            PyDict_SetItemString(kwargs, it->first.c_str(), PyString_FromString(it->second.c_str()));
        }

        PyDict_SetItemString(kwargs, "yerr", yerrarray);

        PyObject *plot_args = PyTuple_New(2);
        PyTuple_SetItem(plot_args, 0, xarray);
        PyTuple_SetItem(plot_args, 1, yarray);

        PyObject *res = PyObject_Call(detail::_interpreter::get().s_python_function_errorbar, plot_args, kwargs);

        Py_DECREF(kwargs);
        Py_DECREF(plot_args);

        if (res)
            Py_DECREF(res);
        else
            throw std::runtime_error("Call to errorbar() failed.");

        return res;
    }

    /// Create a bar plot
    template <typename Numeric>
    inline bool bar(const std::vector<Numeric> &y, const std::map<std::string, std::string> &keywords = {}) {
        detail::_interpreter::get();

        // Create x values as indices
        std::vector<size_t> x(y.size());
        for (size_t i = 0; i < x.size(); ++i)
            x[i] = i;

        PyObject *xarray = detail::get_array(x);
        PyObject *yarray = detail::get_array(y);

        PyObject *kwargs = PyDict_New();
        for (std::map<std::string, std::string>::const_iterator it = keywords.begin(); it != keywords.end(); ++it) {
            PyDict_SetItemString(kwargs, it->first.c_str(), PyString_FromString(it->second.c_str()));
        }

        PyObject *plot_args = PyTuple_New(2);
        PyTuple_SetItem(plot_args, 0, xarray);
        PyTuple_SetItem(plot_args, 1, yarray);

        PyObject *res = PyObject_Call(detail::_interpreter::get().s_python_function_bar, plot_args, kwargs);

        Py_DECREF(kwargs);
        Py_DECREF(plot_args);

        if (res)
            Py_DECREF(res);
        else
            throw std::runtime_error("Call to bar() failed.");

        return true;
    }

    /// Quiver plot (arrow plot)
    template <typename NumericX, typename NumericY, typename NumericU, typename NumericW>
    inline bool quiver(const std::vector<NumericX> &x, const std::vector<NumericY> &y, const std::vector<NumericU> &u,
                       const std::vector<NumericW> &w, const std::map<std::string, std::string> &keywords = {}) {
        // Simple stub version to test template linking
        return true;
    }

    // Explicit specialization for int
    template <>
    inline bool quiver<int, int, int, int>(const std::vector<int> &x, const std::vector<int> &y,
                                           const std::vector<int> &u, const std::vector<int> &v,
                                           const std::map<std::string, std::string> &keywords) {
        return true;
    }
} // namespace plotter
