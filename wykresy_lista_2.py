import matplotlib.pyplot as plt
import pandas as pd

# Wczytywanie danych
filename = "wyniki_lista_2_geometryczny.txt"
with open(filename, 'r') as file:
    lines = [line.strip() for line in file if line.strip()]
data = [list(map(float, line.split())) for line in lines]
df = pd.DataFrame(data, columns=["algorithm", "cost", "n", "k"])

df['algorithm'] = df['algorithm'].astype(int)
df['n'] = df['n'].astype(int)
df['k'] = df['k'].astype(int)

# Kolory i szerokości linii
algorithms = sorted(df['algorithm'].unique())
line_widths = [2.0] * len(algorithms)  # Stała szerokość linii dla wszystkich algorytmów

# Różne wzorce linii przerywanych
linestyles = ['--', '-.', ':', '--', '-.', ':', '--', '-.', ':']  # Powtarzający się zestaw
alg_names = ["FIFO","FWF","LRU","LFU","RAND","RMA"]

# Kolory o dużym kontraście (paleta tab10)
colors = plt.cm.tab10(range(len(algorithms)))

plt.figure(figsize=(14, 6))

# Wykres 1: koszt vs n dla k = n/10
plt.subplot(1, 2, 1)
for i, alg in enumerate(reversed(algorithms)):  # rysujemy najgrubszą najpierw
    subset = df[df['k'] == df['n'] // 10]
    subset = subset[subset['algorithm'] == alg].sort_values(by='n')
    plt.plot(subset['n'], subset['cost'],
             linestyle=linestyles[i % len(linestyles)],  # Różne wzorce linii
             marker='o',     # Stały marker
             color=colors[i],  # Zmienny kolor
             linewidth=line_widths[i],  # Stała grubość linii
             alpha=0.95,
             label=f'{alg_names[alg]}')
plt.title("Średni koszt względem n dla k = n/10")
plt.xlabel("n")
plt.ylabel("Średni koszt")
plt.grid(True)
plt.legend(loc='center left', bbox_to_anchor=(1, 0.5))

# Wykres 2: koszt vs k dla n = 100
plt.subplot(1, 2, 2)
for i, alg in enumerate(reversed(algorithms)):
    subset = df[df['n'] == 100]
    subset = subset[subset['algorithm'] == alg].sort_values(by='k')
    plt.plot(subset['k'], subset['cost'],
             linestyle=linestyles[i % len(linestyles)],  # Różne wzorce linii
             marker='o',     # Stały marker
             color=colors[i],  # Zmienny kolor
             linewidth=line_widths[i],  # Stała grubość linii
             alpha=0.95,
             label=f'{alg_names[alg]}')
plt.title("Średni koszt względem k dla n = 100")
plt.xlabel("k")
plt.ylabel("Średni koszt")
plt.grid(True)

plt.tight_layout()
plt.savefig("wykres_geometryczny_2.pdf", format='pdf', bbox_inches='tight')
plt.show()
