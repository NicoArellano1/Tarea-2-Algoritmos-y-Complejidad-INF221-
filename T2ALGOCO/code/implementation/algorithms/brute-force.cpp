#include <iostream>
#include <vector>
using namespace std;

long long mejor = 0;

void brute_force(int i, int n, int tiempo_restante, int energia_restante, 
        long long sat_actual, int q[], int t[][30], int c[][30],
        long long v[][30], long long b[]) {

    if (i == n) {
        if (sat_actual > mejor) {
            mejor = sat_actual;
        }
        return;
    }

    brute_force(i + 1, n, tiempo_restante, energia_restante, sat_actual, q, t, c, v, b);

    int tiempo_acum = 0, energia_acum = 0;
    long long sat_acum = 0;

    for (int k = 0; k < q[i]; k++) {
        if (tiempo_restante - tiempo_acum - t[i][k] < 0 || 
            energia_restante - energia_acum - c[i][k] < 0) break;

        tiempo_acum  += t[i][k];
        energia_acum += c[i][k];
        sat_acum     += v[i][k];

        long long bonus = 0;
        if (k == q[i] - 1) {
            bonus = b[i];
        }

        brute_force(i + 1, n, tiempo_restante - tiempo_acum, energia_restante - energia_acum, 
            sat_actual + sat_acum + bonus, q, t, c, v, b);
    }
}
