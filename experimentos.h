#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <unordered_map>
#include "hashing_cerrado.h"
#include "hashing_abierto.h"

using namespace std;

// --- Prueba Unordered Map ---
template <typename K>
void run_unordered_map(const vector<K>& datos, const string& nombre_metodo, const string& tipo_clave) {
    unordered_map<K, int> tabla;
    int filasProcesadas = 0;
    int proximo_hito = 10000;

    auto start = chrono::high_resolution_clock::now();

    for (const K& clave : datos) {
        tabla[clave]++;
        filasProcesadas++;

        if (filasProcesadas == proximo_hito) {
            auto end = chrono::high_resolution_clock::now();
            double running_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            running_time *= 1e-9; // Convertir a segundos, igual que en el heapsort_v2

            cout << nombre_metodo << ";" << tipo_clave << ";" << filasProcesadas << ";" << running_time << "\n";
            proximo_hito += 10000;
        }
    }
}

// --- Prueba Hashing Abierto ---
template <typename K>
void run_hashing_abierto(const vector<K>& datos, const string& nombre_metodo, const string& tipo_clave) {
    int N = 100003; 
    TablaHashingAbierto<K> tabla(N);
    int filasProcesadas = 0;
    int proximo_hito = 10000;

    auto start = chrono::high_resolution_clock::now();

    for (const K& clave : datos) {
        int conteo_actual;
        if (tabla.get(clave, conteo_actual)) {
            tabla.insertar(clave, conteo_actual + 1);
        } else {
            tabla.insertar(clave, 1);
        }
        filasProcesadas++;

        if (filasProcesadas == proximo_hito) {
            auto end = chrono::high_resolution_clock::now();
            double running_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            running_time *= 1e-9;

            cout << nombre_metodo << ";" << tipo_clave << ";" << filasProcesadas << ";" << running_time << "\n";
            proximo_hito += 10000;
        }
    }
}

// --- Prueba Hashing Cerrado ---
template <typename K>
void run_hashing_cerrado(const vector<K>& datos, ProbingType tipo_sondeo, const string& nombre_metodo, const string& tipo_clave) {
    int N = 200003; 
    TablaHashingCerrado<K> tabla(N, tipo_sondeo);
    int filasProcesadas = 0;
    int proximo_hito = 10000;

    auto start = chrono::high_resolution_clock::now();

    for (const K& clave : datos) {
        int conteo_actual = tabla.get(clave);
        if (conteo_actual != -1) {
            tabla.insertar(clave, conteo_actual + 1);
        } else {
            tabla.insertar(clave, 1);
        }
        filasProcesadas++;

        if (filasProcesadas == proximo_hito) {
            auto end = chrono::high_resolution_clock::now();
            double running_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            running_time *= 1e-9;

            cout << nombre_metodo << ";" << tipo_clave << ";" << filasProcesadas << ";" << running_time << "\n";
            proximo_hito += 10000;
        }
    }
}