#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <pybind11/pybind11.h>

namespace py = pybind11;

// Función para ordenar con Merge Sort
void merge_sort(std::vector<int>& arr) {
    if (arr.size() > 1) {
        size_t mid = arr.size() / 2;
        std::vector<int> left(arr.begin(), arr.begin() + mid);
        std::vector<int> right(arr.begin() + mid, arr.end());

        merge_sort(left);
        merge_sort(right);

        size_t i = 0, j = 0, k = 0;
        while (i < left.size() && j < right.size()) {
            if (left[i] < right[j]) {
                arr[k] = left[i];
                i++;
            } else {
                arr[k] = right[j];
                j++;
            }
            k++;
        }

        while (i < left.size()) {
            arr[k] = left[i];
            i++;
            k++;
        }

        while (j < right.size()) {
            arr[k] = right[j];
            j++;
            k++;
        }
    }
}

// Función para medir el tiempo de ejecución y devolver los tiempos individuales para 10 pruebas
std::vector<std::vector<double>> measure_sort_times(const std::vector<int>& sizes) {
    std::vector<std::vector<double>> all_times;

    for (int size : sizes) {
        std::vector<double> times_for_size;

        for (int i = 0; i < 10; ++i) {  // Realizar 10 pruebas para cada tamaño
            std::vector<int> arr(size);
            std::generate(arr.begin(), arr.end(), [](){ return rand() % 100; });

            auto start = std::chrono::high_resolution_clock::now();
            merge_sort(arr);
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> duration = end - start;
            times_for_size.push_back(duration.count() * 1000);  // Convertir a milisegundos
        }

        all_times.push_back(times_for_size);  // Almacenar los tiempos para este tamaño
    }

    return all_times;
}

// Registrar la función para Python
PYBIND11_MODULE(sort_analysis, m) {
    m.def("measure_sort_times", &measure_sort_times, "Medir los tiempos de ordenación para diferentes tamaños de arreglos");
}

