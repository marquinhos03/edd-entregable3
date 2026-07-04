#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <unordered_map>
#include "hashing_cerrado.h"
#include "hashing_abierto.h"
#include "utilidades.h"

// --- Prueba Unordered Map ---
template <typename K>
void run_unordered_map(const std::vector<K>& datos, const std::string& nombre_metodo, const std::string& tipo_clave) {
    std::unordered_map<K, int> tabla;
    int filasProcesadas = 0;
    int proximo_hito = 10000;

    auto start = std::chrono::high_resolution_clock::now();

    for (const K& clave : datos) {
        tabla[clave]++;
        filasProcesadas++;

        if (filasProcesadas == proximo_hito) {
            auto end = std::chrono::high_resolution_clock::now();
            double running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            running_time *= 1e-9; // Convertir a segundos, igual que en el heapsort_v2

            std::cout << nombre_metodo << ";" << tipo_clave << ";" << filasProcesadas << ";" << running_time << "\n";
            proximo_hito += 10000;
        }
    }
}

// --- Prueba Hashing Abierto ---
template <typename K>
void run_hashing_abierto(const std::vector<K>& datos, const std::string& nombre_metodo, const std::string& tipo_clave) {
    int N = 100003; 
    TablaHashingAbierto<K> tabla(N);
    int filasProcesadas = 0;
    int proximo_hito = 10000;

    auto start = std::chrono::high_resolution_clock::now();

    for (const K& clave : datos) {
        contarTweets(tabla, clave); 
        filasProcesadas++;

        if (filasProcesadas == proximo_hito) {
            auto end = std::chrono::high_resolution_clock::now();
            double running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            running_time *= 1e-9;

            std::cout << nombre_metodo << ";" << tipo_clave << ";" << filasProcesadas << ";" << running_time << "\n";
            proximo_hito += 10000;
        }
    }
}

// --- Prueba Hashing Cerrado ---
template <typename K>
void run_hashing_cerrado(const std::vector<K>& datos, ProbingType tipo_sondeo, const std::string& nombre_metodo, const std::string& tipo_clave) {
    int N = 200003; 
    TablaHashingCerrado<K> tabla(N, tipo_sondeo);
    int filasProcesadas = 0;
    int proximo_hito = 10000;

    auto start = std::chrono::high_resolution_clock::now();

    for (const K& clave : datos) {
        contarTweets(tabla, clave); 
        filasProcesadas++;

        if (filasProcesadas == proximo_hito) {
            auto end = std::chrono::high_resolution_clock::now();
            double running_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            running_time *= 1e-9;

            std::cout << nombre_metodo << ";" << tipo_clave << ";" << filasProcesadas << ";" << running_time << "\n";
            proximo_hito += 10000;
        }
    }
}