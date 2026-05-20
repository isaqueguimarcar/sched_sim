import os
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("estatisticas.csv")

algoritmos = df["algoritmo"].unique()

for algoritmo in algoritmos:

    dados = df[df["algoritmo"] == algoritmo]

    for quantum in [10,20,30]:

        subset = dados[dados["quantum"] == quantum]

        plt.figure()

        plt.errorbar(
            subset["nproc"],
            subset["media"],
            yerr=subset["desvio"],
            marker='o',
            capsize=5
        )

        plt.xlabel("Número de Processos")
        plt.ylabel("TME Médio")
        plt.title(f"{algoritmo} - Quantum {quantum}")

        plt.grid(True)

        os.makedirs("graficos", exist_ok=True)
        
        plt.savefig(f"graficos/{algoritmo}_q{quantum}.png")

        plt.close()