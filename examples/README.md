# ImPlot Library Examples

This directory contains simple examples demonstrating the usage of the ImPlot library integrated with the plotter framework.

## Available Examples

### 1. `data_test.cpp` - Basic Data Processing
A console application that demonstrates:
- Mathematical function generation (sin, cos, exponential decay)
- Random data generation for scatter plots
- Basic statistical calculations
- Data range operations similar to ImPlot ranges

**Build and run:**
```bash
cd build
make data_test
./data_test
```

### 2. `implot_types_test.cpp` - ImPlot Data Structures
Tests the core ImPlot data structures:
- `ImPlotPoint`: 2D points with double precision
- `ImPlotRange`: Min/max range with utility functions
- `ImPlotRect`: 2D rectangular bounds
- Data bounds calculation for plotting datasets

**Build and run:**
```bash
cd build
make implot_types_test
./implot_types_test
```

### 3. `comprehensive_test.cpp` - Complete ImPlot Simulation
A comprehensive test that simulates a complete plotting session:
- Multiple plot types (line, scatter, bar charts)
- Plot bounds calculation and management
- Viewport and range queries
- API structure demonstration
- Interactive plot testing simulation

**Build and run:**
```bash
cd build
make comprehensive_test
./comprehensive_test
```

## Building All Examples

To build all examples at once:

```bash
# Configure with examples enabled
cd /path/to/plotter
mkdir -p build && cd build
cmake .. -DPLOTTER_BUILD_EXAMPLES=ON

# Build all examples
make

# List available executables
ls -la *_test data_test
```

## Example Output

### Data Test
```
Starting Simple Data Processing Test...
Generated 100 data points for plotting:

Sample data points:
x		sin(x)		cos(x)		exp_decay
0.000		0.000		1.000		0.000
0.100		0.100		0.995		0.197
...

Data statistics:
sin(x) range: [-1.000, 1.000]
cos(x) range: [-1.000, 1.000]

Data processing test completed successfully!
```

### ImPlot Types Test
```
Testing ImPlotPoint...
Point 1: (1, 2)
Point 2: (3, 4)

Testing ImPlotRange...
Range: [0, 10]
Range size: 10
Contains 5.0: Yes

ImPlot types test completed successfully!
```

## Library Features Demonstrated

1. **Data Structures**: Core ImPlot types (`ImPlotPoint`, `ImPlotRange`, `ImPlotRect`)
2. **Data Generation**: Mathematical functions, random data, statistical datasets
3. **Bounds Calculation**: Automatic plot bounds computation
4. **Range Operations**: Point containment, clamping, size calculations
5. **API Structure**: Complete ImPlot API overview and usage patterns

## Next Steps

These examples demonstrate the foundational data structures and operations of the ImPlot library. The next step would be to create a full GUI application that integrates with ImGui and OpenGL for actual visual plotting.

For actual visual plotting, you would need:
1. ImGui context with OpenGL/GLFW backend
2. ImPlot context initialization
3. Render loop with ImPlot drawing calls
4. Window management and user interaction

## Notes

- The examples are designed to work with the current ImPlot header-only library structure
- All examples are console-based for easy testing and debugging
- The data generated in these examples is suitable for use with actual ImPlot rendering functions
- Error handling demonstrates proper usage of ImPlot data structures

## Troubleshooting

If you encounter build issues:

1. **Header include errors**: The examples use selective header inclusion to avoid circular dependencies
2. **Missing dependencies**: Ensure ImGui is properly configured in CMake
3. **Build configuration**: Make sure `PLOTTER_BUILD_EXAMPLES=ON` is set

For actual GUI plotting, additional dependencies are needed:
- GLFW3 for window management
- OpenGL for rendering
- Platform-specific backends (see ImGui documentation)
