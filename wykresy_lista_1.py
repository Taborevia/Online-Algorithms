import matplotlib.pyplot as plt
import numpy as np

# Nazwa pliku z danymi
filename = "wyniki_wykres.txt"  # Zmień na rzeczywistą nazwę pliku

# Rozkłady w kolejności występowania w pliku
distributions = ["Uniform", "Harmonic", "Biharmonic", "Geometric"]

# Struktura danych: {rozkład: {id_grupy: (listy n, listy wartości)}}
data = {dist: {i: ([], []) for i in range(4)} for dist in distributions}

# Wczytywanie danych
with open(filename, "r") as file:
    lines = file.readlines()

# Przetwarzanie danych (podział na rozkłady i grupy)
for i, line in enumerate(lines):
    n, value = map(float, line.split())  # Odczytanie wartości n i kosztu

    dist_index = i % 4  # Który rozkład?
    group_id = (i // 4) % 4  # Do której grupy (modulo 16 -> 4 grupy)?

    data[distributions[dist_index]][group_id][0].append(n)   # Dodaj n do listy X
    data[distributions[dist_index]][group_id][1].append(value)  # Dodaj wartość do listy Y

# Słownik z nazwami grup dla każdego ID
group_names = {
    0: "Bez organizacji",
    1: "MTF (Move To Front)",
    2: "Transpose",
    3: "Count"
}

# Tworzenie wykresów
plt.figure(figsize=(12, 8))

for idx, (dist_name, groups) in enumerate(data.items()):
    plt.subplot(2, 2, idx + 1)  # 2x2 układ wykresów
    
    for group_id, (n_values, cost_values) in groups.items():
        # Sortowanie wartości n (dla poprawnego rysowania linii)
        sorted_indices = np.argsort(n_values)
        n_sorted = np.array(n_values)[sorted_indices]
        cost_sorted = np.array(cost_values)[sorted_indices]

        # Rysowanie linii bez kropek
        plt.plot(n_sorted, cost_sorted, linestyle='-', linewidth=1.5, alpha=0.7, label=f"Grupa {group_names[group_id]}")

    # Ustawianie tytułu wykresu w zależności od rozkładu
    plt.title(f"{dist_name} Distribution")
    plt.xlabel("n")
    plt.ylabel("Wartość")
    plt.xscale("log")  # Logarytmiczna skala X (opcjonalnie)
    plt.legend()
    plt.grid()

# Wyświetlenie wykresów
plt.tight_layout()
plt.show()
