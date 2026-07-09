#pragma once

#include <string>
#include <vector>
#include <list>
#include <iostream>

/// @brief Struct que representa una entrada individual dentro de la tabla hash abierta (nodo de la lista enlazada).
/// @tparam CType Tipo de dato de la clave (ej. long long para user_id o string para user_screen_name).
template <typename CType>
struct EntradaAbierta {
    CType clave;
    int valor;

    EntradaAbierta(CType c, int v) : clave(c), valor(v) {}
};

/// @brief Implementación de Tabla Hash con hashing abierto.
/// @tparam CType Tipo de dato de la clave.
template <typename CType>
class TablaHashingAbierto {
private:
    std::vector<std::list<EntradaAbierta<CType>>> tabla;
    int size;

    int funcionHash(CType clave) const;

public:
    /// @brief Constructor que inicializa la tabla hash.
    /// @param s Tamaño inicial del vector principal.
    TablaHashingAbierto(int s) : size(s) {
        tabla.resize(size);
    }

    /// @brief Inserta una entrada en la tabla o actualiza su valor si la clave ya existe.
    /// @param clave La clave de la entrada que se desea insertar o actualizar.
    /// @param valor Un entero asociado a la clave (conteo de tweets).
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

    /// @brief Busca una clave en la tabla y recupera su valor asociado.
    /// @param clave La clave que se desea buscar.
    /// @param resultado Referencia a un entero donde se almacenará el valor en caso de éxito.
    /// @return true si la clave fue encontrada, false en caso de que no exista.
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

    /// @brief Elimina una entrada de la tabla buscando por su clave.
    /// @param clave La clave de la entrada que se desea eliminar.
    void remover(CType clave) {
        int indice = funcionHash(clave);

        for (auto it = tabla[indice].begin(); it != tabla[indice].end(); ++it) {
            if (it->clave == clave) {
                tabla[indice].erase(it);
                return;
            }
        }
    }

    /// @brief Imprime todos los pares (Clave, Valor) almacenados actualmente en la tabla.
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

    /// @brief Calcula una estimación del espacio de memoria total consumido por la estructura de datos.
    /// @return size_t Cantidad total de memoria ocupada por la estructura (expresada en bytes).
    size_t getMemoriaBytes() const {
        // Tamaño base + tamaño pre-reservado del vector de listas
        size_t total = sizeof(*this) + tabla.capacity() * sizeof(std::list<EntradaAbierta<CType>>);
        
        // Sumar el tamaño de los nodos dinámicos (list usa 2 punteros extras por nodo)
        for (int i = 0; i < size; ++i) {
            total += tabla[i].size() * (sizeof(EntradaAbierta<CType>) + 2 * sizeof(void*));
        }
        return total;
    }

};

/// @brief Función hash para claves de tipo string (user_screen_name) usando un hash polinomial.
template <>
int TablaHashingAbierto<std::string>::funcionHash(std::string clave) const {
    long long h = 0;
    int a = 127;
    for (char v : clave) {
        h = (a * h + v) % size;
    }
    return h;
}

/// @brief Especialización de la función hash para claves de tipo long long (user_id)
template <>
int TablaHashingAbierto<long long>::funcionHash(long long clave) const {
    return clave % size;
}