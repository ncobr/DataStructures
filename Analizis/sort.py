import sort_analysis
import matplotlib.pyplot as plt

# Definir los tamaños de los arreglos
sizes = [10**i for i in range(2, 7)]

# Llamar a la función C++ para medir los tiempos de ordenación
times = sort_analysis.measure_sort_times(sizes)

# Graficar los resultados
plt.plot(sizes, times, label="Merge Sort")
plt.xlabel("Tamaño del arreglo (10^n)")
plt.ylabel("Tiempo (ms)")
plt.xscale("log")
plt.yscale("log")
plt.grid(True, which="both", ls="--")
plt.title("Tiempo de ejecución de Merge Sort")
plt.show()
