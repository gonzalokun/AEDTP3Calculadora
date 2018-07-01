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
    const list<rutina>& getRutinas() const;
    list<rutina>& getRutinas();
    Instruccion instruccion(const rutina r, const int iesima);
    Operacion instruccion2(const rutina r, const int iesima);
    int longitud(rutina r) ;

private:

    struct estructuraDeRutinasPorNombre{
        list<Instruccion> listaInstr;
    };

    trie<estructuraDeRutinasPorNombre> rutinasPorNombre; //clave rutinas
    list<rutina> rutinas;

};

#endif
