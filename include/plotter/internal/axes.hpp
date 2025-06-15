#pragma once

#include "core.hpp"

namespace plotter {

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
    inline void set_zlabel(const std::string &str, const std::map<std::string, std::string> &keywords = {});

    /// Set plot title
    inline void title(const std::string &titlestr, const std::map<std::string, std::string> &keywords = {});

    /// Set super title
    inline void suptitle(const std::string &suptitlestr, const std::map<std::string, std::string> &keywords);

    /// Create subplot
    inline void subplot(long nrows, long ncols, long index, const std::map<std::string, std::string> &keywords);

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

    /// Set equal aspect ratio
    inline void set_aspect_equal() {
        detail::_interpreter::get();

        PyObject *args = PyTuple_New(1);
        PyTuple_SetItem(args, 0, PyString_FromString("equal"));
        PyObject *kwargs = PyDict_New();

        PyObject *ax = PyObject_CallObject(detail::_interpreter::get().s_python_function_gca,
                                           detail::_interpreter::get().s_python_empty_tuple);
        if (!ax)
            throw std::runtime_error("Call to gca() failed.");

        PyObject *set_aspect = PyObject_GetAttrString(ax, "set_aspect");
        if (!set_aspect)
            throw std::runtime_error("Couldn't find set_aspect");

        PyObject *res = PyObject_Call(set_aspect, args, kwargs);
        if (!res)
            throw std::runtime_error("Call to set_aspect() failed.");

        Py_DECREF(args);
        Py_DECREF(kwargs);
        Py_DECREF(ax);
        Py_DECREF(set_aspect);
        Py_DECREF(res);
    }

    /// Create subplot with grid specification (simple version)
    inline void subplot2grid(long nrows, long ncols, long rowid = 0, long colid = 0, long rowspan = 1,
                             long colspan = 1) {
        detail::_interpreter::get();

        PyObject *shape = PyTuple_New(2);
        PyTuple_SetItem(shape, 0, PyLong_FromLong(nrows));
        PyTuple_SetItem(shape, 1, PyLong_FromLong(ncols));

        PyObject *loc = PyTuple_New(2);
        PyTuple_SetItem(loc, 0, PyLong_FromLong(rowid));
        PyTuple_SetItem(loc, 1, PyLong_FromLong(colid));

        PyObject *args = PyTuple_New(4);
        PyTuple_SetItem(args, 0, shape);
        PyTuple_SetItem(args, 1, loc);
        PyTuple_SetItem(args, 2, PyLong_FromLong(rowspan));
        PyTuple_SetItem(args, 3, PyLong_FromLong(colspan));

        PyObject *res = PyObject_CallObject(detail::_interpreter::get().s_python_function_subplot2grid, args);
        if (!res)
            throw std::runtime_error("Call to subplot2grid() failed.");

        Py_DECREF(shape);
        Py_DECREF(loc);
        Py_DECREF(args);
        Py_DECREF(res);
    }

    /// Add text implementation
    template <typename Numeric>
    void text(Numeric x, Numeric y, const std::string &s = "",
              const std::map<std::string, std::string> &keywords = {}) {
        detail::_interpreter::get();

        PyObject *args = PyTuple_New(3);
        PyTuple_SetItem(args, 0, PyFloat_FromDouble(x));
        PyTuple_SetItem(args, 1, PyFloat_FromDouble(y));
        PyTuple_SetItem(args, 2, PyString_FromString(s.c_str()));

        // construct keyword args
        PyObject *kwargs = PyDict_New();
        for (auto it = keywords.begin(); it != keywords.end(); ++it) {
            PyDict_SetItemString(kwargs, it->first.c_str(), PyString_FromString(it->second.c_str()));
        }

        PyObject *res = PyObject_Call(detail::_interpreter::get().s_python_function_text, args, kwargs);
        if (!res)
            throw std::runtime_error("Call to text() failed.");

        Py_DECREF(args);
        Py_DECREF(kwargs);
        Py_DECREF(res);
    }

    /// Get current axes
    inline long gca();

    /// Get mouse input
    inline std::vector<std::array<double, 2>> ginput(const int numClicks = 1,
                                                     const std::map<std::string, std::string> &keywords = {});

    // Implementations
    inline void title(const std::string &titlestr, const std::map<std::string, std::string> &keywords) {
        detail::_interpreter::get();

        PyObject *args = PyTuple_New(1);
        PyTuple_SetItem(args, 0, PyString_FromString(titlestr.c_str()));

        PyObject *kwargs = PyDict_New();
        for (auto const &it : keywords) {
            PyDict_SetItemString(kwargs, it.first.c_str(), PyString_FromString(it.second.c_str()));
        }

        PyObject *res = PyObject_Call(detail::_interpreter::get().s_python_function_title, args, kwargs);
        if (!res)
            throw std::runtime_error("Call to title() failed.");

        Py_DECREF(args);
        Py_DECREF(kwargs);
        Py_DECREF(res);
    }

    inline void legend() {
        detail::_interpreter::get();

        PyObject *res = PyObject_CallObject(detail::_interpreter::get().s_python_function_legend,
                                            detail::_interpreter::get().s_python_empty_tuple);
        if (!res)
            throw std::runtime_error("Call to legend() failed.");

        Py_DECREF(res);
    }

    inline void set_zlabel(const std::string &str, const std::map<std::string, std::string> &keywords) {
        detail::_interpreter::get();

        // Import matplotlib.pyplot to call gca() function
        PyObject *pyplot_name = PyString_FromString("matplotlib.pyplot");
        PyObject *pyplot = PyImport_Import(pyplot_name);
        Py_DECREF(pyplot_name);

        if (!pyplot)
            throw std::runtime_error("Failed to import matplotlib.pyplot for set_zlabel");

        PyObject *gca_func = PyObject_GetAttrString(pyplot, "gca");
        if (!gca_func) {
            Py_DECREF(pyplot);
            throw std::runtime_error("Failed to get gca function");
        }

        PyObject *gca = PyObject_CallObject(gca_func, detail::_interpreter::get().s_python_empty_tuple);
        if (!gca) {
            Py_DECREF(gca_func);
            Py_DECREF(pyplot);
            throw std::runtime_error("Failed to get current axes for set_zlabel");
        }

        PyObject *args = PyTuple_New(1);
        PyTuple_SetItem(args, 0, PyString_FromString(str.c_str()));

        PyObject *kwargs = PyDict_New();
        for (auto const &it : keywords) {
            PyDict_SetItemString(kwargs, it.first.c_str(), PyString_FromString(it.second.c_str()));
        }

        PyObject *set_zlabel_func = PyObject_GetAttrString(gca, "set_zlabel");
        if (!set_zlabel_func) {
            Py_DECREF(args);
            Py_DECREF(kwargs);
            Py_DECREF(gca);
            Py_DECREF(gca_func);
            Py_DECREF(pyplot);
            throw std::runtime_error("set_zlabel function not found on axes");
        }

        PyObject *res = PyObject_Call(set_zlabel_func, args, kwargs);
        if (!res) {
            Py_DECREF(args);
            Py_DECREF(kwargs);
            Py_DECREF(set_zlabel_func);
            Py_DECREF(gca);
            Py_DECREF(gca_func);
            Py_DECREF(pyplot);
            throw std::runtime_error("Call to set_zlabel() failed.");
        }

        Py_DECREF(args);
        Py_DECREF(kwargs);
        Py_DECREF(set_zlabel_func);
        Py_DECREF(gca);
        Py_DECREF(gca_func);
        Py_DECREF(pyplot);
        Py_DECREF(res);
    }

    inline void xlabel(const std::string &str, const std::map<std::string, std::string> &keywords) {
        detail::_interpreter::get();

        PyObject *args = PyTuple_New(1);
        PyTuple_SetItem(args, 0, PyString_FromString(str.c_str()));

        PyObject *kwargs = PyDict_New();
        for (auto const &it : keywords) {
            PyDict_SetItemString(kwargs, it.first.c_str(), PyString_FromString(it.second.c_str()));
        }

        PyObject *res = PyObject_Call(detail::_interpreter::get().s_python_function_xlabel, args, kwargs);
        if (!res)
            throw std::runtime_error("Call to xlabel() failed.");

        Py_DECREF(args);
        Py_DECREF(kwargs);
        Py_DECREF(res);
    }

    inline void ylabel(const std::string &str, const std::map<std::string, std::string> &keywords) {
        detail::_interpreter::get();

        PyObject *args = PyTuple_New(1);
        PyTuple_SetItem(args, 0, PyString_FromString(str.c_str()));

        PyObject *kwargs = PyDict_New();
        for (auto const &it : keywords) {
            PyDict_SetItemString(kwargs, it.first.c_str(), PyString_FromString(it.second.c_str()));
        }

        PyObject *res = PyObject_Call(detail::_interpreter::get().s_python_function_ylabel, args, kwargs);
        if (!res)
            throw std::runtime_error("Call to ylabel() failed.");

        Py_DECREF(args);
        Py_DECREF(kwargs);
        Py_DECREF(res);
    }

    inline void suptitle(const std::string &suptitlestr, const std::map<std::string, std::string> &keywords = {}) {
        detail::_interpreter::get();

        PyObject *args = PyTuple_New(1);
        PyTuple_SetItem(args, 0, PyString_FromString(suptitlestr.c_str()));

        PyObject *kwargs = PyDict_New();
        for (auto const &it : keywords) {
            PyDict_SetItemString(kwargs, it.first.c_str(), PyString_FromString(it.second.c_str()));
        }

        PyObject *res = PyObject_Call(detail::_interpreter::get().s_python_function_suptitle, args, kwargs);
        if (!res)
            throw std::runtime_error("Call to suptitle() failed.");

        Py_DECREF(args);
        Py_DECREF(kwargs);
        Py_DECREF(res);
    }

    inline void subplot(long nrows, long ncols, long index, const std::map<std::string, std::string> &keywords = {}) {
        detail::_interpreter::get();

        PyObject *args = PyTuple_New(3);
        PyTuple_SetItem(args, 0, PyLong_FromLong(nrows));
        PyTuple_SetItem(args, 1, PyLong_FromLong(ncols));
        PyTuple_SetItem(args, 2, PyLong_FromLong(index));

        PyObject *kwargs = PyDict_New();
        for (auto const &it : keywords) {
            PyDict_SetItemString(kwargs, it.first.c_str(), PyString_FromString(it.second.c_str()));
        }

        PyObject *res = PyObject_Call(detail::_interpreter::get().s_python_function_subplot, args, kwargs);
        if (!res)
            throw std::runtime_error("Call to subplot() failed.");

        Py_DECREF(args);
        Py_DECREF(kwargs);
        Py_DECREF(res);
    }

} // namespace plotter
