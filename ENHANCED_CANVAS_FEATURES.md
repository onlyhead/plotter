# Enhanced Canvas Features Documentation

## Overview

The Canvas class has been significantly enhanced with three major features as requested:

1. **Subplot Support** - Ability to divide the canvas into multiple subplots
2. **Theme Support** - Built-in dark and light themes with custom color palettes
3. **Infrastructure for Future Features** - Foundation for axis labels, titles, and grid support

## 1. Subplot Support

### Creating Subplots
```cpp
plotter::Canvas canvas(800, 600);
canvas.create_subplots(2, 2);  // Creates a 2x2 grid of subplots
```

### Selecting Active Subplot
```cpp
canvas.subplot(0, 0);  // Select top-left subplot
canvas.plot(x_data, y_data);  // Plot in the selected subplot

canvas.subplot(1, 1);  // Select bottom-right subplot
canvas.plot(x_data2, y_data2);  // Plot in this subplot
```

### Features
- Automatic subplot border rendering
- Independent data scaling per subplot
- Clipped rendering (plots stay within subplot boundaries)
- Support for any grid size (rows × columns)

## 2. Theme Support

### Built-in Themes
```cpp
// Dark theme
canvas.set_dark_theme();

// Light theme  
canvas.set_light_theme();

// Custom theme
plotter::Theme custom_theme = plotter::Theme::dark();
custom_theme.background = plotter::Color("#1E1E1E");
canvas.set_theme(custom_theme);
```

### Theme Properties
Each theme defines:
- `background` - Canvas background color
- `grid_color` - Grid line color (for future grid implementation)
- `text_color` - Text color (for future text rendering)
- `border_color` - Subplot border color
- `plot_colors` - Array of colors for automatic color cycling

### Automatic Color Cycling
When no color is specified for a plot, the canvas automatically cycles through the theme's color palette:
```cpp
canvas.plot(x1, y1);  // Uses first theme color
canvas.plot(x2, y2);  // Uses second theme color
// ... continues cycling through theme colors
```

## 3. Infrastructure for Future Features

### Title and Label Support (Ready for Implementation)
```cpp
canvas.set_title("My Plot Title");
canvas.set_xlabel("X Axis Label");
canvas.set_ylabel("Y Axis Label");
```
*Note: These are stored in the subplot structure but not yet rendered*

### Axis Limits
```cpp
canvas.set_xlim(-10, 10);
canvas.set_ylim(0, 100);
```

### Grid Support (Ready for Implementation)
```cpp
canvas.show_grid(true);
```
*Note: Grid state is stored but not yet rendered*

### Information Queries
```cpp
int subplot_count = canvas.get_subplot_count();
auto [current_row, current_col] = canvas.get_current_subplot_index();
auto [total_rows, total_cols] = canvas.get_subplot_layout();
```

## Internal Architecture

### Subplot Structure
```cpp
struct Subplot {
    int row, col;                    // Position in grid
    int x_offset, y_offset;          // Pixel offset
    int width, height;               // Subplot dimensions
    double x_min, x_max, y_min, y_max;  // Data bounds
    bool has_data;                   // Whether subplot contains data
    std::vector<Operation> operations; // Plot operations
    
    // Infrastructure fields
    std::string title, xlabel, ylabel;
    bool show_grid;
};
```

### Theme Structure
```cpp
struct Theme {
    Color background;
    Color grid_color;
    Color text_color;
    Color border_color;
    std::vector<Color> plot_colors;
    
    static Theme light();  // Predefined light theme
    static Theme dark();   // Predefined dark theme
};
```

### Rendering Pipeline
1. Clear canvas with background color
2. Draw subplot borders (if multiple subplots)
3. For each subplot:
   - Calculate data bounds
   - Render clipped plot operations
   - Store bounds for future axis rendering

## Example Usage

### Basic Subplot Example
```cpp
plotter::Canvas canvas(400, 300);
canvas.set_dark_theme();
canvas.create_subplots(1, 2);

// Left subplot
canvas.subplot(0, 0);
canvas.set_title("Sine Wave");
canvas.plot(x, sine_data);

// Right subplot  
canvas.subplot(0, 1);
canvas.set_title("Cosine Wave");
canvas.plot(x, cosine_data);

canvas.save("subplots_demo.png");
```

### Color Cycling Example
```cpp
plotter::Canvas canvas(600, 400);
canvas.set_light_theme();

// Each plot gets a different theme color automatically
canvas.plot(x1, y1);  // First theme color
canvas.plot(x2, y2);  // Second theme color
canvas.plot(x3, y3);  // Third theme color

canvas.save("colors_demo.png");
```

## Backward Compatibility

All existing Canvas functionality remains unchanged:
- `plot(xs, ys, color)` - Still works as before
- `set_background(color)` - Still works
- `save()`, `set_frame()`, `show()` - All unchanged
- Animation support - Fully preserved

## Future Development Ready

The infrastructure is in place for:
1. **Text Rendering** - Title and label strings are stored per subplot
2. **Grid Rendering** - Grid state is tracked per subplot
3. **Axis Rendering** - Data bounds are calculated and stored
4. **Legend Support** - Color information is maintained
5. **Interactive Features** - Subplot selection and management is ready

## Testing

Three demo programs showcase the features:
- `simple_enhanced_test` - Basic theme switching
- `enhanced_demo` - Full subplot and theme demonstration
- Existing demos (`spatial_demo`, `tester`) - Verify backward compatibility
