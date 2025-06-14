#pragma once

// Python headers must be included before any system headers, since
// they define _POSIX_C_SOURCE
#include <Python.h>

#include <algorithm>
#include <array>
#include <cstdint>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

// Always include NumPy - we need it for the plotter library
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>

#ifdef WITH_OPENCV
#include <opencv2/opencv.hpp>

/*
 * A bunch of constants were removed in OpenCV 4 in favour of enum classes, so
 * define the ones we need here.
 */
#if CV_MAJOR_VERSION > 3
#define CV_BGR2RGB cv::COLOR_BGR2RGB
#define CV_BGRA2RGBA cv::COLOR_BGRA2RGBA
#endif
#endif // WITH_OPENCV

#if PY_MAJOR_VERSION >= 3
#define PyString_FromString PyUnicode_FromString
#define PyInt_FromLong PyLong_FromLong
#define PyString_FromString PyUnicode_FromString
#endif

namespace plotter {
    namespace detail {

        static std::string s_backend;

        struct _interpreter {
            PyObject *s_python_function_arrow;
            PyObject *s_python_function_show;
            PyObject *s_python_function_close;
            PyObject *s_python_function_draw;
            PyObject *s_python_function_pause;
            PyObject *s_python_function_save;
            PyObject *s_python_function_figure;
            PyObject *s_python_function_fignum_exists;
            PyObject *s_python_function_plot;
            PyObject *s_python_function_quiver;
            PyObject *s_python_function_contour;
            PyObject *s_python_function_semilogx;
            PyObject *s_python_function_semilogy;
            PyObject *s_python_function_loglog;
            PyObject *s_python_function_fill;
            PyObject *s_python_function_fill_between;
            PyObject *s_python_function_hist;
            PyObject *s_python_function_imshow;
            PyObject *s_python_function_scatter;
            PyObject *s_python_function_boxplot;
            PyObject *s_python_function_subplot;
            PyObject *s_python_function_subplot2grid;
            PyObject *s_python_function_legend;
            PyObject *s_python_function_xlim;
            PyObject *s_python_function_ion;
            PyObject *s_python_function_ginput;
            PyObject *s_python_function_ylim;
            PyObject *s_python_function_title;
            PyObject *s_python_function_axis;
            PyObject *s_python_function_axhline;
            PyObject *s_python_function_axvline;
            PyObject *s_python_function_axvspan;
            PyObject *s_python_function_xlabel;
            PyObject *s_python_function_ylabel;
            PyObject *s_python_function_gca;
            PyObject *s_python_function_xticks;
            PyObject *s_python_function_yticks;
            PyObject *s_python_function_margins;
            PyObject *s_python_function_tick_params;
            PyObject *s_python_function_grid;
            PyObject *s_python_function_cla;
            PyObject *s_python_function_clf;
            PyObject *s_python_function_errorbar;
            PyObject *s_python_function_annotate;
            PyObject *s_python_function_tight_layout;
            PyObject *s_python_colormap;
            PyObject *s_python_empty_tuple;
            PyObject *s_python_function_stem;
            PyObject *s_python_function_xkcd;
            PyObject *s_python_function_text;
            PyObject *s_python_function_suptitle;
            PyObject *s_python_function_bar;
            PyObject *s_python_function_subplots_adjust;
            PyObject *s_python_function_barh;
            PyObject *s_python_function_spy;

            /* Don't call this destructor explicitly. Rather, call Py_Finalize() on exit.
               The reason is that Py_Finalize() will restore the original signal handlers
               whereas this destructor may not. */
            ~_interpreter() { Py_Finalize(); }

            static _interpreter &get() {
                static _interpreter ctx;
                return ctx;
            }

          private:
            _interpreter();
        };

        // NumPy type selection templates - always available
        template <typename T> struct select_npy_type {
            const static NPY_TYPES type = NPY_NOTYPE;
        }; // Default
        template <> struct select_npy_type<double> {
            const static NPY_TYPES type = NPY_DOUBLE;
        };
        template <> struct select_npy_type<float> {
            const static NPY_TYPES type = NPY_FLOAT;
        };
        template <> struct select_npy_type<bool> {
            const static NPY_TYPES type = NPY_BOOL;
        };
        template <> struct select_npy_type<int8_t> {
            const static NPY_TYPES type = NPY_INT8;
        };
        template <> struct select_npy_type<int16_t> {
            const static NPY_TYPES type = NPY_SHORT;
        };
        template <> struct select_npy_type<int32_t> {
            const static NPY_TYPES type = NPY_INT;
        };
        template <> struct select_npy_type<int64_t> {
            const static NPY_TYPES type = NPY_INT64;
        };
        template <> struct select_npy_type<uint8_t> {
            const static NPY_TYPES type = NPY_UINT8;
        };
        template <> struct select_npy_type<uint16_t> {
            const static NPY_TYPES type = NPY_USHORT;
        };
        template <> struct select_npy_type<uint32_t> {
            const static NPY_TYPES type = NPY_ULONG;
        };
        template <> struct select_npy_type<uint64_t> {
            const static NPY_TYPES type = NPY_UINT64;
        };

// Handle special cases for long long types
#if !defined(_MSC_VER) || _MSC_VER >= 1900
        template <> struct select_npy_type<long long> {
            const static NPY_TYPES type = NPY_INT64;
        };
#endif
        template <> struct select_npy_type<unsigned long long> {
            const static NPY_TYPES type = NPY_UINT64;
        };

        // Utility functions for creating Python arrays from C++ data
        template <typename Numeric> PyObject *get_array(const std::vector<Numeric> &v);

        template <typename Numeric> PyObject *get_2darray(const std::vector<std::vector<Numeric>> &v);

        template <typename Numeric> PyObject *get_1darray(const Numeric *v, size_t size);

        PyObject *get_array(const std::vector<std::string> &strings);

    } // namespace detail

    // Backend configuration
    inline void backend(const std::string &name);

    // Annotation function
    inline bool annotate(std::string annotation, double x, double y);

} // namespace plotter
