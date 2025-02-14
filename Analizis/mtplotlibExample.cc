#include "matplotlibcpp.h"
#include <iostream>
#include <vector>

namespace plt = matplotlibcpp;

int main() {
    // Datos para graficar
    std::vector<double> x, y;
    for (double i = 0; i < 10; i += 0.1) {
        x.push_back(i);
        y.push_back(std::sin(i));
    }

    // Crear la gráfica
    plt::plot(x, y, "r-"); // Línea roja

    // Mostrar la gráfica
    plt::show();

    return 0;
}
