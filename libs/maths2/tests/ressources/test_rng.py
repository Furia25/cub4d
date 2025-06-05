from PIL import Image
import numpy as np
from scipy.stats import chisquare, entropy, norm
import matplotlib.pyplot as plt
import math

def lire_fichier(fichier):
    with open(fichier, 'r') as f:
        lignes = f.readlines()
    matrice = []
    for ligne in lignes:
        valeurs = [int(val) for val in ligne.strip().split()]
        matrice.append(valeurs)
    return np.array(matrice)

def normaliser(matrice):
    min_val = matrice.min()
    max_val = matrice.max()
    if max_val == min_val:
        return np.zeros_like(matrice, dtype=np.uint8)
    return ((matrice - min_val) / (max_val - min_val) * 255).astype(np.uint8)

def creer_image_grayscale(matrice, nom_image='image.png'):
    matrice_normalisee = normaliser(matrice)
    image = Image.fromarray(matrice_normalisee, mode='L')
    image.save(nom_image)
    image.show()

def test_moyenne(valeurs):
    moyenne = np.mean(valeurs)
    print(f"[Moyenne] Moyenne : {moyenne:.2f}")

def test_autocorrelation(valeurs):
    correlation = np.corrcoef(valeurs[:-1], valeurs[1:])[0, 1]
    print(f"[Autocorrélation] Corrélation (voisins) : {correlation:.3f}")

def test_chi2_uniformite(valeurs):
    unique, counts = np.unique(valeurs, return_counts=True)
    effectifs = np.zeros(max(unique) + 1)
    effectifs[unique] = counts
    chi2, p = chisquare(effectifs[effectifs > 0])
    print(f"[Chi²] chi2 = {chi2:.2f}, p = {p:.4f}")
    if p < 0.05:
        print("→ Non-uniforme (p < 0.05)")
    else:
        print("→ Compatible avec uniformité")

def test_entropie(valeurs):
    _, counts = np.unique(valeurs, return_counts=True)
    probs = counts / counts.sum()
    ent = entropy(probs, base=2)
    print(f"[Entropie] Entropie de Shannon : {ent:.3f} bits")
    max_ent = math.log2(len(probs))
    print(f"→ Max théorique : {max_ent:.3f} bits")

def test_runs(valeurs):
    diff = np.diff(valeurs)
    runs = 1
    for i in range(1, len(diff)):
        if (diff[i] > 0) != (diff[i-1] > 0):
            runs += 1
    print(f"[Runs] Nombre de changements de tendance : {runs}")

def test_bits(valeurs):
    """Convertit les entiers en binaire et effectue des tests sur les bits"""
    bits = []
    for val in valeurs:
        bits.extend(list(f"{val:08b}"))  # 8 bits par valeur
    bits = np.array([int(b) for b in bits])
    n = len(bits)
    nb_zeros = np.sum(bits == 0)
    nb_uns = np.sum(bits == 1)
    freq = nb_uns / n
    z = abs(freq - 0.5) * math.sqrt(n)
    p = 2 * (1 - norm.cdf(z))
    print(f"[Bits] Proportion de 1 : {freq:.3f}, p = {p:.4f}")
    if p < 0.01:
        print("→ Mauvaise répartition des bits")
    else:
        print("→ Répartition des bits correcte")

def tester_randomness(matrice):
    print("\n=== 🔍 TESTS DE RANDOMNESS ===")
    valeurs = matrice.flatten()

    test_moyenne(valeurs)
    test_autocorrelation(valeurs)
    test_chi2_uniformite(valeurs)
    test_entropie(valeurs)
    test_runs(valeurs)
    test_bits(valeurs)

    # Optionnel : histogramme
    plt.hist(valeurs, bins=range(min(valeurs), max(valeurs) + 2), edgecolor='black')
    plt.title("Histogramme des valeurs")
    plt.xlabel("Valeur")
    plt.ylabel("Fréquence")
    plt.show()

# Exécution
if __name__ == "__main__":
    matrice = lire_fichier("output")
    creer_image_grayscale(matrice)
    tester_randomness(matrice)
