#ifndef SOLUCION_PROGRAMA_H
#define SOLUCION_PROGRAMA_H

#include <list>
#include <vector>

#include "DiccionarioTrie.h"
#include "Instruccion.h"

using namespace std;

class Programa{
public:

    Programa();

    void agregarInstruccion(Id rutina, Instruccion i);

    list<Id>&  rutinas() const;

    //Pre: rutina pertenece a rutinas(p) e i<= longitud(rutina)
    Instruccion& DameInstruccion(Id rutina, int i) const;

    //Pre: rutina pertenece a rutinas(p)
    int longitudDeRutina(Id rutina) const;

    ~Programa();

private:
    DiccTrie<list<Instruccion>> _rutinasPorNombre;
    vector<Id> _rutinas;

};

#endif //SOLUCION_PROGRAMA_H