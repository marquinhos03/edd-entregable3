#include "hashing_cerrado.hpp"
#include <iostream>
#include <cmath>

using namespace std;

int TablaHashingCerrado::h1(int k, int n) {
    return k % n;
}

int TablaHashingCerrado::h2(int k, int n) {
    float A = (sqrt(5) - 1) / 2;

    float a = (float)k * A;
    a -= (int)a;
    return n * a;
}

int TablaHashingCerrado::linear_probing(int k, int n, int i) {
    return (h1(k, n) + i) % n;
}

int TablaHashingCerrado::quadratic_probing(int k, int n, int i) {
    return (h1(k, n) + i + 2 * i * i) % n;
}

int TablaHashingCerrado::double_hashing(int k, int n, int i) {
    return (h1(k, n) + i * h2(k, n)) % n;
}

// Usa la técnica que desees aquí (solo cambia el nombre de la función de sondeo)
int TablaHashingCerrado::calcularIndiceSondeo(int clave, int i) {
    return linear_probing(clave, size, i);
    // return quadratic_probing(key, size, i);
    // return double_hashing(key, size, i);
}

void TablaHashingCerrado::insertar(int clave, string valor) {
    for (int i = 0; i < size; i++) {
        int indice = calcularIndiceSondeo(clave, i);

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

string TablaHashingCerrado::get(int clave) {
    for (int i = 0; i < size; i++) {
        int indice = calcularIndiceSondeo(clave, i);

        if (tabla[indice].estado == VACIO) break;   // Ya no va a aparecer

        if (tabla[indice].estado == OCUPADO && tabla[indice].clave == clave) {
            return tabla[indice].valor;
        }
    }

    return "No encontrado";
}

void TablaHashingCerrado::remover(int clave) {
    for (int i = 0; i < size; i++) {
        int indice = calcularIndiceSondeo(clave, i);

        if (tabla[indice].estado == VACIO) break;

        if (tabla[indice].estado == OCUPADO && tabla[indice].clave == clave) {
            tabla[indice].estado = BORRADO;
            return;
        }
    }
}

void TablaHashingCerrado::imprimir() {
    cout << "\n--- Estado actual de la Tabla ---\n";
    for (int i = 0; i < size; i++) {
        std::cout << "[" << i << "] ";
        
        if (tabla[i].estado == OCUPADO) {
            std::cout << "Clave: " << tabla[i].clave << "\t| Valor: " << tabla[i].valor;
        } else if (tabla[i].estado == VACIO) {
            std::cout << "VACIO";
        } else if (tabla[i].estado == BORRADO) {
            std::cout << "BORRADO";
        }
        
        cout << endl;
    }

    std::cout << "---------------------------------\n";
}