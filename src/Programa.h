#ifndef H_PROGRAMA
#define H_PROGRAMA
using namespace std;

#include "Instruccion.h"
#include <vector>
#include "trie.h"
#include <list>
#include <set> //conj lineal

class Programa {
public:
    Programa();
    ~Programa();
    void agregarInstruccion(rutina r, Instruccion i);
    list<rutina>& getRutinas() const;
    Instruccion instruccion(const rutina r, const int iesima);
    Operacion instruccion2(const rutina r, const int iesima);
    int longitud(rutina r) ;

private:

    trie<list<Instruccion>> rutinasPorNombre; //clave rutinas
    list<rutina> rutinas;

};

#endif
