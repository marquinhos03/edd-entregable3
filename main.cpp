#include "hashing_cerrado.hpp"
#include <iostream>
#include "extern/csv.h"

using namespace std;

int main() {
    int N = 40;
    // factor de carga: alfa = n / N
    // En esta prueba, alfa = 0.5 (no cumple alfa < 0.5)
    // Número de pruebas esperado con direccionamiento abierto = 1 / (1 - alfa) = 2
    TablaHashingCerrado tablaTweets(N, LINEAR_PROBING);

    io::CSVReader<1, io::trim_chars<' ', '\t'>, io::double_quote_escape<',', '\"'>> in("datasets/auspol2019.csv");
    in.read_header(io::ignore_extra_column, "user_screen_name");

    string user_screen_name;
    int limiteFilas = 20;
    int filasProcesadas = 0;
    int filasSaltadas = 0;

    cout << "Iniciando lectura del dataset (Límite: " << limiteFilas << " filas)..." << endl << endl;

    bool leyendo = true;

    while (leyendo && filasProcesadas < limiteFilas) {
        try {
            // Intentamos leer la fila
            leyendo = in.read_row(user_screen_name);
            
            // Si la lectura fue exitosa y aun quedan lineaws por leer
            if (leyendo) {
                int conteo_actual = tablaTweets.get(user_screen_name);

                if (conteo_actual != -1) {
                    tablaTweets.insertar(user_screen_name, conteo_actual + 1);
                } else {
                    tablaTweets.insertar(user_screen_name, 1);
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

    tablaTweets.imprimir();

    cout << "\nLectura finalizada." << endl;
    cout << "- Filas procesadas correctamente: " << filasProcesadas << endl;
    cout << "- Filas descartadas por formato invalido: " << filasSaltadas << endl;

    return 0;
}