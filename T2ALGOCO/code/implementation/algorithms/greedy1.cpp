#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long mejor_g1 = 0;

void greedy1(int n, int M, int E, int q[], int t[][30], int c[][30],
             long long v[][30], long long b[]) {
    vector<pair<long long, int>> animes;
    for (int i = 0; i < n; i++) {
        animes.push_back({b[i], i});
    }
    sort(animes.begin(), animes.end(), greater<pair<long long, int>>());

    int tiempo_restante = M;
    int energia_restante = E;

    for (auto [bono, i] : animes) {
        for (int k = 0; k < q[i]; k++) {
            if (t[i][k] <= tiempo_restante && c[i][k] <= energia_restante) {
                mejor_g1 += v[i][k];
                tiempo_restante -= t[i][k];
                energia_restante -= c[i][k];
                if (k == q[i] - 1) {
                    mejor_g1 += b[i];
                }
            } else {
                break;
            }
        }
    }
}