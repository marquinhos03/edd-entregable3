// Compilación (Windows/Linux): 
// g++ main.cpp -o main
//
// Ejecución de un experimento individual: 
// ./main <algoritmo> <tipo_clave>       (Linux/Mac)
// .\main.exe <algoritmo> <tipo_clave>   (Windows/PowerShell)
// (Ej: .\main.exe abierto id)
//
// Ejecución automatizada de todo el estudio experimental (Linux/Mac):
// chmod +x run_experiments.sh
// ./run_experiments.sh
//
// Ejecución automatizada de todo el estudio experimental (Windows/PowerShell):
// Set-ExecutionPolicy Bypass -Scope Process -Force; .\run_experiments.ps1

#include <iostream>
<<<<<<< Updated upstream
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

=======
#include <string>
#include <vector>
#include "extern/csv.h"
#include "experimentos.h"

using namespace std;

int main(int argc, char** argv) {
    // Si no hay suficientes argumentos, terminamos la ejecución
    if (argc < 3) {
        cerr << "Uso: " << argv[0] << " <algoritmo> <tipo_clave>" << endl;
        cerr << "Algoritmos validos: unordered_map, abierto, cerrado_linear, cerrado_quadratic, cerrado_double" << endl;
        cerr << "Tipos de clave validos: id, name" << endl;
        exit(1);
    }

    string algoritmo = argv[1];
    string tipo_clave = argv[2];

    // Cargar los datos dependiendo del tipo de clave solicitada
    io::CSVReader<1, io::trim_chars<' ', '\t'>, io::double_quote_escape<',', '\"'>> in("datasets/auspol2019.csv");

    vector<long long> datos_id;
    vector<string> datos_name;

    if (tipo_clave == "id") {
        in.read_header(io::ignore_extra_column, "user_id"); 
        long long id_temporal;
        while (true) {
            try {
                if (!in.read_row(id_temporal)) break;
                datos_id.push_back(id_temporal);
            } catch (...) { /* Ignorar filas corruptas */ }
        }
    } else if (tipo_clave == "name") {
        in.read_header(io::ignore_extra_column, "user_screen_name"); 
        string name_temporal;
        while (true) {
            try {
                if (!in.read_row(name_temporal)) break;
                datos_name.push_back(name_temporal);
            } catch (...) { /* Ignorar filas corruptas */ }
        }
    } else {
        cerr << "Tipo de clave no reconocido." << endl;
        exit(1);
    }

    // Ejecutar el algoritmo solicitado
    if (algoritmo == "unordered_map") {
        if (tipo_clave == "id") run_unordered_map(datos_id, algoritmo, tipo_clave);
        else run_unordered_map(datos_name, algoritmo, tipo_clave);
    } 
    else if (algoritmo == "abierto") {
        if (tipo_clave == "id") run_hashing_abierto(datos_id, algoritmo, tipo_clave);
        else run_hashing_abierto(datos_name, algoritmo, tipo_clave);
    } 
    else if (algoritmo == "cerrado_linear") {
        if (tipo_clave == "id") run_hashing_cerrado(datos_id, LINEAR_PROBING, algoritmo, tipo_clave);
        else run_hashing_cerrado(datos_name, LINEAR_PROBING, algoritmo, tipo_clave);
    }
    else if (algoritmo == "cerrado_quadratic") {
        if (tipo_clave == "id") run_hashing_cerrado(datos_id, QUADRATIC_PROBING, algoritmo, tipo_clave);
        else run_hashing_cerrado(datos_name, QUADRATIC_PROBING, algoritmo, tipo_clave);
    }
    else if (algoritmo == "cerrado_double") {
        if (tipo_clave == "id") run_hashing_cerrado(datos_id, DOUBLE_HASHING, algoritmo, tipo_clave);
        else run_hashing_cerrado(datos_name, DOUBLE_HASHING, algoritmo, tipo_clave);
    }
    else {
        cerr << "Algoritmo no reconocido." << endl;
        exit(1);
    }
>>>>>>> Stashed changes

    return 0;
}