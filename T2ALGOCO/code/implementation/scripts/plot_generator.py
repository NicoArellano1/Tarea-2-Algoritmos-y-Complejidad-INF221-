# Lee los archivos CSV de mediciones y genera graficos PNG en data/plots/.
# Compara tiempo de ejecucion, uso de memoria y calidad de solucion entre algoritmos.
#
# Referencias:
# - Documentacion de pandas: pandas.pydata.org
# - Documentacion de matplotlib: matplotlib.org

import pandas as pd
import matplotlib.pyplot as plt
import os

os.makedirs("../data/plots", exist_ok=True)

med = pd.read_csv("../data/measurements/measurements.csv")
out = pd.read_csv("../data/outputs/outputs.csv")

med_std = med[med['n'].astype(str).str.isnumeric()].copy()
med_std['n'] = pd.to_numeric(med_std['n'])

out_std = out[out['n'].astype(str).str.isnumeric()].copy()
out_std['n'] = pd.to_numeric(out_std['n'])

fig, ax = plt.subplots(figsize=(10, 6))
for algo in ['brute_force', 'greedy1', 'greedy2']:
    df = med_std[med_std['algoritmo'] == algo]
    promedio = df.groupby('n')['tiempo_us'].mean()
    ax.plot(promedio.index, promedio.values, marker='o', label=algo)

ax.set_title("Tiempo de ejecución: BF y Greedy")
ax.set_xlabel("Cantidad de animes (n)")
ax.set_ylabel("Tiempo promedio (µs)")
ax.legend()
ax.grid(True)
plt.tight_layout()
plt.savefig("../data/plots/tiempo_bf_greedy.png")
plt.close()

fig, ax = plt.subplots(figsize=(10, 6))
df = med_std[med_std['algoritmo'] == 'dynamic_programming']
promedio = df.groupby('n')['tiempo_us'].mean()
ax.plot(promedio.index, promedio.values, marker='o', color='red', label='dynamic_programming')

ax.set_title("Tiempo de ejecución: DP")
ax.set_xlabel("Cantidad de animes (n)")
ax.set_ylabel("Tiempo promedio (µs)")
ax.legend()
ax.grid(True)
plt.tight_layout()
plt.savefig("../data/plots/tiempo_dp.png")
plt.close()

fig, ax = plt.subplots(figsize=(10, 6))
for algo in med_std['algoritmo'].unique():
    df = med_std[med_std['algoritmo'] == algo]
    promedio = df.groupby('n')['memoria_kb'].mean()
    ax.plot(promedio.index, promedio.values, marker='o', label=algo)

ax.set_title("Uso de memoria según tamaño de entrada")
ax.set_xlabel("Cantidad de animes (n)")
ax.set_ylabel("Memoria promedio (KB)")
ax.legend()
ax.grid(True)
plt.tight_layout()
plt.savefig("../data/plots/memoria.png")
plt.close()

dp = out_std[out_std['algoritmo'] == 'dynamic_programming'][['n', 'caso', 'resultado']]
dp = dp.rename(columns={'resultado': 'resultado_dp'})

for algo in ['greedy1', 'greedy2']:
    fig, ax = plt.subplots(figsize=(10, 6))
    g = out_std[out_std['algoritmo'] == algo][['n', 'caso', 'resultado']]
    merged = pd.merge(g, dp, on=['n', 'caso'])
    merged['ratio'] = merged['resultado'] / merged['resultado_dp'] * 100
    merged.loc[merged['resultado_dp'] == 0, 'ratio'] = 100

    promedio = merged.groupby('n')['ratio'].mean()
    ax.plot(promedio.index, promedio.values, marker='o', color='orange' if algo == 'greedy1' else 'green')
    ax.axhline(y=100, color='red', linestyle='--', label='Óptimo (DP)')
    ax.set_title(f"Calidad de solución: {algo} vs DP")
    ax.set_xlabel("Cantidad de animes (n)")
    ax.set_ylabel("% del óptimo alcanzado")
    ax.legend()
    ax.grid(True)
    plt.tight_layout()
    plt.savefig(f"../data/plots/calidad_{algo}.png")
    plt.close()

def plot_controlled(prefix, xlabel, file_suffix):
    df_ctrl = med[med['n'].astype(str).str.startswith(prefix)].copy()
    if df_ctrl.empty: return
    df_ctrl['var_val'] = df_ctrl['n'].apply(lambda x: int(x.split('_')[-1]))
    fig, ax = plt.subplots(figsize=(10, 6))
    for algo in df_ctrl['algoritmo'].unique():
        df_algo = df_ctrl[df_ctrl['algoritmo'] == algo]
        promedio = df_algo.groupby('var_val')['tiempo_us'].mean()
        ax.plot(promedio.index, promedio.values, marker='o', label=algo)
    ax.set_title(f"Tiempo de ejecución variando {xlabel}")
    ax.set_xlabel(xlabel)
    ax.set_ylabel("Tiempo promedio (µs)")
    ax.legend()
    ax.grid(True)
    plt.tight_layout()
    plt.savefig(f"../data/plots/control_tiempo_{file_suffix}.png")
    plt.close()

plot_controlled('ctrl_n_', 'Cantidad de Animes (n)', 'n')
plot_controlled('ctrl_M_', 'Tiempo Máximo (M)', 'M')
plot_controlled('ctrl_E_', 'Energía Máxima (E)', 'E')
plot_controlled('ctrl_q_', 'Capítulos Máximos (q)', 'q')