#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include "adaptador_unordered_map.h"
#include "hashing_cerrado.h"
#include "hashing_abierto.h"
#include "utilidades.h"

template <typename TType, typename CType>
void medir_rendimiento(
    TType& tabla,
    const std::vector<CType>& datos,
    const std::string& nombre_metodo,
    const std::string& tipo_clave
) {
    int filasProcesadas = 0;
    int proximo_hito = 10000;

    auto start = std::chrono::high_resolution_clock::now();

    for (const CType& clave : datos) {
        contarTweets(tabla, clave); 
        filasProcesadas++;

        if (filasProcesadas == proximo_hito) {
            auto end = std::chrono::high_resolution_clock::now();
            double running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            running_time *= 1e-9;   // Segundos
            size_t espacio_bytes = tabla.getMemoriaBytes();

            std::cout << nombre_metodo << ";"
                << tipo_clave << ";"
                << filasProcesadas << ";"
                << running_time << ";"
                << espacio_bytes << std::endl;
            
            proximo_hito += 10000;
        }
    }
}

// --- Prueba Unordered Map ---
template <typename K>
void run_unordered_map(const std::vector<K>& datos, const std::string& nombre_metodo, const std::string& tipo_clave) {
    int N = 200003;
    AdaptadorUnorderedMap<K> tabla(N); 
    medir_rendimiento(tabla, datos, nombre_metodo, tipo_clave);
}

// --- Prueba Hashing Abierto ---
template <typename K>
void run_hashing_abierto(const std::vector<K>& datos, const std::string& nombre_metodo, const std::string& tipo_clave) {
    int N = 100003;
    TablaHashingAbierto<K> tabla(N);
    medir_rendimiento(tabla, datos, nombre_metodo, tipo_clave);
}

// --- Prueba Hashing Cerrado ---
template <typename K>
void run_hashing_cerrado(const std::vector<K>& datos, ProbingType tipo_sondeo, const std::string& nombre_metodo, const std::string& tipo_clave) {
    int N = 200003;
    TablaHashingCerrado<K> tabla(N, tipo_sondeo);
    medir_rendimiento(tabla, datos, nombre_metodo, tipo_clave);
}

void ejecutar_experimento(
    const std::string& tipo_tabla, 
    const std::string& tipo_clave, 
    const std::vector<long long>& datos_id, 
    const std::vector<std::string>& datos_name
) {
    if (tipo_tabla == "unordered_map") {
        if (tipo_clave == "id") run_unordered_map(datos_id, tipo_tabla, tipo_clave);
        else run_unordered_map(datos_name, tipo_tabla, tipo_clave);
    } 
    else if (tipo_tabla == "abierto") {
        if (tipo_clave == "id") run_hashing_abierto(datos_id, tipo_tabla, tipo_clave);
        else run_hashing_abierto(datos_name, tipo_tabla, tipo_clave);
    } 
    else if (tipo_tabla == "cerrado_linear") {
        if (tipo_clave == "id") run_hashing_cerrado(datos_id, LINEAR_PROBING, tipo_tabla, tipo_clave);
        else run_hashing_cerrado(datos_name, LINEAR_PROBING, tipo_tabla, tipo_clave);
    }
    else if (tipo_tabla == "cerrado_quadratic") {
        if (tipo_clave == "id") run_hashing_cerrado(datos_id, QUADRATIC_PROBING, tipo_tabla, tipo_clave);
        else run_hashing_cerrado(datos_name, QUADRATIC_PROBING, tipo_tabla, tipo_clave);
    }
    else if (tipo_tabla == "cerrado_double") {
        if (tipo_clave == "id") run_hashing_cerrado(datos_id, DOUBLE_HASHING, tipo_tabla, tipo_clave);
        else run_hashing_cerrado(datos_name, DOUBLE_HASHING, tipo_tabla, tipo_clave);
    }
    else {
        std::cerr << "tipo_tabla no reconocida." << std::endl;
        exit(1);
    }
}