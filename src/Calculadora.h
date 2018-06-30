#ifndef H_CALCULADORA
#define H_CALCULADORA

using namespace std;
#include "Instruccion.h"
#include "Programa.h"
#include "Ventana.h"
#include <queue>
#include <map>
#include <stack>
#include <tuple>

typedef int instante;
typedef list<tuple<instante,valor> > valorHistorico;
typedef tuple<Ventana<tuple<instante, valor> >, valorHistorico>* itVarNombre;
typedef vector<Instruccion>* itRut;
typedef tuple<Operacion, int, itVarNombre, itRut> superInstruccion;


class Calculadora {

public:
        Calculadora();
        ~Calculadora();
        void nuevaCalculadora(Programa p, rutina r, int capVent);
        bool getEjecutando() const;
        void ejecutarUnPaso();
        void asignarVariable(variable x, valor v);
        instante getInstanteActual() const;
        rutina getRutinaActual() const;
        int getIndiceInstruccionActual() const;
        valor valorEnInstante(variable var, instante inst);
        valor valorActualVariable(variable var);
        const stack<valor>& getPila() const;
        valor primeroPila() const;
        valor segundoPila() const;
        stack<valor> getPilaSinDos() const;
        bool escribiendoVariable(variable &var) const;
        bool haySalto();

private:

    trie<tuple<Ventana<tuple<instante,valor> >, valorHistorico> > variablePorNombre;
    int instanteActual;
    bool ejecutando;
    vector<superInstruccion>*  rutinaActual;
    int indiceInstruccionActual;
    stack<int> pila;
    Programa * programa;
    int W;
};


#endif
