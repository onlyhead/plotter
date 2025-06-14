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

    /// Set figure size
    inline void figure_size(int width, int height);

    /// Set x-axis limits
    template <typename Numeric> inline void xlim(Numeric left, Numeric right);

    /// Set y-axis limits
    template <typename Numeric> inline void ylim(Numeric bottom, Numeric top);

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

    /// Enable xkcd style
    inline void xkcd();

    /// Tight layout
    inline void tight_layout();

    /// Adjust subplot parameters
    inline void subplots_adjust(const std::map<std::string, std::string> &keywords = {});

    // Implementation of show function
    inline void show(const bool block) {
        detail::_interpreter::get();

        PyObject *res;
        if (block) {
            res = PyObject_CallObject(detail::_interpreter::get().s_python_function_show,
                                      detail::_interpreter::get().s_python_empty_tuple);
        } else {
            PyObject *kwargs = PyDict_New();
            PyDict_SetItemString(kwargs, "block", Py_False);
            res = PyObject_Call(detail::_interpreter::get().s_python_function_show,
                                detail::_interpreter::get().s_python_empty_tuple, kwargs);
            Py_DECREF(kwargs);
        }

        if (!res)
            throw std::runtime_error("Call to show() failed.");

        Py_DECREF(res);
    }

    // Implementation of figure_size function
    inline void figure_size(int width, int height) {
        detail::_interpreter::get();

        PyObject *fig = PyObject_CallObject(detail::_interpreter::get().s_python_function_figure,
                                            detail::_interpreter::get().s_python_empty_tuple);
        if (!fig)
            throw std::runtime_error("Call to figure() failed.");

        PyObject *size = Py_BuildValue("(ii)", width, height);
        PyObject_SetAttrString(fig, "set_size_inches", size);

        Py_DECREF(size);
        Py_DECREF(fig);
    }

    // Implementation of xlim function
    template <typename Numeric> inline void xlim(Numeric left, Numeric right) {
        detail::_interpreter::get();

        PyObject *args = PyTuple_New(2);
        PyTuple_SetItem(args, 0, PyFloat_FromDouble(static_cast<double>(left)));
        PyTuple_SetItem(args, 1, PyFloat_FromDouble(static_cast<double>(right)));

        PyObject *res = PyObject_CallObject(detail::_interpreter::get().s_python_function_xlim, args);
        if (!res)
            throw std::runtime_error("Call to xlim() failed.");

        Py_DECREF(args);
        Py_DECREF(res);
    }

    // Implementation of ylim function
    template <typename Numeric> inline void ylim(Numeric bottom, Numeric top) {
        detail::_interpreter::get();

        PyObject *args = PyTuple_New(2);
        PyTuple_SetItem(args, 0, PyFloat_FromDouble(static_cast<double>(bottom)));
        PyTuple_SetItem(args, 1, PyFloat_FromDouble(static_cast<double>(top)));

        PyObject *res = PyObject_CallObject(detail::_interpreter::get().s_python_function_ylim, args);
        if (!res)
            throw std::runtime_error("Call to ylim() failed.");

        Py_DECREF(args);
        Py_DECREF(res);
    }

    // Implementation of save function
    inline void save(const std::string &filename, int dpi) {
        detail::_interpreter::get();

        PyObject *args = PyTuple_New(1);
        PyTuple_SetItem(args, 0, PyString_FromString(filename.c_str()));

        PyObject *kwargs = PyDict_New();
        PyDict_SetItemString(kwargs, "dpi", PyLong_FromLong(dpi));

        PyObject *res = PyObject_Call(detail::_interpreter::get().s_python_function_save, args, kwargs);
        if (!res)
            throw std::runtime_error("Call to save() failed.");

        Py_DECREF(args);
        Py_DECREF(kwargs);
        Py_DECREF(res);
    }

    // Implementation of clf function
    inline void clf() {
        detail::_interpreter::get();

        PyObject *res = PyObject_CallObject(detail::_interpreter::get().s_python_function_clf,
                                            detail::_interpreter::get().s_python_empty_tuple);

        if (!res)
            throw std::runtime_error("Call to clf() failed.");

        Py_DECREF(res);
    }

    /// Pause for a specified interval
    template <typename Numeric> inline void pause(Numeric interval) {
        detail::_interpreter::get();

        PyObject *args = PyTuple_New(1);
        PyTuple_SetItem(args, 0, PyFloat_FromDouble(interval));

        PyObject *res = PyObject_CallObject(detail::_interpreter::get().s_python_function_pause, args);
        if (!res)
            throw std::runtime_error("Call to pause() failed.");

        Py_DECREF(args);
        Py_DECREF(res);
    }

    // Implementation of xkcd function
    inline void xkcd() {
        detail::_interpreter::get();

        PyObject *res;
        PyObject *kwargs = PyDict_New();

        res = PyObject_Call(detail::_interpreter::get().s_python_function_xkcd,
                            detail::_interpreter::get().s_python_empty_tuple, kwargs);

        Py_DECREF(kwargs);

        if (!res)
            throw std::runtime_error("Call to xkcd() failed.");

        Py_DECREF(res);
    }

    /// Clear the current figure
    inline void clf();

    /// Set figure size
    inline void figure_size(int width, int height);

    /// Set x-axis limits
    template <typename Numeric> inline void xlim(Numeric left, Numeric right);

    /// Set y-axis limits
    template <typename Numeric> inline void ylim(Numeric bottom, Numeric top);

    /// Clear the current axes
    inline void cla();

    /// Close figure(s)
    inline void close();
    inline void close(long fignum);

    /// Enable interactive mode
    inline void ion();

    /// Disable interactive mode
    inline void ioff();
} // namespace plotter
