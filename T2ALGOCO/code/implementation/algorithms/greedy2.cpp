/*
 * Algoritmo: Greedy 2 - Criterio de mayor ratio v/(t+c)
 *
 * Descripcion:
 * Heuristica greedy que en cada paso selecciona el siguiente capitulo
 * disponible de cualquier anime que maximice el ratio v/(t+c), donde
 * v es la satisfaccion, t el tiempo y c la energia. Usa un puntero
 * por anime para respetar la restriccion de prefijos consecutivos.
 * Es suboptima porque toma decisiones locales sin considerar el futuro.
 *
 * Complejidad temporal: O(Q^2) donde Q es el total de capitulos
 * Complejidad espacial: O(n)
 *
 * Referencias:
 * - Kleinberg, J. y Tardos, E. "Algorithm Design". Cap 4: Greedy Algorithms.
 * - Dantzig, G. "Discrete Variable Extremum Problems", 1957.
 * - Material de clases INF-221 2026-1
 */

#include <iostream>
#include <vector>
using namespace std;

long long mejor_g2 = 0;

void greedy2(int n, int M, int E, int q[], int t[][30], int c[][30],
             long long v[][30], long long b[]) {
    int puntero[200] = {0};
    int tiempo_restante = M;
    int energia_restante = E;

    while (true) {
        int mejor_anime = -1;
        double mejor_ratio = -1;

        for (int i = 0; i < n; i++) {
            int k = puntero[i];
            if (k >= q[i]) continue;
            if (t[i][k] > tiempo_restante || c[i][k] > energia_restante) continue;

            double ratio = (double)v[i][k] / (t[i][k] + c[i][k]);
            if (ratio > mejor_ratio) {
                mejor_ratio = ratio;
                mejor_anime = i;
            }
        }

        if (mejor_anime == -1) break;

        int k = puntero[mejor_anime];
        mejor_g2 += v[mejor_anime][k];
        tiempo_restante -= t[mejor_anime][k];
        energia_restante -= c[mejor_anime][k];

        if (puntero[mejor_anime] == q[mejor_anime] - 1) {
            mejor_g2 += b[mejor_anime];
        }

        puntero[mejor_anime]++;
    }
}