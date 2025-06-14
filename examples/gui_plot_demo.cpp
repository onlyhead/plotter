#include <iostream>
#include <vector>
#include <cmath>
#include <random>

// Include ImGui and backends
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// Include ImPlot types first
#include "plotter/implot/implot_types.h"
#include "plotter/implot/implot_enums.h"
#include "plotter/implot/implot_defines.h"

// Include ImPlot core functions (we'll implement basic ones)
namespace ImPlot {
    // Forward declarations of functions we'll implement
    bool CreateContext();
    void DestroyContext();
    bool BeginPlot(const char* title, const ImVec2& size = ImVec2(-1,0), int flags = 0);
    void EndPlot();
    void PlotLine(const char* label, const float* x_data, const float* y_data, int count);
    void PlotScatter(const char* label, const float* x_data, const float* y_data, int count);
}

// OpenGL and GLFW
#include <GL/gl.h>
#include <GLFW/glfw3.h>

// Simple implementation of basic ImPlot functions for demo
namespace ImPlot {
    static bool g_context_created = false;
    static bool g_plot_active = false;
    static ImVec2 g_plot_pos, g_plot_size;
    static ImPlotRect g_current_bounds;

    bool CreateContext() {
        g_context_created = true;
        std::cout << "ImPlot context created" << std::endl;
        return true;
    }

    void DestroyContext() {
        g_context_created = false;
        std::cout << "ImPlot context destroyed" << std::endl;
    }

    bool BeginPlot(const char* title, const ImVec2& size, int flags) {
        if (!g_context_created) return false;
        
        // Use ImGui to create a child window for the plot
        ImGui::BeginChild(title, size, true, ImGuiWindowFlags_NoScrollbar);
        
        g_plot_active = true;
        g_plot_pos = ImGui::GetCursorScreenPos();
        g_plot_size = ImGui::GetContentRegionAvail();
        
        // Set up default bounds
        g_current_bounds = ImPlotRect(-1, 1, -1, 1);
        
        // Draw plot background
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        ImVec2 p_min = g_plot_pos;
        ImVec2 p_max = ImVec2(g_plot_pos.x + g_plot_size.x, g_plot_pos.y + g_plot_size.y);
        
        // Background
        draw_list->AddRectFilled(p_min, p_max, IM_COL32(30, 30, 30, 255));
        
        // Grid lines
        const int grid_lines = 10;
        for (int i = 0; i <= grid_lines; ++i) {
            float x = p_min.x + (p_max.x - p_min.x) * i / grid_lines;
            float y = p_min.y + (p_max.y - p_min.y) * i / grid_lines;
            draw_list->AddLine(ImVec2(x, p_min.y), ImVec2(x, p_max.y), IM_COL32(60, 60, 60, 255));
            draw_list->AddLine(ImVec2(p_min.x, y), ImVec2(p_max.x, y), IM_COL32(60, 60, 60, 255));
        }
        
        // Border
        draw_list->AddRect(p_min, p_max, IM_COL32(100, 100, 100, 255));
        
        return true;
    }

    void EndPlot() {
        if (!g_plot_active) return;
        
        g_plot_active = false;
        ImGui::EndChild();
    }

    ImVec2 PlotToPixels(float x, float y) {
        float px = g_plot_pos.x + (x - g_current_bounds.X.Min) / g_current_bounds.X.Size() * g_plot_size.x;
        float py = g_plot_pos.y + g_plot_size.y - (y - g_current_bounds.Y.Min) / g_current_bounds.Y.Size() * g_plot_size.y;
        return ImVec2(px, py);
    }

    void PlotLine(const char* label, const float* x_data, const float* y_data, int count) {
        if (!g_plot_active || count < 2) return;
        
        // Calculate bounds from data
        float x_min = x_data[0], x_max = x_data[0];
        float y_min = y_data[0], y_max = y_data[0];
        
        for (int i = 1; i < count; ++i) {
            x_min = std::min(x_min, x_data[i]);
            x_max = std::max(x_max, x_data[i]);
            y_min = std::min(y_min, y_data[i]);
            y_max = std::max(y_max, y_data[i]);
        }
        
        // Add some padding
        float x_padding = (x_max - x_min) * 0.1f;
        float y_padding = (y_max - y_min) * 0.1f;
        g_current_bounds = ImPlotRect(x_min - x_padding, x_max + x_padding, 
                                      y_min - y_padding, y_max + y_padding);
        
        // Draw the line
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        ImU32 color = IM_COL32(255, 100, 100, 255); // Red color
        
        for (int i = 0; i < count - 1; ++i) {
            ImVec2 p1 = PlotToPixels(x_data[i], y_data[i]);
            ImVec2 p2 = PlotToPixels(x_data[i + 1], y_data[i + 1]);
            draw_list->AddLine(p1, p2, color, 2.0f);
        }
        
        // Add label to legend (simple text display)
        ImGui::Text("%s", label);
    }

    void PlotScatter(const char* label, const float* x_data, const float* y_data, int count) {
        if (!g_plot_active || count < 1) return;
        
        // Calculate bounds from data
        float x_min = x_data[0], x_max = x_data[0];
        float y_min = y_data[0], y_max = y_data[0];
        
        for (int i = 1; i < count; ++i) {
            x_min = std::min(x_min, x_data[i]);
            x_max = std::max(x_max, x_data[i]);
            y_min = std::min(y_min, y_data[i]);
            y_max = std::max(y_max, y_data[i]);
        }
        
        // Add some padding
        float x_padding = (x_max - x_min) * 0.1f;
        float y_padding = (y_max - y_min) * 0.1f;
        g_current_bounds = ImPlotRect(x_min - x_padding, x_max + x_padding, 
                                      y_min - y_padding, y_max + y_padding);
        
        // Draw scatter points
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        ImU32 color = IM_COL32(100, 255, 100, 255); // Green color
        
        for (int i = 0; i < count; ++i) {
            ImVec2 p = PlotToPixels(x_data[i], y_data[i]);
            draw_list->AddCircleFilled(p, 3.0f, color);
        }
        
        // Add label to legend
        ImGui::Text("%s", label);
    }
}

static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main() {
    std::cout << "Starting ImPlot GUI Demo..." << std::endl;
    
    // Setup GLFW
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    
    // Create window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "ImPlot GUI Demo", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    
    // Generate sample data
    const int data_size = 100;
    std::vector<float> x_data(data_size);
    std::vector<float> sin_data(data_size);
    std::vector<float> cos_data(data_size);
    std::vector<float> exp_data(data_size);
    
    for (int i = 0; i < data_size; ++i) {
        x_data[i] = i * 0.1f;
        sin_data[i] = std::sin(x_data[i]);
        cos_data[i] = std::cos(x_data[i]);
        exp_data[i] = std::exp(-x_data[i] * 0.1f) * std::sin(x_data[i] * 2.0f);
    }
    
    // Generate scatter data
    std::vector<float> scatter_x(50), scatter_y(50);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<float> dist(0.0f, 1.0f);
    
    for (int i = 0; i < 50; ++i) {
        scatter_x[i] = dist(gen);
        scatter_y[i] = dist(gen);
    }
    
    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        // Main window
        ImGui::Begin("ImPlot GUI Demo");
        
        ImGui::Text("ImPlot Library GUI Demonstration");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 
                   1000.0f / io.Framerate, io.Framerate);
        ImGui::Separator();
        
        // Plot 1: Trigonometric functions
        ImGui::Text("Trigonometric Functions");
        if (ImPlot::BeginPlot("Trig Functions", ImVec2(-1, 300))) {
            ImPlot::PlotLine("sin(x)", x_data.data(), sin_data.data(), data_size);
            ImPlot::PlotLine("cos(x)", x_data.data(), cos_data.data(), data_size);
            ImPlot::EndPlot();
        }
        
        ImGui::Separator();
        
        // Plot 2: Exponential decay
        ImGui::Text("Exponential Decay");
        if (ImPlot::BeginPlot("Exp Decay", ImVec2(-1, 300))) {
            ImPlot::PlotLine("exp(-0.1x) * sin(2x)", x_data.data(), exp_data.data(), data_size);
            ImPlot::EndPlot();
        }
        
        ImGui::Separator();
        
        // Plot 3: Scatter plot
        ImGui::Text("Scatter Plot");
        if (ImPlot::BeginPlot("Random Scatter", ImVec2(-1, 300))) {
            ImPlot::PlotScatter("Random Points", scatter_x.data(), scatter_y.data(), 50);
            ImPlot::EndPlot();
        }
        
        ImGui::End();
        
        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        glfwSwapBuffers(window);
    }
    
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();
    
    glfwDestroyWindow(window);
    glfwTerminate();
    
    std::cout << "ImPlot GUI Demo completed!" << std::endl;
    return 0;
}
