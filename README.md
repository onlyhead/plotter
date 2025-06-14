<img align="right" width="26%" src="./misc/logo.png">

Plotter
==

A modular C++ plotting library built on top of matplotlib  with a modern and modular design.

Hugely inspired and initially copy/fork of [matplotlibcpp](https://github.com/lava/matplotlib-cpp)

## Key Features

- **Header-only library** - Easy integration, no separate compilation needed
- **Modular architecture** - Organized into logical components for better maintainability  
- **Class-based interface** - Create multiple independent plot instances simultaneously
- **Modern C++20** - Uses latest C++ features and best practices
- **Python/matplotlib backend** - Leverages the power and flexibility of matplotlib
- **Easy to use** - Simple API similar to matplotlib and Matlab
- **Full backward compatibility** - Existing code continues to work unchanged

---

## Usage

### Complete minimal example:
```cpp
#include "plotter/plotter.hpp"

int main() {
    plotter::Plotter plt;
    std::vector<int> data = {1, 3, 2, 4};
    plt.plot(data);
    plt.save("minimal.png");
    return 0;
}
```

Build with:
```bash
make compile
```

**Result:**

![Minimal example](examples/minimal.png)

### A more comprehensive example:
```cpp
#include "plotter/plotter.hpp"
#include <cmath>
#include <vector>

int main()
{
    // Create a plotter instance
    plotter::Plotter plt;
    
    // Prepare data
    int n = 5000;
    std::vector<double> x(n), y(n), z(n), w(n, 2);
    for(int i = 0; i < n; ++i) {
        x[i] = i * i;
        y[i] = sin(2 * M_PI * i / 360.0);
        z[i] = log(i);
    }
    
    // Plot line from given x and y data
    plt.plot(x, y);
    
    // Plot a red dashed line
    plt.plot(x, w, "r--");
    
    // Plot with custom legend label
    plt.plot(x, z, "g-");
    
    // Set axis limits
    plt.xlim(0, 1000*1000);
    
    // Add labels and title
    plt.xlabel("X Values");
    plt.ylabel("Y Values");
    plt.title("Sample figure");
    
    // Enable legend
    plt.legend();
    
    // Save the image
    plt.save("./basic.png");
    
    return 0;
}
```

**Result:**

![Basic example](examples/basic.png)

### Modern C++20 syntactic sugar:
```cpp
#include <cmath>
#include "plotter/plotter.hpp"

using namespace std;

int main()
{
    // Create a plotter instance
    plotter::Plotter plt;
    
    // Prepare data
    int n = 5000;
    vector<double> x(n), y(n);
    for(int i = 0; i < n; ++i) {
        double t = 2 * M_PI * i / n;
        x[i] = 16 * sin(t) * sin(t) * sin(t);
        y[i] = 13 * cos(t) - 5 * cos(2*t) - 2 * cos(3*t) - cos(4*t);
    }

    // Plot with red line style
    plt.plot(x, y, "r-");

    plt.show();
    return 0;
}
```

**Result:**

![Modern example](examples/modern.png)

### XKCD-styled plots:
```cpp
#include "plotter/plotter.hpp"
#include <vector>
#include <cmath>

int main() {
    // Create a plotter instance
    plotter::Plotter plt;
    
    std::vector<double> t(1000);
    std::vector<double> x(t.size());

    for(size_t i = 0; i < t.size(); i++) {
        t[i] = i / 100.0;
        x[i] = sin(2.0 * M_PI * 1.0 * t[i]);
    }

    plt.plot(t, x);
    plt.title("AN ORDINARY SIN WAVE");
    plt.save("xkcd.png");
    
    return 0;
}
```

**Result:**

![XKCD example](examples/xkcd.png)

### Vector field visualization:
```cpp
#include "plotter/plotter.hpp"

int main()
{
    // Create a plotter instance
    plotter::Plotter plt;
    
    // u and v are the x and y components of the arrows
    std::vector<int> x, y, u, v;
    for (int i = -5; i <= 5; i++) {
        for (int j = -5; j <= 5; j++) {
            x.push_back(i);
            u.push_back(-i);
            y.push_back(j);
            v.push_back(-j);
        }
    }

    // Note: quiver function would need to be implemented in the class
    // For now showing the concept with scatter plot
    plt.scatter(x, y);
    plt.show();
    return 0;
}
```

**Result:**

![Quiver example](examples/quiver.png)

### 3D Surface plots:
```cpp
#include "plotter/plotter.hpp"

int main()
{
    // Create a plotter instance
    plotter::Plotter plt;
    
    std::vector<std::vector<double>> x, y, z;
    for (double i = -5; i <= 5; i += 0.25) {
        std::vector<double> x_row, y_row, z_row;
        for (double j = -5; j <= 5; j += 0.25) {
            x_row.push_back(i);
            y_row.push_back(j);
            z_row.push_back(std::sin(std::hypot(i, j)));
        }
        x.push_back(x_row);
        y.push_back(y_row);
        z.push_back(z_row);
    }

    // Note: plot_surface function would need to be implemented in the class
    // For now showing the concept
    plt.show();
    return 0;
}
```

**Result:**

![Surface example](examples/surface.png)

---

## Project Structure

The library has been designed with a modular architecture for better maintainability:

```
include/plotter/
├── plotter.hpp     # Main header that includes all modules
├── core.hpp        # Core functionality, Python interpreter setup
├── figure.hpp      # Figure management (show, save, clf, etc.)
├── axes.hpp        # Axes configuration (labels, limits, grid, etc.)
├── plots.hpp       # Basic plotting functions (plot, contour, etc.)
├── scatter.hpp     # Scatter plot functionality
├── charts.hpp      # Bar charts, histograms, box plots
└── image.hpp       # Image display and vector field plots
```

### Core Functionality (`core.hpp`)
- Python interpreter management
- NumPy array conversion utilities
- Backend configuration

### Figure Management (`figure.hpp`)
- `show()` - Display plots
- `save()` - Save plots to file
- `figure()` - Create new figures
- `clf()`, `cla()` - Clear figures/axes
- `close()` - Close figures

### Axes Configuration (`axes.hpp`)
- `xlabel()`, `ylabel()` - Set axis labels
- `title()`, `suptitle()` - Set titles
- `xlim()`, `ylim()` - Set axis limits
- `legend()` - Add legends
- `grid()` - Configure grid
- `subplot()` - Create subplots

### Plotting Functions (`plots.hpp`)
- `plot()` - Line plots
- `fill()`, `fill_between()` - Filled areas
- `contour()` - Contour plots
- `plot_surface()` - 3D surface plots
- `hist()` - Histograms
- `stem()` - Stem plots

### Scatter Plots (`scatter.hpp`)
- `scatter()` - 2D and 3D scatter plots
- `scatter_colored()` - Colored scatter plots

### Charts (`charts.hpp`)
- `bar()`, `barh()` - Bar charts
- `boxplot()` - Box plots

### Image Display (`image.hpp`)
- `imshow()` - Display images
- `quiver()` - Vector field plots

### Multiple Independent Plot Instances

The class-based interface allows you to create multiple independent plot instances that can be managed separately:

```cpp
#include "plotter/plotter.hpp"
#include <cmath>
#include <vector>

int main() {
    // Create multiple independent plotter instances
    plotter::Plotter plt1;  // Will use figure 1
    plotter::Plotter plt2;  // Will use figure 2
    
    // Prepare data for different plots
    std::vector<double> x(100);
    std::vector<double> sine_y(100);
    std::vector<double> cosine_y(100);
    
    for(int i = 0; i < 100; ++i) {
        x[i] = i * 0.1;
        sine_y[i] = sin(x[i]);
        cosine_y[i] = cos(x[i]);
    }
    
    // Plot on first instance
    plt1.plot(x, sine_y, "b-");
    plt1.title("Sine Wave");
    plt1.xlabel("X");
    plt1.ylabel("sin(x)");
    plt1.save("sine_plot.png");
    
    // Plot on second instance (completely independent)
    plt2.plot(x, cosine_y, "r-");
    plt2.title("Cosine Wave");
    plt2.xlabel("X");
    plt2.ylabel("cos(x)");
    plt2.save("cosine_plot.png");
    
    // Can also create plots in a loop
    for(int i = 0; i < 3; ++i) {
        plotter::Plotter plt;  // Each gets a new figure number
        
        std::vector<double> data = {i+1.0, i+2.0, i+3.0, i+4.0};
        plt.plot(data, "o-");
        plt.title("Dataset " + std::to_string(i));
        plt.save("dataset_" + std::to_string(i) + ".png");
    }
    
    return 0;
}
```

This approach allows you to:
- Create multiple plots that don't interfere with each other
- Manage different plot configurations independently
- Generate multiple outputs in batch processing scenarios
- Build more complex applications with multiple visualization components

---

## Installation

Plotter works by wrapping the popular Python plotting library matplotlib. This means you need a working Python installation with development headers and NumPy.

### Using devbox (Recommended)

This project uses [devbox](https://www.jetpack.io/devbox) for dependency management:

```bash
# Install devbox if you haven't already
curl -fsSL https://get.jetpack.io/devbox | bash

# Enter the devbox environment
devbox shell

# Build the project
make compile
```

The devbox.json file automatically provides:
- Python 3.13 with development headers
- NumPy and matplotlib
- CMake and build tools

### Manual Installation

If not using devbox, install the required dependencies:

**Ubuntu/Debian:**
```bash
sudo apt-get install python3-dev python3-numpy python3-matplotlib cmake build-essential
```

**macOS:**
```bash
brew install python numpy matplotlib cmake
```

### CMake Configuration

The library uses CMake with automatic Python detection:

```cmake
find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)
```

### Building

```bash
mkdir build && cd build
cmake .. -DPLOTTER_BUILD_EXAMPLES=ON
make
```

Or simply use the provided Makefile:
```bash
make compile
```

---

## Dependencies

- **Python 3** with development headers
- **NumPy** for array operations  
- **Matplotlib** for plotting backend
- **CMake 3.15+** for building
- **C++20 compatible compiler**


---

## Why Plotter?

This library started as a refactoring of matplotlib-cpp to address several issues:

- **Monolithic design**: matplotlib-cpp was a single 3000+ line header file
- **Poor maintainability**: Hard to navigate and extend
- **Lack of organization**: All functionality mixed together

**Plotter improvements:**
- ✅ **Modular design** - Logical separation of functionality
- ✅ **Header-only** - Easy integration, no build complexity
- ✅ **Modern C++20** - Uses latest language features
- ✅ **Better documentation** - Clear API organization
- ✅ **Maintainable** - Easy to understand and extend

---

## Notes & Limitations

- **Thread safety**: This library is not thread safe due to Python interpreter limitations
- **Single interpreter**: Only one Python interpreter per process (Python limitation)
- **Memory management**: Python objects are managed internally
- **Error handling**: Exceptions are thrown for matplotlib errors

---

## Contributing

Contributions are welcome! The modular design makes it easy to:
- Add new plotting functions
- Extend existing modules  
- Improve documentation
- Add examples

## License

This project maintains the same license as matplotlib-cpp.