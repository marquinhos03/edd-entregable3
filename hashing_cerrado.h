#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

enum Estado { VACIO, OCUPADO, BORRADO };

enum ProbingType { LINEAR_PROBING, QUADRATIC_PROBING, DOUBLE_HASHING };

template <typename CType>
struct EntradaCerrada {
    CType clave;
    int valor;
    Estado estado;

    EntradaCerrada() : valor(0), estado(VACIO) {}
};

template <typename CType>
class TablaHashingCerrado {
private:
    std::vector<EntradaCerrada<CType>> tabla;
    int size;
    ProbingType probing_type;

    int h1(CType k, int n);
    int h2(CType k, int n);

    int linear_probing(CType k, int n, int i) {
        return (h1(k, n) + i) % n;
    }

    int quadratic_probing(CType k, int n, int i) {
        return (h1(k, n) + i + 2 * i * i) % n;
    }

    int double_hashing(CType k, int n, int i) {
        return (h1(k, n) + i * h2(k, n)) % n;
    }

    int calcularIndiceSondeo(CType clave, int i) {
        switch (probing_type) {
            case LINEAR_PROBING: return linear_probing(clave, size, i);
            case QUADRATIC_PROBING: return quadratic_probing(clave, size, i);
            case DOUBLE_HASHING: return double_hashing(clave, size, i);
            default: throw std::invalid_argument("ProbingType (Tipo de sondeo) no reconocido.");
        }
    }

public:
    TablaHashingCerrado(int s, ProbingType pt) : size(s), probing_type(pt) {
        tabla.resize(size);
    }

    void insertar(CType clave, int valor) {
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

        std::cout << "Tabla llena, no se pudo insertar " << clave << std::endl;
    }

    bool get(CType clave, int& resultado) {
        for (int i = 0; i < size; i++) {
            int indice = calcularIndiceSondeo(clave, i);

            if (tabla[indice].estado == VACIO) break;   

            if (tabla[indice].estado == OCUPADO && tabla[indice].clave == clave) {
                resultado = tabla[indice].valor;
                return true;
            }
        }

        return false;
    }

    void remover(CType clave) {
        for (int i = 0; i < size; i++) {
            int indice = calcularIndiceSondeo(clave, i);

            if (tabla[indice].estado == VACIO) break;

            if (tabla[indice].estado == OCUPADO && tabla[indice].clave == clave) {
                tabla[indice].estado = BORRADO;
                return;
            }
        }
    }

    void imprimir() const {
        std::cout << "\n--- Estado actual de la Tabla Hash (Cerrado) ---" << std::endl;
        std::cout << "Índice\t(Clave, Valor)" << std::endl;
        std::cout << "---------------------------------" << std::endl;

        for (int i = 0; i < size; i++) {
            std::cout << "[" << i << "]\t";
            
            if (tabla[i].estado == OCUPADO) {
                std::cout << "(" << tabla[i].clave << ", " << tabla[i].valor << ") ";
            } else if (tabla[i].estado == VACIO) {
                std::cout << "VACIO";
            } else if (tabla[i].estado == BORRADO) {
                std::cout << "BORRADO";
            }
            
            std::cout << std::endl;
        }

        std::cout << "---------------------------------" << std::endl;
    }

};

// --- Función Hash para string (user_screen_name) ---

/**
 * @brief Función Hash para claves strings
 *
 * @param k Clave de tipo string que se desea convertir.
 * @param n Tamaño de la tabla hash.
 *
 * @return El índice calculado para la clave (un número entero entre 0 y n-1).
 */
template <>
int TablaHashingCerrado<std::string>::h1(std::string k, int n) {
    long long h = 0;
    int a = 127;
    for (char v : k) {
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
template <>
int TablaHashingCerrado<std::string>::h2(std::string k, int n) {
    long long h = 0;
    int a = 31; 
    for (char v : k) {
        h = (a * h + v) % n;
    }
    int R = 97; 
    return R - (h % R);
}

// --- Función Hash para long long (user_id) ---

template <>
int TablaHashingCerrado<long long>::h1(long long k, int n) {
    return k % n;
}

template <>
int TablaHashingCerrado<long long>::h2(long long k, int n) {
    int R = 97; 
    return R - (k % R);
}