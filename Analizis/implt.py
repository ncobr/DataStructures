import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

df = pd.read_csv("resultados.csv")

plt.figure(figsize=(10, 6))
sns.lineplot(data=df, x="Tamaño", y="Promedio",
             hue="Algoritmo", style="Pivote", markers=True)
plt.xscale("log")
plt.yscale("log")
plt.xlabel("Tamaño del arreglo")
plt.ylabel("Tiempo de ejecución (s)")
plt.title("Comparación de MergeSort y QuickSort")
plt.legend()
plt.show()
