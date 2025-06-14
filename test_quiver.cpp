#include <plotter/plotter.hpp>
int main() { 
    std::vector<int> x{1}, y{1}, u{1}, v{1}; 
    plotter::quiver(x,y,u,v); 
    return 0; 
}
