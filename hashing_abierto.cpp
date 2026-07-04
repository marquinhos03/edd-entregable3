#include "hashing_abierto.hpp"
#include <iostream>

using namespace std;

int TablaHashingAbierto::funcionHash(int clave) const {
    return clave % size;
}

void TablaHashingAbierto::insertar(int clave, string valor) {
    int indice = funcionHash(clave);

    // Si la clave ya existe, actualizamos el valor
    for (auto& entrada : tabla[indice]) {
        if (entrada.clave == clave) {
            entrada.valor = valor;
            return;
        }
    }

    // Si no existe, la agregamos al final
    tabla[indice].emplace_back(clave, valor);
}

bool TablaHashingAbierto::get(int clave, string& resultado) const {
    int indice = funcionHash(clave);

    for (const auto& entrada : tabla[indice]) {
        if (entrada.clave == clave) {
            resultado = entrada.valor;
            return true;
        }
    }

    return false;
}

void TablaHashingAbierto::remover(int clave) {
    int indice = funcionHash(clave);

    for (auto it = tabla[indice].begin(); it != tabla[indice].end(); ++it) {
        if (it->clave == clave) {
            return;
        }
    }
}
