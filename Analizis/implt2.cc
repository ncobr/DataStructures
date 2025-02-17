#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
using namespace std::chrono;

// Función para generar un vector aleatorio de tamaño n
vector<int> generarVector(int n) {
    vector<int> vec(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 1000000);

    for (int &num : vec)
        num = dist(gen);

    return vec;
}

// Implementaciones de MergeSort y QuickSort
void merge(vector<int> &arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

void mergeSort(vector<int> &arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// QuickSort con diferentes pivotes
int partition(vector<int> &arr, int low, int high, string pivot_type) {
    int pivot_index;
    if (pivot_type == "Inicio")
        pivot_index = low;
    else if (pivot_type == "Final")
        pivot_index = high;
    else
        pivot_index = low + (high - low) / 2;

    swap(arr[pivot_index], arr[high]);
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot)
            swap(arr[++i], arr[j]);
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int> &arr, int low, int high, string pivot_type) {
    if (low < high) {
        int pi = partition(arr, low, high, pivot_type);
        quickSort(arr, low, pi - 1, pivot_type);
        quickSort(arr, pi + 1, high, pivot_type);
    }
}

// Función para medir el tiempo de ejecución
double medirTiempo(void (*func)(vector<int> &, int, int), vector<int> arr) {
    auto start = high_resolution_clock::now();
    func(arr, 0, arr.size() - 1);
    auto stop = high_resolution_clock::now();
    return duration<double>(stop - start).count();
}

double medirTiempoQuicksort(vector<int> arr, string pivot_type) {
    auto start = high_resolution_clock::now();
    quickSort(arr, 0, arr.size() - 1, pivot_type);
    auto stop = high_resolution_clock::now();
    return duration<double>(stop - start).count();
}

// Cálculo de promedio y desviación estándar
pair<double, double> calcularEstadisticas(vector<double> tiempos) {
    double suma = 0, suma_cuadrados = 0;
    int n = tiempos.size();

    for (double t : tiempos)
        suma += t;
    double promedio = suma / n;

    for (double t : tiempos)
        suma_cuadrados += pow(t - promedio, 2);
    double desviacion = sqrt(suma_cuadrados / n);

    return {promedio, desviacion};
}

// Tamaños de arreglos a probar
vector<long long> tamanios = {100, 1000, 10000, 100000, 1000000, 10000000};

int main() {
    ofstream archivo("resultados.csv");
    archivo << "Tamaño,Algoritmo,Pivote,Promedio,Desviacion\n";

    for (long long n : tamanios) {
        vector<double> tiemposMerge, tiemposQuickInicio, tiemposQuickFinal,
            tiemposQuickMitad;

        // 10 ejecuciones por cada algoritmo y tamaño de arreglo
        for (int i = 0; i < 10; i++) {
            cout << "test: " << i << endl;
            vector<int> arr = generarVector(n);

            vector<int> copia = arr;
            tiemposMerge.push_back(medirTiempo(mergeSort, copia));

            copia = arr;
            tiemposQuickInicio.push_back(medirTiempoQuicksort(copia, "Inicio"));

            copia = arr;
            tiemposQuickFinal.push_back(medirTiempoQuicksort(copia, "Final"));

            copia = arr;
            tiemposQuickMitad.push_back(medirTiempoQuicksort(copia, "Mitad"));
        }

        // Calcular estadísticas
        auto [promMerge, desvMerge] = calcularEstadisticas(tiemposMerge);
        auto [promQuickInicio, desvQuickInicio] =
            calcularEstadisticas(tiemposQuickInicio);
        auto [promQuickFinal, desvQuickFinal] =
            calcularEstadisticas(tiemposQuickFinal);
        auto [promQuickMitad, desvQuickMitad] =
            calcularEstadisticas(tiemposQuickMitad);

        // Guardar resultados
        archivo << n << ",MergeSort,NA," << promMerge << "," << desvMerge
                << "\n";
        archivo << n << ",QuickSort,Inicio," << promQuickInicio << ","
                << desvQuickInicio << "\n";
        archivo << n << ",QuickSort,Final," << promQuickFinal << ","
                << desvQuickFinal << "\n";
        archivo << n << ",QuickSort,Mitad," << promQuickMitad << ","
                << desvQuickMitad << "\n";
    }

    archivo.close();
    cout << "Resultados guardados en resultados.csv" << endl;
    return 0;
}

