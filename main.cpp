// Compilación (Windows/Linux): 
// g++ main.cpp -o main
//
// Ejecución de un experimento individual: 
// ./main <tipo_tabla> <tipo_clave>       (Linux/Mac)
// .\main.exe <tipo_tabla> <tipo_clave>   (Windows/PowerShell)
// (Ej: .\main.exe abierto id)
//
// Ejecución automatizada de todo el estudio experimental (Linux/Mac):
// chmod +x run_experiments.sh
// ./run_experiments.sh
//
// Ejecución automatizada de todo el estudio experimental (Windows/PowerShell):
// Set-ExecutionPolicy Bypass -Scope Process -Force; .\run_experiments.ps1

#include <iostream>
#include <string>
#include <vector>
#include "extern/csv.h"
#include "utilidades.h"
#include "experimentos.h"

using namespace std;

int main(int argc, char** argv) {
    // Si no hay suficientes argumentos, terminamos la ejecución
    if (argc < 3) {
        cerr << "Uso: " << argv[0] << " <tipo_tabla> <tipo_clave>" << endl;
        cerr << "   tipo_tabla validos: unordered_map, abierto, cerrado_linear, cerrado_quadratic, cerrado_double" << endl;
        cerr << "   tipo_clave validos: id, name" << endl;
        exit(1);
    }

    string tipo_tabla = argv[1];
    string tipo_clave = argv[2];

    vector<long long> datos_id;
    vector<string> datos_name;
    const string ruta_csv = "datasets/auspol2019.csv";

    // CARGA DE DATOS
    if (tipo_clave == "id") {
        cargarVector(datos_id, ruta_csv, "user_id");
    } else if (tipo_clave == "name") {
        cargarVector(datos_name, ruta_csv, "user_screen_name");
    } else {
        cerr << "tipo_clave no reconocida." << endl;
        exit(1);
    }

    // EJECUCIÓN DE EXPERIMENTO PARA EL tipo_tabla SOLICITADO
    ejecutar_experimento(tipo_tabla, tipo_clave, datos_id, datos_name);

    return 0;
}