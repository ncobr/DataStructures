#include <algorithm>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>

using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 10000);

    cout << setw(20) << "Tamaño (10^n)" << setw(20) << "n" << setw(25)
         << "Tiempo Promedio (ms)" << endl;
    cout << string(65, '-') << endl;

    // Generar y procesar los arreglos uno por uno
    for (int i = 2; i <= 8; i++) { // Hasta 10^9
        long long size = pow(10, i);
        double total_time = 0;

        int num_tests = (size < 1e6) ? 10 : (size < 1e8) ? 5 : 3;

        for (int test = 0; test < num_tests; test++) {
            // Asignar memoria dinámicamente
            vector<int> arr(size);

            // Generar números aleatorios
            for (long long j = 0; j < size; j++) {
                arr[j] = dis(gen);
            }

            // Medir tiempo de ejecución
            auto start = chrono::high_resolution_clock::now();
            sort(arr.begin(), arr.end()); // Ordenamiento estándar
            auto end = chrono::high_resolution_clock::now();

            chrono::duration<double, milli> duration = end - start;
            total_time += duration.count();

            // Liberar memoria
        }

        double avg_time = total_time / num_tests;
        cout << setw(20) << size << setw(20) << i + 2 << setw(25) << fixed
             << setprecision(3) << avg_time << endl;
    }

    return 0;
}

