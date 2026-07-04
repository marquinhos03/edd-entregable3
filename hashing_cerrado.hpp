#pragma once

#include <vector>
#include <string>

enum Estado { VACIO, OCUPADO, BORRADO };

enum ProbingType { LINEAR_PROBING, QUADRATIC_PROBING, DOUBLE_HASHING };

struct Entrada {
    std::string clave;
    int valor;
    Estado estado;

    Entrada() : clave(""), valor(0), estado(VACIO) {}
};

class TablaHashingCerrado {
private:
    std::vector<Entrada> tabla;
    int size;
    ProbingType probing_type;

    int h1(std::string k, int n);
    int h2(std::string k, int n);

    int linear_probing(std::string k, int n, int i);
    int quadratic_probing(std::string k, int n, int i);
    int double_hashing(std::string k, int n, int i);

public:
    TablaHashingCerrado(int s, ProbingType pt) : size(s), probing_type(pt) {
        tabla.resize(size);
    }

    int calcularIndiceSondeo(std::string clave, int i, ProbingType probing_type);

    void insertar(std::string clave, int valor);

    int get(std::string clave);

    void remover(std::string clave);

    void imprimir();
};