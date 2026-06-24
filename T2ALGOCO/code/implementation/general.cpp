/* 
 * Programa principal que lee los casos de prueba, corre todos los algoritmos
 * y guarda los resultados de tiempo, memoria y satisfaccion en archivos CSV.
 * 
 * Para medir tiempo use chrono de C++ en microsegundos.
 * Para memoria lei /proc/self/status que entrega el uso de RAM del proceso.
 * 
 * Referencias:
 * - cppreference.com para uso de chrono y filesystem
 * - Material de clases INF-221 2026-1
 */

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
using namespace std;

// Valores optimizados ya sea global o localmente de la satisfaccion total de cada algoritmo de optimizacion 
extern long long mejor;
extern long long mejor_g1;
extern long long mejor_g2;
extern long long mejor_dp;

// Llamadas a las funciones en el general para invocarlas en el main!
void brute_force(int i, int n, int tiempo_restante, int energia_restante,
                 long long sat_actual, int q[], int t[][30], int c[][30],
                 long long v[][30], long long b[]);

void greedy1(int n, int M, int E, int q[], int t[][30], int c[][30],
             long long v[][30], long long b[]);

void greedy2(int n, int M, int E, int q[], int t[][30], int c[][30],
             long long v[][30], long long b[]);

void dynamic_programming(int n, int M, int E, int q[], int t[][30], int c[][30],
                         long long v[][30], long long b[]);

// Funcion pequeñita obtener memoria en kb
long long obtener_memoria_kb() {
    ifstream status("/proc/self/status");
    string linea;
    while (getline(status, linea)) {
        if (linea.find("VmRSS:") != string::npos) {
            long long kb;
            sscanf(linea.c_str(), "VmRSS: %lld kB", &kb);
            return kb;
        }
    }
    return 0;
}

// Funcion para leer los archivos
void leer_archivo(string path, int &n, int &M, int &E, string nombres[],
                  int q[], long long b[], int t[][30], int c[][30], long long v[][30]) {
    ifstream archivo(path);
    archivo >> n >> M >> E;
    for (int i = 0; i < n; i++) {
        archivo >> nombres[i] >> q[i] >> b[i];
        for (int k = 0; k < q[i]; k++) {
            archivo >> t[i][k] >> c[i][k] >> v[i][k];
        }
    }
}

void correr_todos(string path, string label, int caso,
                  ofstream &med, ofstream &out,
                  int &n, int &M, int &E, string nombres[],
                  int q[], long long b[], int t[][30], int c[][30], long long v[][30],
                  bool correr_bf) {

    leer_archivo(path, n, M, E, nombres, q, b, t, c, v);

    if (correr_bf) {
        mejor = 0;
        auto inicio = chrono::high_resolution_clock::now();
        brute_force(0, n, M, E, 0, q, t, c, v, b);
        auto fin = chrono::high_resolution_clock::now();
        double tiempo = chrono::duration<double, micro>(fin - inicio).count();
        med << "brute_force," << label << "," << caso << "," << tiempo << "," << obtener_memoria_kb() << "\n";
        out << "brute_force," << label << "," << caso << "," << mejor << "\n";
    }

    mejor_g1 = 0;
    auto inicio = chrono::high_resolution_clock::now();
    greedy1(n, M, E, q, t, c, v, b);
    auto fin = chrono::high_resolution_clock::now();
    double tiempo = chrono::duration<double, micro>(fin - inicio).count();
    med << "greedy1," << label << "," << caso << "," << tiempo << "," << obtener_memoria_kb() << "\n";
    out << "greedy1," << label << "," << caso << "," << mejor_g1 << "\n";

    mejor_g2 = 0;
    inicio = chrono::high_resolution_clock::now();
    greedy2(n, M, E, q, t, c, v, b);
    fin = chrono::high_resolution_clock::now();
    tiempo = chrono::duration<double, micro>(fin - inicio).count();
    med << "greedy2," << label << "," << caso << "," << tiempo << "," << obtener_memoria_kb() << "\n";
    out << "greedy2," << label << "," << caso << "," << mejor_g2 << "\n";

    mejor_dp = 0;
    inicio = chrono::high_resolution_clock::now();
    dynamic_programming(n, M, E, q, t, c, v, b);
    fin = chrono::high_resolution_clock::now();
    tiempo = chrono::duration<double, micro>(fin - inicio).count();
    med << "dynamic_programming," << label << "," << caso << "," << tiempo << "," << obtener_memoria_kb() << "\n";
    out << "dynamic_programming," << label << "," << caso << "," << mejor_dp << "\n";
}

int main() {
    int n, M, E;
    int q[200];
    long long b[200];
    int t[200][30], c[200][30];
    long long v[200][30];
    string nombres[200];

    ofstream med("data/measurements/measurements.csv");
    ofstream out("data/outputs/outputs.csv");

    med << "algoritmo,n,caso,tiempo_us,memoria_kb\n";
    out << "algoritmo,n,caso,resultado\n";

    // CASOS ORIGINALES
    int pequeños[] = {3, 5, 8};
    for (int tam : pequeños) {
        for (int i = 0; i < 3; i++) {
            string path = "data/testcases/testcases_" + to_string(tam) + "_" + to_string(i) + ".txt";
            correr_todos(path, to_string(tam), i, med, out, n, M, E, nombres, q, b, t, c, v, true);
        }
    }

    int todos[] = {20, 40, 80, 100, 150, 200};
    for (int tam : todos) {
        for (int i = 0; i < 3; i++) {
            string path = "data/testcases/testcases_" + to_string(tam) + "_" + to_string(i) + ".txt";
            correr_todos(path, to_string(tam), i, med, out, n, M, E, nombres, q, b, t, c, v, false);
        }
    }

    // CASOS CONTROLADOS PARA VARIAR: n
    int ns[] = {10, 20, 40, 60, 80, 100, 120, 150, 200};
    for (int vn : ns) {
        string path = "data/testcases/control_n_" + to_string(vn) + ".txt";
        correr_todos(path, "ctrl_n_" + to_string(vn), 0, med, out, n, M, E, nombres, q, b, t, c, v, false);
    }

    // CASOS CONTROLADOS PARA VARIAR: M
    int Ms[] = {500, 1000, 1500, 2000, 2500, 3000};
    for (int vM : Ms) {
        string path = "data/testcases/control_M_" + to_string(vM) + ".txt";
        correr_todos(path, "ctrl_M_" + to_string(vM), 0, med, out, n, M, E, nombres, q, b, t, c, v, false);
    }

    // CASOS CONTROLADOS PARA VARIAR: E
    int Es[] = {100, 200, 300, 400, 500};
    for (int vE : Es) {
        string path = "data/testcases/control_E_" + to_string(vE) + ".txt";
        correr_todos(path, "ctrl_E_" + to_string(vE), 0, med, out, n, M, E, nombres, q, b, t, c, v, false);
    }

    // CASOS CONTROLADOS PARA VARIAR: q
    int qs[] = {5, 10, 15, 20, 25, 30};
    for (int vq : qs) {
        string path = "data/testcases/control_q_" + to_string(vq) + ".txt";
        correr_todos(path, "ctrl_q_" + to_string(vq), 0, med, out, n, M, E, nombres, q, b, t, c, v, false);
    }

    med.close();
    out.close();

    return 0;
}