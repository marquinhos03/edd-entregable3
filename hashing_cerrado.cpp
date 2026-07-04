#include "hashing_cerrado.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace std;

/**
 * @brief Función Hash para claves strings
 *
 * @param k Clave de tipo string que se desea convertir.
 * @param n Tamaño de la tabla hash.
 *
 * @return El índice calculado para la clave (un número entero entre 0 y n-1).
 */
int TablaHashingCerrado::h1(string k, int n) {
    long long h = 0;
    int a = 127;

    for (char v : k) {
        // Multiplicamos el acumulado, sumamos el ASCII, y aplicamos módulo
        h = (a * h + v) % n;
    }

    return h;
}

/**
 * @brief Función Hash (Double Hashing)
 *
 * @param k Clave de tipo string que se desea convertir.
 * @param n Tamaño de la tabla hash.
 *
 * @return Un número entero que representa el intervalo de salto para el double hashing.
 */
int TablaHashingCerrado::h2(string k, int n) {
    long long h = 0;
    int a = 31; // Un número primo distinto al 127 de h1

    // Calculamos un hash base distinto
    for (char v : k) {
        h = (a * h + v) % n;
    }

    // Sea R un número primo menor que el tamaño de la tabla "n"
    // Nota: se puede settear un número primo estático grande o calcular uno dinámicamente.
    int R = 97; 

    // Aplicamos la fórmula matemática para garantizar que el salto nunca sea 0 para evitar bucles infinitos. Se garantiza que el valor esté en el rango [1, R].
    int salto = R - (h % R);
    
    return salto;
}

int TablaHashingCerrado::linear_probing(string k, int n, int i) {
    return (h1(k, n) + i) % n;
}

int TablaHashingCerrado::quadratic_probing(string k, int n, int i) {
    return (h1(k, n) + i + 2 * i * i) % n;
}

int TablaHashingCerrado::double_hashing(string k, int n, int i) {
    return (h1(k, n) + i * h2(k, n)) % n;
}

int TablaHashingCerrado::calcularIndiceSondeo(string clave, int i, ProbingType probing_type) {
    switch (probing_type) {
        case LINEAR_PROBING:
            return linear_probing(clave, size, i);
        case QUADRATIC_PROBING:
            return quadratic_probing(clave, size, i);
        case DOUBLE_HASHING:
            return double_hashing(clave, size, i);
        default:
            throw std::invalid_argument("ProbingType (Tipo de sondeo) no reconocido.");
    }
}

void TablaHashingCerrado::insertar(string clave, int valor) {
    for (int i = 0; i < size; i++) {
        int indice = calcularIndiceSondeo(clave, i, probing_type);

        if (tabla[indice].estado == VACIO || tabla[indice].estado == BORRADO) {
            tabla[indice].clave = clave;
            tabla[indice].valor = valor;
            tabla[indice].estado = OCUPADO;
            return;
        }

        // Si ya existe, actualizar
        if (tabla[indice].estado == OCUPADO && tabla[indice].clave == clave) {
            tabla[indice].valor = valor;
            return;
        }
    }

    cout << "Tabla llena, no se pudo insertar " << clave << endl;
}

int TablaHashingCerrado::get(string clave) {
    for (int i = 0; i < size; i++) {
        int indice = calcularIndiceSondeo(clave, i, probing_type);

        if (tabla[indice].estado == VACIO) break;   // Ya no va a aparecer

        if (tabla[indice].estado == OCUPADO && tabla[indice].clave == clave) {
            return tabla[indice].valor;
        }
    }

    return -1;
}

void TablaHashingCerrado::remover(string clave) {
    for (int i = 0; i < size; i++) {
        int indice = calcularIndiceSondeo(clave, i, probing_type);

        if (tabla[indice].estado == VACIO) break;

        if (tabla[indice].estado == OCUPADO && tabla[indice].clave == clave) {
            tabla[indice].estado = BORRADO;
            return;
        }
    }
}

void TablaHashingCerrado::imprimir() {
    cout << "\n--- Estado actual de la Tabla ---" << endl;
    for (int i = 0; i < size; i++) {
        cout << "[" << i << "] ";
        
        if (tabla[i].estado == OCUPADO) {
            cout << "Clave: " << tabla[i].clave << "\t| Valor: " << tabla[i].valor;
        } else if (tabla[i].estado == VACIO) {
            cout << "VACIO";
        } else if (tabla[i].estado == BORRADO) {
            cout << "BORRADO";
        }
        
        cout << endl;
    }

    cout << "---------------------------------" << endl;
}