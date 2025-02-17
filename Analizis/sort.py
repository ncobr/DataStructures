import sort_analysis
import matplotlib.pyplot as plt

# Definir los tamaños de los arreglos
sizes = [10**i for i in range(2, 7)]

# Llamar a la función C++ para medir los tiempos de ordenación
all_times = sort_analysis.measure_sort_times(sizes)

# Graficar los resultados
for i, times in enumerate(all_times):
    plt.plot([sizes[i]] * len(times), times, 'bo-',
             label=f"Tamaño {sizes[i]}")  # Línea por cada prueba

plt.xlabel("Tamaño del arreglo (10^n)")
plt.ylabel("Tiempo (ms)")
plt.xscale("log")
plt.yscale("log")
plt.grid(True, which="both", ls="--")
plt.title("Tiempos de ejecución de Merge Sort para diferentes tamaños de arreglo")
plt.legend()
plt.show()

