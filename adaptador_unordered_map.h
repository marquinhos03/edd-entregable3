#pragma once

#include <unordered_map>
#include <iostream>

/// @brief Clase Adaptadora para unordered_map (Patrón Adaptador) que unifica la interfaz con las implementaciones de tablas hash (abierto y cerrado).
/// @tparam CType Tipo de dato de la clave (ej. long long para user_id, o string para user_screen_name).
template <typename CType>
class AdaptadorUnorderedMap {
private:
    std::unordered_map<CType, int> tabla;

public:
    /// @brief Constructor que inicializa el adaptador pre-reservando memoria.
    /// @param size_hint Cantidad inicial de buckets a reservar para evitar el rehashing dinámico.
    AdaptadorUnorderedMap(int size_hint = 0) {
        if (size_hint > 0) {
            tabla.reserve(size_hint);
        }
    }

    /// @brief Inserta una entrada en la tabla o actualiza su valor si la clave ya existe.
    /// @param clave La clave de la entrada que se desea insertar o actualizar.
    /// @param valor Un entero asociado a la clave (conteo de tweets).
    void insertar(CType clave, int valor) {
        // En unordered_map, el operador [] inserta o actualiza automáticamente
        tabla[clave] = valor;
    }

    /// @brief Busca una clave en la tabla y recupera su valor asociado.
    /// @param clave La clave que se desea buscar.
    /// @param resultado Referencia a un entero donde se almacenará el valor en caso de éxito.
    /// @return true si la clave fue encontrada, false en caso de que no exista.
    bool get(CType clave, int& resultado) {
        auto it = tabla.find(clave);
        
        if (it != tabla.end()) {
            resultado = it->second;
            return true;
        }
        return false;
    }

    /// @brief Imprime todos los pares (Clave, Valor) almacenados actualmente en la tabla.
    void imprimir() {
        std::cout << "\n--- Estado actual de unordered_map ---" << std::endl;
        std::cout << "(Clave, Valor)" << std::endl;
        std::cout << "---------------------------------" << std::endl;
        
        for (const auto& par : tabla) {
            std::cout << "(" << par.first << ", " << par.second << ") "<< std::endl;
        }
        std::cout << "---------------------------------" << std::endl;
    }

    /// @brief Calcula una estimación del espacio de memoria total consumido por la estructura de datos.
    /// @return size_t Cantidad total de memoria ocupada por la estructura (expresada en bytes).
    size_t getMemoriaBytes() const {
        // Tamaño de la clase + (cantidad de buckets * tamaño de puntero) + (cantidad de elementos * tamaño del nodo)
        size_t memoria_buckets = tabla.bucket_count() * sizeof(void*);
        size_t memoria_elementos = tabla.size() * (sizeof(std::pair<const CType, int>) + sizeof(void*) + sizeof(size_t));
        return sizeof(*this) + memoria_buckets + memoria_elementos;
    }
};