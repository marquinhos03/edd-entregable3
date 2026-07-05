#pragma once

#include <unordered_map>
#include <iostream>

template <typename CType>
class AdaptadorUnorderedMap {
private:
    std::unordered_map<CType, int> tabla;

public:
    // El constructor recibe el tamaño para pre-reservar espacio y evitar rehashing innecesario
    AdaptadorUnorderedMap(int size_hint = 0) {
        if (size_hint > 0) {
            tabla.reserve(size_hint);
        }
    }

    void insertar(CType clave, int valor) {
        // En unordered_map, el operador [] inserta o actualiza automáticamente
        tabla[clave] = valor;
    }

    bool get(CType clave, int& resultado) {
        auto it = tabla.find(clave);
        
        if (it != tabla.end()) {
            resultado = it->second;
            return true;
        }
        return false;
    }

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