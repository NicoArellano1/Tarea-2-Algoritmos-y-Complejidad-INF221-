/*
 * Algoritmo: Programacion Dinamica (Bottom-Up)
 *
 * Descripcion:
 * Resuelve el problema AniMarathon de forma optima mediante una tabla
 * dp[m][e] donde dp[m][e] representa la maxima satisfaccion obtenible
 * con exactamente m minutos y e energia disponibles. Para cada anime
 * se calculan los acumulados de tiempo, energia y satisfaccion por
 * prefijo, y se actualiza la tabla recorriendo de mayor a menor para
 * evitar usar el mismo anime mas de una vez.
 *
 * Complejidad temporal: O(n * q_max * M * E)
 * Complejidad espacial: O(M * E) por la tabla dp
 *
 * Referencias:
 * - Cormen, T. et al. "Introduction to Algorithms", 3ra ed. Cap 15.
 * - Kellerer, H. et al. "Knapsack Problems". Springer, 2004.
 * - Material de clases INF-221 2026-1
 */

#include <iostream>
using namespace std;

long long mejor_dp = 0;
long long dp[3001][501];

void dynamic_programming(int n, int M, int E, int q[], int t[][30], int c[][30],
                          long long v[][30], long long b[]) {

    for (int m = 0; m <= 3000; m++)
        for (int e = 0; e <= 500; e++)
            dp[m][e] = 0;

    for (int i = 0; i < n; i++) {
        int tiempo_acum[31] = {};
        int energia_acum[31] = {};
        long long sat_acum[31] = {};

        for (int k = 0; k < q[i]; k++) {
            tiempo_acum[k+1]  = tiempo_acum[k]  + t[i][k];
            energia_acum[k+1] = energia_acum[k] + c[i][k];
            sat_acum[k+1]     = sat_acum[k]     + v[i][k];
            if (k == q[i] - 1) {
                sat_acum[k+1] += b[i];
            }
        }

        for (int m = M; m >= 0; m--) {
            for (int e = E; e >= 0; e--) {
                for (int k = 1; k <= q[i]; k++) {
                    if (m >= tiempo_acum[k] && e >= energia_acum[k]) {
                        dp[m][e] = max(dp[m][e], dp[m - tiempo_acum[k]][e - energia_acum[k]] + sat_acum[k]);
                    }
                }
            }
        }
    }

    mejor_dp = dp[M][E];
}