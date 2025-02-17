import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Leer los resultados
df = pd.read_csv('sorting_results.csv')

# Crear gráfica de tiempos de ejecución
plt.figure(figsize=(12, 6))
plt.errorbar(df['Size'], df['MergeSort_Mean'], yerr=df['MergeSort_StdDev'],
             label='MergeSort', marker='o')
plt.errorbar(df['Size'], df['QuickSort_First_Mean'], yerr=df['QuickSort_First_StdDev'],
             label='QuickSort (First)', marker='s')
plt.errorbar(df['Size'], df['QuickSort_Last_Mean'], yerr=df['QuickSort_Last_StdDev'],
             label='QuickSort (Last)', marker='^')
plt.errorbar(df['Size'], df['QuickSort_Random_Mean'], yerr=df['QuickSort_Random_StdDev'],
             label='QuickSort (Random)', marker='*')

# Agregar función teórica n*log(n)
x = df['Size']
theoretical = x * np.log2(x) / 1e7  # Factor de escala para visualización
plt.plot(x, theoretical, '--', label='n*log(n)', color='gray')

plt.xscale('log')
plt.yscale('log')
plt.xlabel('Tamaño del Array')
plt.ylabel('Tiempo (segundos)')
plt.title('Comparación de Algoritmos de Ordenamiento')
plt.legend()
plt.grid(True)
plt.show()
