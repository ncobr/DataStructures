#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits.h>
#include <math.h>
#include <random>
#include "matplotlibcpp.h"
using namespace std;
using namespace chrono;
namespace plt = matplotlibcpp;

void myMerge(vector<int> &A, int p, int q, int r) {
    int n1 = q - p + 1, n2 = r - q;
    int i, j, k;
    vector<int> L(n1 + 2), R(n2 + 2);
    for (i = 1; i <= n1; i++)
        L[i] = A[p + i - 1];
    for (j = 1; j <= n2; j++)
        R[j] = A[q + j];
    L[n1 + 1] = INT_MAX;
    R[n2 + 1] = INT_MAX;
    i = 1;
    j = 1;
    for (k = p; k <= r; k++) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
    }
}

void MergeSort(vector<int> &A, int p, int r) {
    int q;
    if (p < r) {
        q = (p + r) >> 1;
        MergeSort(A, p, q);
        MergeSort(A, q + 1, r);
        myMerge(A, p, q, r);
    }
}

double calculateSD(vector<double> &times) {
    double sum = 0.0, sumSquaredDiffs = 0.0, mean;
    int i = 0;

    // Primer paso: calcular la suma
    while (i < times.size()) {
        sum += times[i];
        i++;
    }

    mean = sum / times.size();

    // Reiniciar el índice para calcular la desviación estándar en la misma iteración
    i = 0;

    while (i < times.size()) {
        sumSquaredDiffs += pow(times[i] - mean, 2);
        i++;
    }

    return sqrt(sumSquaredDiffs / times.size());
}

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);
    int nexponent = 6;



    // Bucle para procesar diferentes tamaños de arreglo
    for (int i = 2; i <= nexponent; i++) {
        long long size = pow(10, i);
        vector<double> times;
        int numTests = 10;

        // Información sobre el tamaño del arreglo
        cout << endl << "Processing array size: 10^" << i << " (" << size << " elements)" << endl;


        // Bucle de pruebas
        for (int testId = 1; testId <= numTests; testId++) {
            vector<int> dataset(size);
            for (long long j = 0; j < size; j++)
                dataset[j] = dis(gen);

            auto start = chrono::high_resolution_clock::now();
            MergeSort(dataset, 0, dataset.size() - 1);
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double, milli> duration = end - start;
            times.push_back(duration.count());

            // Mostrar resultados de cada prueba
            cout << setw(15) << testId
                 << setw(20) << fixed << setprecision(5) << duration.count() << endl;
        }
    }
}



