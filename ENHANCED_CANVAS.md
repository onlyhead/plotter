# Enhanced Canvas with Pigment and Concord Integration

This enhanced Canvas implementation integrates two powerful libraries:

- **Pigment**: Advanced color management and manipulation
- **Concord**: Spatial geometry and grid operations

## Key Features

### Pigment Integration
- Rich color support with `pigment::RGB` 
- Hex color string parsing (`#FF0000`, `#00FF00AA`)
- Color arithmetic operations (addition, subtraction, scaling)
- Alpha transparency support
- Built-in color conversion methods

### Concord Integration  
- Grid-based spatial structure for pixel management
- Efficient 2D coordinate system
- Row/column indexing for spatial operations
- Spatial geometry operations

## Usage Examples

### Basic Plotting with Named Colors
```cpp
plotter::Canvas canvas(400, 300);

// Use Pigment colors with hex strings
plotter::Color red("#FF0000");
plotter::Color blue("#0000FF");

// Plot data with different colors
canvas.plot(x_data, y_data, red);
canvas.plot_with_named_color(x2, y2, "green");

canvas.save("output.png");
```

### Color Manipulation
```cpp
// Create colors from hex strings
plotter::Color color1("#FF0000");  // Red
plotter::Color color2("#00FF00");  // Green

// Mix colors using Pigment arithmetic
plotter::Color mixed = color1 + color2;  // Yellow

// Convert back to hex
std::cout << "Mixed color: " << mixed.to_hex() << std::endl;
```

### Pixel-Level Operations with Grid
```cpp
plotter::Canvas canvas(500, 500);

// Set individual pixels using Concord grid
for (int i = 0; i < 100; ++i) {
    plotter::Color pixel_color("#FFA500");  // Orange
    canvas.set_pixel_color(i, i, pixel_color);
}

// Query pixel colors
plotter::Color current = canvas.get_pixel(50, 50);
```

### Animated Canvas
```cpp
plotter::Canvas canvas(400, 300, true);  // Enable animation

for (int frame = 0; frame < 20; ++frame) {
    // Set dynamic background
    canvas.set_background(plotter::Color(200, 200, 255));
    
    // Plot animated data
    canvas.plot(x_data, y_data, plotter::Color("#FF6B6B"));
    
    // Add frame to animation
    canvas.set_frame();
}

// Save as animated GIF
canvas.save("animation.gif", 10);  // 10 centisecond delay
```

## Enhanced Methods

### Color Management
- `set_background(const Color& bg)` - Set background using Pigment color
- `plot_with_named_color(xs, ys, color_name)` - Plot with predefined color names

### Pixel Operations  
- `set_pixel_color(x, y, color)` - Set pixel using both grid and buffer
- `get_pixel(x, y)` - Query pixel color from grid

### Spatial Features
- Integration with Concord's spatial coordinate system
- Grid-based pixel indexing for efficient operations
- Support for spatial transformations and coordinate mapping

## Demo Programs

Three demo programs showcase the enhanced functionality:

1. **tester.cpp** - Basic color and plotting functionality
2. **advanced_demo.cpp** - Animated canvas with complex color effects  
3. **spatial_demo.cpp** - Spatial grid operations and color mixing

## Building

The enhanced canvas builds with the existing CMake configuration:

```bash
mkdir -p build && cd build
cmake .. -DPLOTTER_BUILD_EXAMPLES=ON
make -j4
```

## Dependencies

- **Concord 2.0.1**: Spatial geometry and grid operations
- **Pigment 0.3.1**: Color management and manipulation
- **STB Image**: Image writing (existing)
- **GIF-H**: GIF animation (existing)

Both Pigment and Concord are automatically fetched and built by CMake using FetchContent.
