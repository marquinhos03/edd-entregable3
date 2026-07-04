#include <iostream>
#include <string>
#include "utilidades.h"
#include "adaptador_unordered_map.h"
#include "hashing_cerrado.h"
#include "hashing_abierto.h"

using namespace std;

int main() {
    // Usamos un N minúsculo para forzar que la tabla se llene rápido y colisione
    int N = 7; 
    int limiteFilas = 100; // Suficiente para leer todo el test.csv
    string ruta_test = "datasets/test.csv";

    cout << "==========================================\n";
    cout << "   AUDITORIA LÓGICA: USER_ID NUMÉRICO     \n";
    cout << "==========================================\n";

    // 1. El estándar de oro (STL)
    cout << "\n>>> 1. STD::UNORDERED_MAP <<<";
    AdaptadorUnorderedMap<long long> tabla_stl(N);
    cargarDataset(tabla_stl, ruta_test, "user_id", limiteFilas);
    tabla_stl.imprimir();

    // 2. Tu Hashing Abierto
    cout << "\n>>> 2. HASHING ABIERTO (ENCADENAMIENTO) <<<";
    TablaHashingAbierto<long long> tabla_abierta(N);
    cargarDataset(tabla_abierta, ruta_test, "user_id", limiteFilas);
    tabla_abierta.imprimir();

    // 3. Tu Hashing Cerrado (Linear)
    cout << "\n>>> 3. HASHING CERRADO (LINEAR PROBING) <<<";
    TablaHashingCerrado<long long> tabla_linear(N, LINEAR_PROBING);
    cargarDataset(tabla_linear, ruta_test, "user_id", limiteFilas);
    tabla_linear.imprimir();

    // 4. Tu Hashing Cerrado (Quadratic)
    cout << "\n>>> 4. HASHING CERRADO (QUADRATIC PROBING) <<<";
    TablaHashingCerrado<long long> tabla_quadratic(N, QUADRATIC_PROBING);
    cargarDataset(tabla_quadratic, ruta_test, "user_id", limiteFilas);
    tabla_quadratic.imprimir();

    // 5. Tu Hashing Cerrado (Double Hashing)
    cout << "\n>>> 5. HASHING CERRADO (DOUBLE HASHING) <<<";
    TablaHashingCerrado<long long> tabla_double(N, DOUBLE_HASHING);
    cargarDataset(tabla_double, ruta_test, "user_id", limiteFilas);
    tabla_double.imprimir();

    return 0;
}