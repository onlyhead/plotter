#pragma once

// Python headers must be included before any system headers, since
// they define _POSIX_C_SOURCE
#include <Python.h>

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstring>
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

#if PY_MAJOR_VERSION >= 3
#define PyString_FromString PyUnicode_FromString
#define PyInt_FromLong PyLong_FromLong
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
            PyObject *s_python_function_fill;
            PyObject *s_python_function_fill_between;
            PyObject *s_python_function_hist;
            PyObject *s_python_function_scatter;
            PyObject *s_python_function_boxplot;
            PyObject *s_python_function_bar;
            PyObject *s_python_function_barh;
            PyObject *s_python_function_loglog;
            PyObject *s_python_function_semilogx;
            PyObject *s_python_function_semilogy;
            PyObject *s_python_function_text;
            PyObject *s_python_function_suptitle;
            PyObject *s_python_function_title;
            PyObject *s_python_function_axis;
            PyObject *s_python_function_xlabel;
            PyObject *s_python_function_ylabel;
            PyObject *s_python_function_xticks;
            PyObject *s_python_function_yticks;
            PyObject *s_python_function_subplot;
            PyObject *s_python_function_legend;
            PyObject *s_python_function_ylim;
            PyObject *s_python_function_xlim;
            PyObject *s_python_function_imshow;
            PyObject *s_python_function_annotate;
            PyObject *s_python_function_clf;
            PyObject *s_python_function_errorbar;
            PyObject *s_python_function_tight_layout;
            PyObject *s_python_function_stem;
            PyObject *s_python_function_xkcd;
            PyObject *s_python_function_contour;
            PyObject *s_python_function_contourf;
            PyObject *s_python_function_colorbar;
            PyObject *s_python_function_subplots_adjust;
            PyObject *s_python_function_rcparams;
            PyObject *s_python_function_spy;
            PyObject *s_python_function_gca;
            PyObject *s_python_function_subplot2grid;
            PyObject *s_python_function_quiver;
            PyObject *s_python_empty_tuple;

            PyObject *safe_import(PyObject *module, std::string fname) {
                PyObject *fn = PyObject_GetAttrString(module, fname.c_str());

                if (!fn)
                    throw std::runtime_error(std::string("Couldn't find required function: ") + fname);

                if (!PyFunction_Check(fn))
                    throw std::runtime_error(fname + std::string(" is unexpectedly not a PyFunction."));

                return fn;
            }

#ifndef WITHOUT_NUMPY
#if PY_MAJOR_VERSION >= 3
            void *import_numpy() {
                import_array(); // initialize C-API
                return NULL;
            }
#else
            void import_numpy() {
                import_array(); // initialize C-API
            }
#endif
#endif

            _interpreter() {
                // optional but recommended
#if PY_MAJOR_VERSION >= 3
                wchar_t name[] = L"plotting";
#else
                char name[] = "plotting";
#endif
                Py_SetProgramName(name);
                Py_Initialize();

                wchar_t const *dummy_args[] = {L"Python", NULL};
                wchar_t const **argv = dummy_args;
                int argc = sizeof(dummy_args) / sizeof(dummy_args[0]) - 1;

                PySys_SetArgv(argc, const_cast<wchar_t **>(argv));

#ifndef WITHOUT_NUMPY
                import_numpy(); // initialize numpy C-API
#endif

                PyObject *matplotlibname = PyString_FromString("matplotlib");
                PyObject *pyplotname = PyString_FromString("matplotlib.pyplot");
                PyObject *cmname = PyString_FromString("matplotlib.cm");
                PyObject *pylabname = PyString_FromString("pylab");
                if (!pyplotname || !matplotlibname || !cmname || !pylabname) {
                    throw std::runtime_error("couldnt create string");
                }

                PyObject *matplotlib = PyImport_Import(matplotlibname);
                Py_DECREF(matplotlibname);
                if (!matplotlib) {
                    PyErr_Print();
                    throw std::runtime_error("Error loading module matplotlib!");
                }

                // matplotlib.use() must be called *before* pylab, matplotlib.pyplot,
                // or matplotlib.backends is imported for the first time
                if (!s_backend.empty()) {
                    PyObject_CallMethod(matplotlib, const_cast<char *>("use"), const_cast<char *>("s"),
                                        s_backend.c_str());
                }

                PyObject *pylab = PyImport_Import(pylabname);
                Py_DECREF(pylabname);
                if (!pylab) {
                    PyErr_Print();
                    throw std::runtime_error("Error loading module pylab!");
                }

                PyObject *pyplot = PyImport_Import(pyplotname);
                Py_DECREF(pyplotname);
                if (!pyplot) {
                    PyErr_Print();
                    throw std::runtime_error("Error loading module pyplot!");
                }

                s_python_function_arrow = safe_import(pyplot, "arrow");
                s_python_function_show = safe_import(pyplot, "show");
                s_python_function_close = safe_import(pyplot, "close");
                s_python_function_draw = safe_import(pyplot, "draw");
                s_python_function_pause = safe_import(pyplot, "pause");
                s_python_function_save = safe_import(pyplot, "savefig");
                s_python_function_figure = safe_import(pyplot, "figure");
                s_python_function_fignum_exists = safe_import(pyplot, "fignum_exists");
                s_python_function_plot = safe_import(pyplot, "plot");
                s_python_function_fill = safe_import(pyplot, "fill");
                s_python_function_fill_between = safe_import(pyplot, "fill_between");
                s_python_function_hist = safe_import(pyplot, "hist");
                s_python_function_scatter = safe_import(pyplot, "scatter");
                s_python_function_boxplot = safe_import(pyplot, "boxplot");
                s_python_function_bar = safe_import(pyplot, "bar");
                s_python_function_barh = safe_import(pyplot, "barh");
                s_python_function_loglog = safe_import(pyplot, "loglog");
                s_python_function_semilogx = safe_import(pyplot, "semilogx");
                s_python_function_semilogy = safe_import(pyplot, "semilogy");
                s_python_function_text = safe_import(pyplot, "text");
                s_python_function_suptitle = safe_import(pyplot, "suptitle");
                s_python_function_title = safe_import(pyplot, "title");
                s_python_function_axis = safe_import(pyplot, "axis");
                s_python_function_xlabel = safe_import(pyplot, "xlabel");
                s_python_function_ylabel = safe_import(pyplot, "ylabel");
                s_python_function_xticks = safe_import(pyplot, "xticks");
                s_python_function_yticks = safe_import(pyplot, "yticks");
                s_python_function_subplot = safe_import(pyplot, "subplot");
                s_python_function_legend = safe_import(pyplot, "legend");
                s_python_function_ylim = safe_import(pyplot, "ylim");
                s_python_function_xlim = safe_import(pyplot, "xlim");
                s_python_function_imshow = safe_import(pyplot, "imshow");
                s_python_function_annotate = safe_import(pyplot, "annotate");
                s_python_function_clf = safe_import(pyplot, "clf");
                s_python_function_errorbar = safe_import(pyplot, "errorbar");
                s_python_function_tight_layout = safe_import(pyplot, "tight_layout");
                s_python_function_stem = safe_import(pyplot, "stem");
                s_python_function_xkcd = safe_import(pyplot, "xkcd");
                s_python_function_contour = safe_import(pyplot, "contour");
                s_python_function_contourf = safe_import(pyplot, "contourf");
                s_python_function_colorbar = safe_import(pyplot, "colorbar");
                s_python_function_subplots_adjust = safe_import(pyplot, "subplots_adjust");
                s_python_function_spy = safe_import(pyplot, "spy");
                s_python_function_gca = safe_import(pyplot, "gca");
                s_python_function_subplot2grid = safe_import(pyplot, "subplot2grid");
                s_python_function_quiver = safe_import(pyplot, "quiver");

                PyObject *numpy = PyImport_ImportModule("numpy");
                if (!numpy) {
                    throw std::runtime_error("Error loading module numpy!");
                }

                PyObject *rcparams = PyObject_GetAttrString(pyplot, "rcParams");
                if (!rcparams) {
                    throw std::runtime_error("Error getting rcParams");
                }
                s_python_function_rcparams = rcparams;

                // Create empty tuple for function calls
                s_python_empty_tuple = PyTuple_New(0);

                Py_DECREF(matplotlib);
                Py_DECREF(pylab);
                Py_DECREF(pyplot);
                Py_DECREF(numpy);
            }

            ~_interpreter() { Py_Finalize(); }

            static _interpreter &get() {
                static _interpreter ctx;
                return ctx;
            }

          private:
            // Prevent copying
            _interpreter(const _interpreter &) = delete;
            _interpreter &operator=(const _interpreter &) = delete;
        };

        // NumPy type selection templates
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
            const static NPY_TYPES type = NPY_INT16;
        };

        template <> struct select_npy_type<int32_t> {
            const static NPY_TYPES type = NPY_INT32;
        };

        template <> struct select_npy_type<int64_t> {
            const static NPY_TYPES type = NPY_INT64;
        };

        template <> struct select_npy_type<uint8_t> {
            const static NPY_TYPES type = NPY_UINT8;
        };

        template <> struct select_npy_type<uint16_t> {
            const static NPY_TYPES type = NPY_UINT16;
        };

        template <> struct select_npy_type<uint32_t> {
            const static NPY_TYPES type = NPY_UINT32;
        };

        template <> struct select_npy_type<uint64_t> {
            const static NPY_TYPES type = NPY_UINT64;
        };

#ifdef __GNUC__
        template <> struct select_npy_type<long long> {
            const static NPY_TYPES type = NPY_INT64;
        };

        template <> struct select_npy_type<unsigned long long> {
            const static NPY_TYPES type = NPY_UINT64;
        };
#endif

        // Array conversion functions
        template <typename Numeric> PyObject *get_array(const std::vector<Numeric> &v) {
            npy_intp size = v.size();
            npy_intp dims[] = {size};
            PyObject *array = PyArray_SimpleNew(1, dims, select_npy_type<Numeric>::type);

            if (!array) {
                throw std::runtime_error("Could not create numpy array");
            }

            void *data = PyArray_DATA((PyArrayObject *)array);
            std::memcpy(data, v.data(), sizeof(Numeric) * size);

            return array;
        }

        template <typename Numeric> PyObject *get_2darray(const std::vector<std::vector<Numeric>> &v) {
            if (v.empty()) {
                npy_intp dims[] = {0, 0};
                return PyArray_SimpleNew(2, dims, select_npy_type<Numeric>::type);
            }

            npy_intp rows = v.size();
            npy_intp cols = v[0].size();
            npy_intp dims[] = {rows, cols};

            PyObject *array = PyArray_SimpleNew(2, dims, select_npy_type<Numeric>::type);
            if (!array) {
                throw std::runtime_error("Could not create numpy 2D array");
            }

            Numeric *data = static_cast<Numeric *>(PyArray_DATA((PyArrayObject *)array));
            for (npy_intp i = 0; i < rows; ++i) {
                for (npy_intp j = 0; j < cols; ++j) {
                    data[i * cols + j] = v[i][j];
                }
            }

            return array;
        }

        template <typename Numeric> PyObject *get_2darray(const std::vector<Numeric> &v, int rows, int cols) {
            if (v.size() != static_cast<size_t>(rows * cols)) {
                throw std::runtime_error("get_2darray: data size doesn't match dimensions");
            }

            npy_intp dims[] = {rows, cols};
            PyObject *array = PyArray_SimpleNew(2, dims, select_npy_type<Numeric>::type);
            if (!array) {
                throw std::runtime_error("Could not create numpy 2D array");
            }

            void *data = PyArray_DATA((PyArrayObject *)array);
            std::memcpy(data, v.data(), sizeof(Numeric) * v.size());

            return array;
        }

        // String array conversion (special case)
        inline PyObject *get_array(const std::vector<std::string> &strings) {
            PyObject *list = PyList_New(strings.size());
            for (size_t i = 0; i < strings.size(); ++i) {
                PyList_SetItem(list, i, PyString_FromString(strings[i].c_str()));
            }
            return list;
        }

    } // namespace detail

    // Backend selection
    inline void backend(const std::string &name) { detail::s_backend = name; }

    // Interpreter access
    inline detail::_interpreter &get_interpreter() { return detail::_interpreter::get(); }

} // namespace plotter
