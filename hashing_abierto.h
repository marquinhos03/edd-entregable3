#pragma once

#include <string>
#include <vector>
#include <list>
#include <iostream>

template <typename CType>
struct EntradaAbierta {
    CType clave;
    int valor;

    EntradaAbierta(CType c, int v) : clave(c), valor(v) {}
};

template <typename CType>
class TablaHashingAbierto {
private:
    std::vector<std::list<EntradaAbierta<CType>>> tabla;
    int size;

    int funcionHash(CType clave) const;

public:
    TablaHashingAbierto(int s) : size(s) {
        tabla.resize(size);
    }

    void insertar(CType clave, int valor) {
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

    bool get(CType clave, int& resultado) const {
        int indice = funcionHash(clave);

        for (const auto& entrada : tabla[indice]) {
            if (entrada.clave == clave) {
                resultado = entrada.valor;
                return true;
            }
        }

        return false;
    }

    void remover(CType clave) {
        int indice = funcionHash(clave);

        for (auto it = tabla[indice].begin(); it != tabla[indice].end(); ++it) {
            if (it->clave == clave) {
                tabla[indice].erase(it);
                return;
            }
        }
    }

    void imprimir() const {
        std::cout << "\n--- Estado actual de la Tabla Hash (Abierto) ---" << std::endl;
        std::cout << "Índice\t(Clave, Valor)" << std::endl;
        std::cout << "---------------------------------" << std::endl;
        
        for (int i = 0; i < size; ++i) {
            std::cout << "[" << i << "] ";

            if (tabla[i].empty()) {
                std::cout << "VACIO";
            }
            else {
                for (const auto& entrada : tabla[i]) {
                    std::cout << "-> (" << entrada.clave << ", " << entrada.valor << ") ";
                }
            }

            std::cout << std::endl;
        }

        std::cout << "---------------------------------" << std::endl;
    }

};

// --- Función Hash para string (user_screen_name) ---

template <>
int TablaHashingAbierto<std::string>::funcionHash(std::string clave) const {
    long long h = 0;
    int a = 127;
    for (char v : clave) {
        h = (a * h + v) % size;
    }
    return h;
}

// --- Función Hash para long long (user_id) ---

template <>
int TablaHashingAbierto<long long>::funcionHash(long long clave) const {
    return clave % size;
}