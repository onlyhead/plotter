# Modular Canvas Architecture

## 🏗️ **Modular Design Overview**

The Canvas class has been refactored into a clean, modular architecture while maintaining 100% backward compatibility. The Canvas class now delegates to specialized managers and components.

## 📁 **File Structure**

```
include/canvas/
├── canvas.hpp                     # Main public header (unchanged interface)
├── modular_canvas.hpp            # New modular Canvas implementation
├── core/                         # Core data structures
│   ├── types.hpp                 # Basic types and forward declarations
│   ├── theme.hpp                 # Theme definitions
│   └── subplot.hpp               # Subplot structure
├── managers/                     # Component managers
│   ├── theme_manager.hpp         # Theme and palette management
│   └── subplot_manager.hpp       # Subplot grid management
├── rendering/                    # Rendering system
│   └── renderer.hpp              # Drawing and rendering logic
└── plotting/                     # Plotting interface
    └── plot_interface.hpp        # Named color plotting methods
```

## 🔧 **Component Breakdown**

### **Core Components** (`core/`)

#### `types.hpp`
- Basic type definitions (`Color`, `Operation`)
- Forward declarations
- Common includes

#### `theme.hpp` 
- `Theme` struct with predefined themes
- Light, Dark, and Vibrant theme definitions
- Pigment color integration

#### `subplot.hpp`
- `Subplot` structure
- Position, bounds, and metadata
- Infrastructure for future features

### **Managers** (`managers/`)

#### `ThemeManager`
- **Responsibilities**: Theme switching, palette management, color cycling
- **Key Methods**:
  - `set_dark_theme()`, `set_light_theme()`, `set_vibrant_theme()`
  - `set_material_design_palette()`, `set_warm_palette()`, etc.
  - `get_next_plot_color(index)` - automatic color cycling

#### `SubplotManager`  
- **Responsibilities**: Subplot grid management, navigation, data storage
- **Key Methods**:
  - `create_subplots(rows, cols)` - create grid layout
  - `set_current_subplot(row, col)` - navigate between subplots
  - `get_current_subplot()` - access current subplot data
  - `clear_all_operations()` - clear plot data

### **Rendering** (`rendering/`)

#### `Renderer`
- **Responsibilities**: Canvas clearing, drawing primitives, clipping
- **Key Methods**:
  - `clear_canvas()` - fill with background color
  - `draw_subplot_borders()` - render grid separators
  - `render_subplot()` - transform data and draw plots
  - `clip_line_to_rect()` - Cohen-Sutherland line clipping

### **Plotting Interface** (`plotting/`)

#### `PlotInterface`
- **Responsibilities**: Named color plotting, color name resolution
- **Key Methods**:
  - `plot_red()`, `plot_blue()`, etc. - convenience plotting
  - `plot_with_named_color()` - string-based color selection
  - Static utility methods for operation management

## 🎯 **Canvas Class Architecture**

The main `Canvas` class is now a **facade** that coordinates between components:

```cpp
class Canvas {
private:
    // Core rendering data
    int width, height;
    std::vector<uint8_t> pixels;
    std::unique_ptr<concord::Grid<Color>> grid;
    
    // Component managers
    ThemeManager theme_manager_;           // Handles themes and palettes
    SubplotManager subplot_manager_;       // Handles subplot grid
    std::unique_ptr<Renderer> renderer_;   // Handles drawing operations

public:
    // Public API delegates to appropriate manager
    void set_dark_theme() { 
        theme_manager_.set_dark_theme();
        renderer_->set_background_color(theme_manager_.get_background_color());
    }
    
    void create_subplots(int rows, int cols) {
        subplot_manager_.create_subplots(rows, cols);
    }
    
    void plot_red(const std::vector<double>& xs, const std::vector<double>& ys) {
        Subplot& subplot = subplot_manager_.get_current_subplot();
        PlotInterface::plot_red(subplot.operations, xs, ys);
        subplot.has_data = true;
    }
};
```

## ✅ **Benefits of Modular Design**

### **1. Separation of Concerns**
- **Theme management** isolated in `ThemeManager`
- **Subplot logic** isolated in `SubplotManager`  
- **Rendering** isolated in `Renderer`
- **Plotting interface** isolated in `PlotInterface`

### **2. Easy Testing**
- Each component can be unit tested independently
- Mock managers can be injected for testing
- Rendering logic separated from data management

### **3. Future Extensibility**
- Add new managers (e.g., `AnimationManager`, `LegendManager`)
- Extend rendering without touching plotting logic
- Add new plot types in separate files

### **4. Maintainability**
- Small, focused files (50-200 lines each)
- Clear responsibilities for each component
- Easy to locate and modify specific functionality

### **5. Backward Compatibility**
- **100% API compatibility** - all existing code works unchanged
- Same public interface as before
- Same performance characteristics

## 🚀 **Future Extensions Made Easy**

### **Adding New Features**

**Legend Support:**
```cpp
// Add: managers/legend_manager.hpp
class LegendManager {
    void add_legend_entry(const std::string& label, const Color& color);
    void render_legend(Renderer& renderer);
};
```

**Animation Support:**
```cpp
// Add: managers/animation_manager.hpp
class AnimationManager {
    void enable_animation(int frame_duration);
    void capture_frame();
    void save_gif(const std::string& filename);
};
```

**Text Rendering:**
```cpp
// Add: rendering/text_renderer.hpp
class TextRenderer {
    void render_title(const std::string& title, int x, int y);
    void render_axis_labels(const Subplot& subplot);
};
```

### **Adding New Plot Types**

```cpp
// Add: plotting/advanced_plots.hpp
class AdvancedPlots {
    static void plot_histogram(std::vector<Operation>& ops, const std::vector<double>& data);
    static void plot_scatter(std::vector<Operation>& ops, const std::vector<double>& x, const std::vector<double>& y);
    static void plot_bar_chart(std::vector<Operation>& ops, const std::vector<double>& values);
};
```

## 📊 **Performance Impact**

- **Compilation**: Faster due to smaller headers and reduced dependencies
- **Runtime**: Minimal overhead from delegation (inlined function calls)
- **Memory**: Same memory usage as before (managers store minimal state)
- **Maintainability**: Significantly improved due to modular structure

## 🎯 **Migration Path**

**Existing Code**: No changes required! ✅
```cpp
plotter::Canvas canvas(800, 600);
canvas.set_dark_theme();
canvas.create_subplots(2, 2);
canvas.subplot(0, 0);
canvas.plot_red(x, y);
canvas.save("output.png");
```

**New Features**: Use the same API ✅
```cpp
// Everything works exactly the same
canvas.set_material_design_palette();
canvas.set_vibrant_theme();
canvas.plot_with_named_color(x, y, "crimson");
```

The modular architecture provides a **solid foundation** for future development while keeping the same simple, intuitive API you designed! 🚀
