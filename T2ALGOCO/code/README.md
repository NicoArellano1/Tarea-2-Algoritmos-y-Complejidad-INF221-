# Documentación

## Implementación

### Programa principal

`general.cpp` es el programa principal que lee los casos de prueba, ejecuta todos los algoritmos, mide tiempo y memoria, y guarda los resultados en `data/measurements/measurements.csv` y `data/outputs/outputs.csv`.

Para compilar y ejecutar todo desde `code/implementation/`:

```bash
make
```

Para pasos individuales:

```bash
make compile   # compila todos los algoritmos
make tests     # genera casos de prueba en data/testcases/
make run       # ejecuta los algoritmos y guarda mediciones
make plots     # genera gráficos PNG en data/plots/
make clean     # limpia archivos generados
```

### Scripts

`scripts/testcases_generator.py` genera automáticamente los casos de prueba en `data/testcases/`:
- `testcases_{n}_{i}.txt`: casos aleatorios pequeños, medianos y grandes
- `control_n_{n}.txt`, `control_M_{M}.txt`, `control_E_{E}.txt`, `control_q_{q}.txt`: casos controlados variando un parámetro a la vez

`scripts/plot_generator.py` lee los archivos CSV de mediciones y genera los gráficos en `data/plots/`.