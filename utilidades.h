#pragma once

#include <iostream>
#include <string>
#include "extern/csv.h"

/**
 * @brief Función de utilidad para cargar el dataset en la tabla hash.
 *
 * @tparam TType Clase template de la tabla hash (ej. TablaHashingCerrado o TablaHashingAbierto).
 * @tparam CType Tipo de dato de la clave (ej. long long o string).
 *
 */
template <template <typename> class TType, typename CType>
void cargarDataset(
    TType<CType>& tabla,
    const std::string& ruta_archivo,
    const std::string& nombre_columna,
    int limiteFilas
) {

    // Configuramos el lector CSV
    io::CSVReader<1, io::trim_chars<' ', '\t'>, io::double_quote_escape<',', '\"'>> in(ruta_archivo);
    in.read_header(io::ignore_extra_column, nombre_columna);

    CType clave;
    int filasProcesadas = 0;
    int filasSaltadas = 0;

    std::cout << "Iniciando lectura del dataset para la columna '" << nombre_columna 
              << "' (Límite: " << limiteFilas << " filas)..." << std::endl << std::endl;

    bool leyendo = true;

    while (leyendo && filasProcesadas < limiteFilas) {
        try {
            // Intentamos leer la fila
            leyendo = in.read_row(clave);

            // Si la lectura fue exitosa y aun quedan lineas por leer
            if (leyendo) {
                contarTweets(tabla, clave);

                filasProcesadas++;  // Contar las filas válidas
            }
        } 
        catch (const std::exception& e) {
            // Error capturado (seguir leyendo sin detener la ejecución)
            filasSaltadas++;    // Contar las filas inválidas

            // cout << "Fila saltada por formato inválido: " << e.what() << endl;
        }
    }

    std::cout << "\nLectura finalizada." << std::endl;
    std::cout << "- Filas procesadas correctamente: " << filasProcesadas << std::endl;
    std::cout << "- Filas descartadas por formato invalido: " << filasSaltadas << std::endl;
}


/**
 * @brief Función auxiliar para contar cuántos tweets publico cada usuario.
 * El valor asociado a cada clave será un entero correspondiente a la cantidad de tweets que ese usuario publicó.
 *
 * @tparam TType Clase template de la tabla hash (ej. TablaHashingCerrado o TablaHashingAbierto).
 * @tparam CType Tipo de dato de la clave (ej. long long o string).
 *
 * @param H Tabla hash
 * @param k Clave (ej. user_id o user_screen_name)
 */
template <template <typename> class TType, typename CType>
void contarTweets(TType<CType>& H, const CType& k) {
    int conteo_actual = 0;
    
    // get retorna true si "k" está en "H"
    if (H.get(k, conteo_actual)) {
        H.insertar(k, conteo_actual + 1);
    }
    else {
        H.insertar(k, 1);
    }
}