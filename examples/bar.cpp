#define _USE_MATH_DEFINES

#include <iostream>
#include <plotter/plotter.hpp>
#include <string>
namespace plt = plotter;

int main(int argc, char **argv) {
    std::vector<int> test_data;
    for (int i = 0; i < 20; i++) {
        test_data.push_back(i);
    }

    plt::bar(test_data);
    plt::show();

    return (0);
}
