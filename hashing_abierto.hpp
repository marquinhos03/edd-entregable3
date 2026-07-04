#pragma once

#include <string>
#include <vector>
#include <list>

struct Entrada {
    int clave;
    std::string valor;

    Entrada(int c, std::string v) : clave(c), valor(v) {}
};

class TablaHashingAbierto {
private:
    std::vector<std::list<Entrada>> tabla;
    int size;

    int funcionHash(int clave) const;

public:
    TablaHashingAbierto(int tablaSize) : size(tablaSize) {
        tabla.resize(size);
    }

    void insertar(int clave, std::string valor);

    bool get(int clave, std::string& resultado) const;

    void remover(int clave);
};