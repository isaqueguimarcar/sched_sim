import pandas as pd

df = pd.read_csv("resultados.csv")

resultado = df.groupby(
    ["algoritmo", "nproc", "quantum"]
)["tme"].agg(
    media="mean",
    desvio="std"
).reset_index()

resultado.to_csv("estatisticas.csv", index=False)

print(resultado)