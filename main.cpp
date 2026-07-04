#include "hashing_cerrado.hpp"
#include <iostream>

using namespace std;

int main() {
    TablaHashingCerrado ht(7);

    ht.insertar(10, "A");
    ht.insertar(20, "B");
    ht.insertar(15, "C");
    ht.insertar(7, "D");

    ht.imprimir();

    cout << "\nBuscar 15: " << ht.get(15) << endl;

    ht.remover(15);
    cout << "Después de eliminar 15:\n";
    ht.imprimir();

    return 0;
}