// Compilación Linux: g++ main.cpp -o main
// Ejecución Linux: ./main

#include <iostream>
#include "hashing_cerrado.h"
#include "hashing_abierto.h"
#include "utilidades.h"

using namespace std;

const string ruta_dataset = "datasets/auspol2019.csv";

int main() {
    int N = 40;
    // factor de carga: alfa = n / N
    // En esta prueba, alfa = 0.5 (no cumple alfa < 0.5)
    // Número de pruebas esperado con direccionamiento abierto = 1 / (1 - alfa) = 2

    int maxFilas = 20;

    // ========================================
    // HASHING CERRADO: USER_ID (long long)
    // ========================================

    TablaHashingCerrado<long long> thc_user_id(N, LINEAR_PROBING);
    cargarDataset(thc_user_id, ruta_dataset, "user_id", maxFilas);
    thc_user_id.imprimir();

    // ========================================
    // HASHING CERRADO: USER_SCREEN_NAME (string)
    // ========================================

    TablaHashingCerrado<string> thc_user_screen_name(N, LINEAR_PROBING);
    cargarDataset(thc_user_screen_name, ruta_dataset, "user_screen_name", maxFilas);
    thc_user_screen_name.imprimir();

    // TablaHashingAbierto<long long> tha_user_id(N);
    // cargarDataset(tha_user_id, ruta_dataset, "user_id", maxFilas);
    // tha_user_id.imprimir();

    // TablaHashingAbierto<string> tha_user_screen_name(N);
    // cargarDataset(tha_user_screen_name, ruta_dataset, "user_screen_name", maxFilas);
    // tha_user_screen_name.imprimir();


    return 0;
}