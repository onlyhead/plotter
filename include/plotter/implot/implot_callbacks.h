#pragma once

#include "implot_types.h"

//-----------------------------------------------------------------------------
// [SECTION] Callbacks
//-----------------------------------------------------------------------------

// Callback signature for axis tick label formatter.
typedef int (*ImPlotFormatter)(double value, char *buff, int size, void *user_data);

// Callback signature for data getter.
typedef ImPlotPoint (*ImPlotGetter)(int idx, void *user_data);

// Callback signature for axis transform.
typedef double (*ImPlotTransform)(double value, void *user_data);
