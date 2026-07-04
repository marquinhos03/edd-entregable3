#pragma once

#include <vector>
#include <string>

enum Estado { VACIO, OCUPADO, BORRADO };

struct Entrada {
    int clave;
    std::string valor;
    Estado estado;

    Entrada() : clave(0), valor(""), estado(VACIO) {}
};

class TablaHashingCerrado {
private:
    std::vector<Entrada> tabla;
    int size;

    int h1(int k, int n);
    int h2(int k, int n);

    int linear_probing(int k, int n, int i);
    int quadratic_probing(int k, int n, int i);
    int double_hashing(int k, int n, int i);

public:
    TablaHashingCerrado(int tablaSize) : size(tablaSize) {
        tabla.resize(size);
    }

    int calcularIndiceSondeo(int clave, int i);

    void insertar(int clave, std::string valor);

    std::string get(int clave);

    void remover(int clave);

    void imprimir();
};