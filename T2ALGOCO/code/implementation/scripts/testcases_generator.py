# Genera casos de prueba aleatorios y controlados para el problema AniMarathon.
# Los archivos se guardan en data/testcases/ con el formato requerido.
#
# Referencias:
# - Documentacion de Python random: docs.python.org/3/library/random.html

import random
import os

os.makedirs("../data/testcases", exist_ok=True)

# CASOS ORIGINALES
tamaños = [3, 5, 8, 20, 40, 80, 100, 150, 200]
casos_por_tamaño = 3

for n in tamaños:
    for i in range(casos_por_tamaño):
        nombre_archivo = f"../data/testcases/testcases_{n}_{i}.txt"
        with open(nombre_archivo, "w") as f:
            M = random.randint(1, 3000)
            E = random.randint(1, 500)
            f.write(f"{n} {M} {E}\n")
            for j in range(n):
                q = random.randint(1, 30)
                b = random.randint(0, 1000000000)
                f.write(f"anime_{j} {q} {b}\n")
                for k in range(q):
                    t = random.randint(1, 300)
                    c = random.randint(1, 100)
                    v = random.randint(1, 1000000000)
                    f.write(f"{t} {c} {v}\n")

# CASOS PARA VARIAR: n
M_fijo, E_fijo, q_fijo = 1500, 250, 10
for n in [10, 20, 40, 60, 80, 100, 120, 150, 200]:
    nombre_archivo = f"../data/testcases/control_n_{n}.txt"
    with open(nombre_archivo, "w") as f:
        f.write(f"{n} {M_fijo} {E_fijo}\n")
        for j in range(n):
            f.write(f"anime_{j} {q_fijo} {random.randint(0, 1000000000)}\n")
            for k in range(q_fijo):
                f.write(f"{random.randint(1, 300)} {random.randint(1, 100)} {random.randint(1, 1000000000)}\n")

# CASOS PARA VARIAR: M
n_fijo, E_fijo2, q_fijo2 = 50, 250, 10
for M in [500, 1000, 1500, 2000, 2500, 3000]:
    nombre_archivo = f"../data/testcases/control_M_{M}.txt"
    with open(nombre_archivo, "w") as f:
        f.write(f"{n_fijo} {M} {E_fijo2}\n")
        for j in range(n_fijo):
            f.write(f"anime_{j} {q_fijo2} {random.randint(0, 1000000000)}\n")
            for k in range(q_fijo2):
                f.write(f"{random.randint(1, 300)} {random.randint(1, 100)} {random.randint(1, 1000000000)}\n")

# CASOS PARA VARIAR: E
n_fijo2, M_fijo2, q_fijo3 = 50, 1500, 10
for E in [100, 200, 300, 400, 500]:
    nombre_archivo = f"../data/testcases/control_E_{E}.txt"
    with open(nombre_archivo, "w") as f:
        f.write(f"{n_fijo2} {M_fijo2} {E}\n")
        for j in range(n_fijo2):
            f.write(f"anime_{j} {q_fijo3} {random.randint(0, 1000000000)}\n")
            for k in range(q_fijo3):
                f.write(f"{random.randint(1, 300)} {random.randint(1, 100)} {random.randint(1, 1000000000)}\n")

# CASOS PARA VARIAR: q
n_fijo3, M_fijo3, E_fijo3 = 50, 1500, 250
for q_max in [5, 10, 15, 20, 25, 30]:
    nombre_archivo = f"../data/testcases/control_q_{q_max}.txt"
    with open(nombre_archivo, "w") as f:
        f.write(f"{n_fijo3} {M_fijo3} {E_fijo3}\n")
        for j in range(n_fijo3):
            f.write(f"anime_{j} {q_max} {random.randint(0, 1000000000)}\n")
            for k in range(q_max):
                f.write(f"{random.randint(1, 300)} {random.randint(1, 100)} {random.randint(1, 1000000000)}\n")
