#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits.h>
#include <random>
#include <vector>

using namespace std;
using namespace chrono;

// Estructura para almacenar los resultados de las medidas
struct SortingResult {
    double mean;
    double stdDev;
};

void merge(vector<int> &A, int p, int q, int r) {
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

void mergesort(vector<int> &A, int p, int r) {
    int q;
    if (p < r) {
        q = (p + r) >> 1;
        mergesort(A, p, q);
        mergesort(A, q + 1, r);
        merge(A, p, q, r);
    }
}

// Implementación de QuickSort con diferentes estrategias de pivot
int partitionLast(vector<int> &A, int p, int r) {
    int x = A[r];
    int i = p - 1;

    for (int j = p; j < r; j++) {
        if (A[j] < x) {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[r]);
    return i + 1;
}

int partitionFirst(vector<int> &A, int p, int r) {
    int x = A[p];
    int i = p + 1;

    for (int j = p + 1; j <= r; j++) {
        if (A[j] < x) {
            swap(A[i], A[j]);
            i++;
        }
    }
    swap(A[p], A[i - 1]);
    return i - 1;
}

int partitionRandom(vector<int> &A, int p, int r) {
    // Pivote aleatorio
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(p, r);
    int ri = dis(gen);
    swap(A[ri], A[r]); // Mover pivote al final

    int x = A[r]; // Ahora el pivote es el último elemento
    int i = p - 1;

    for (int j = p; j < r; j++) {
        if (A[j] < x)
            swap(A[++i], A[j]); // preincremento
    }
    swap(A[i + 1], A[r]);
    return i + 1;
}

void quickSort(vector<int> &A, int p, int r, int pivotStrategy) {
    if (p < r) {
        int q;
        switch (pivotStrategy) {
        case 0:
            q = partitionFirst(A, p, r);
            break;
        case 1:
            q = partitionLast(A, p, r);
            break;
        case 2:
            q = partitionRandom(A, p, r);
            break;
        }
        quickSort(A, p, q - 1, pivotStrategy);
        quickSort(A, q + 1, r, pivotStrategy);
    }
}


vector<int> generateRandomVector(int size) {
    vector<int> randomVec(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, size * 10);

    for (int i = 0; i < size; i++)
        randomVec[i] = dis(gen);

    return randomVec;
}

SortingResult measureSortingTime(int size, bool isMergeSort,int pivotStrategy = 0) {
    vector<double> times;
    for (int i = 0; i < 10; i++) {
        vector<int> arr = generateRandomVector(size);

        auto start = high_resolution_clock::now();
        if (isMergeSort)
            mergesort(arr, 0, arr.size() - 1);
        else
            quickSort(arr, 0, arr.size() - 1, pivotStrategy);
        auto end = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(end - start);
        cout << "Test: " << i + 1 << setw(25) << "Time: " << duration.count()
             << " mcrs" << endl;
        times.push_back(duration.count());
    }

    double sum = 0;
    // double time = 0; time < times.size(); time++
    for (double time : times)
        sum += time;
    double mean = sum / times.size();

    // Calcular desviación estándar
    double sqSum = 0;
    for (double time : times)
        sqSum += (time - mean) * (time - mean);
    double stdDev = sqrt(sqSum / (times.size() - 1));
    // retorna un objeto de tipo SortingResult que contiene los
    // valores calculados de la media y la desviación estándar.
    return {mean, stdDev};
}

int main() {
    cout << "Starting benchmark ..." << endl;
    ofstream outFile("sorting_results.csv");
    outFile << "Size,MergeSort_Mean,MergeSort_StdDev,QuickSort_First_Mean,"
               "QuickSort_First_StdDev,"
            << "QuickSort_Last_Mean,QuickSort_Last_StdDev,QuickSort_Random_"
               "Mean,QuickSort_Random_StdDev\n";

    vector<int64_t> sizes = {100,       1000,       10000,
                             100000,    1000000,    10000000,
                             100000000, 1000000000, 10000000000};

    for (int i = 0; i < sizes.size(); i++) {

        int64_t size = sizes[i];
        cout << string(50, '-') << endl;
        cout << "Processing size: " << size << endl;
        cout << "Testing dataset whit size: " << size << endl;

        // MergeSort
        cout << "Algorithm: MergeSort" << endl;
        SortingResult mergeResult = measureSortingTime(size, true);

        // QuickSort con diferentes estrategias de pivot
        cout << "\nAlgorithm: QuickSort (first position pivot)" << endl;
        SortingResult quickFirstResult = measureSortingTime(size, false, 0);

        cout << "\nAlgorithm: QuickSort (last position pivot)" << endl;
        SortingResult quickLastResult = measureSortingTime(size, false, 1);

        cout << "\nAlgorithm: QuickSort (random pivot)" << endl;
        SortingResult quickMiddleResult = measureSortingTime(size, false, 2);

        outFile << size << "," << mergeResult.mean << "," << mergeResult.stdDev
                << "," << quickFirstResult.mean << ","
                << quickFirstResult.stdDev << "," << quickLastResult.mean << ","
                << quickLastResult.stdDev << "," << quickMiddleResult.mean
                << "," << quickMiddleResult.stdDev << "\n";
    }

    outFile.close();
    cout << "Results have been written to sorting_results.csv" << endl;

    return 0;
}
