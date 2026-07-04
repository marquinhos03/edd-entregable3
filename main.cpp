// Compilación Linux: g++ main.cpp -o main
// Ejecución Linux: ./main

#include "hashing_cerrado.h"
#include <iostream>
#include "extern/csv.h"

using namespace std;

int main() {
    int N = 40;
    // factor de carga: alfa = n / N
    // En esta prueba, alfa = 0.5 (no cumple alfa < 0.5)
    // Número de pruebas esperado con direccionamiento abierto = 1 / (1 - alfa) = 2

    //TablaHashingCerrado<string> tabla_user_screen_name(N, LINEAR_PROBING);
    TablaHashingCerrado<long long> tabla_user_id(N, LINEAR_PROBING);

    io::CSVReader<1, io::trim_chars<' ', '\t'>, io::double_quote_escape<',', '\"'>> in("datasets/auspol2019.csv");

    //in.read_header(io::ignore_extra_column, "user_screen_name");
    in.read_header(io::ignore_extra_column, "user_id");

    //string user_screen_name;
    long long user_id;
    int limiteFilas = 20;
    int filasProcesadas = 0;
    int filasSaltadas = 0;

    cout << "Iniciando lectura del dataset (Límite: " << limiteFilas << " filas)..." << endl << endl;

    bool leyendo = true;

    while (leyendo && filasProcesadas < limiteFilas) {
        try {
            // Intentamos leer la fila
            //leyendo = in.read_row(user_screen_name);
            leyendo = in.read_row(user_id);
            
            // Si la lectura fue exitosa y aun quedan lineaws por leer
            if (leyendo) {
                //int conteo_actual = tabla_user_screen_name.get(user_screen_name);
                int conteo_actual = tabla_user_id.get(user_id);

                if (conteo_actual != -1) {
                    //tabla_user_screen_name.insertar(user_screen_name, conteo_actual + 1);
                    tabla_user_id.insertar(user_id, conteo_actual + 1);
                } else {
                    //tabla_user_screen_name.insertar(user_screen_name, 1);
                    tabla_user_id.insertar(user_id, 1);
                }
                
                filasProcesadas++; // Solo contamos las filas validas
            }
        } 
        catch (const std::exception& e) {
            // Error capturado (seguir leyendo sin detener la ejecución)
            filasSaltadas++;
            // cout << "Fila saltada por formato inválido: " << e.what() << endl;
        }
    }

    //tabla_user_screen_name.imprimir();
    tabla_user_id.imprimir();

    cout << "\nLectura finalizada." << endl;
    cout << "- Filas procesadas correctamente: " << filasProcesadas << endl;
    cout << "- Filas descartadas por formato invalido: " << filasSaltadas << endl;

    return 0;
}