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

//typedef tuple<Ventana<tuple<instante, valor> >, valorHistorico>* itVarNombre;

//struct estructuraDeVariablePorNombre;

//typedef trie<estructuraDeVariablePorNombre>::ItDiccTrie itVarNombre;

//typedef vector<Instruccion>* itRut;

//typedef trie<vector<Instruccion>>::ItDiccTrie itRut;

//typedef tuple<Operacion, int, itVarNombre, itRut> superInstruccion;

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
    valor segundoPila();
    stack<valor>& getPilaSinDos();

    bool escribiendoVariable(variable &var) const;
    bool haySalto();

private:
    struct estructuraDeVariablePorNombre{

        Ventana<tuple<instante,valor> > vent;
        list<tuple<instante,valor> > valorHistorico;
        estructuraDeVariablePorNombre(int w) : vent(Ventana<tuple<instante,valor> >(w)), valorHistorico(list<tuple<instante, valor> >()){        };
    };
    int indiceInstante(int i,int s,instante busc,variable var);
    trie<estructuraDeVariablePorNombre> variablePorNombre;

    struct superInstruccion{
        ~superInstruccion();
        Instruccion i;
        Operacion op;
        int constanteNumerica;
        trie<estructuraDeVariablePorNombre>::ItDiccTrie itVarNombre;
        trie<vector<superInstruccion>>::ItDiccTrie* itRut;
    };

    trie<vector<superInstruccion>> rutinasProg;

    trie<vector<superInstruccion>>::ItDiccTrie rutinaActual;

    stack<int> pila;
    Programa* programa;
    int W;
    int instanteActual;
    bool ejecutando;
    int indiceInstruccionActual;
};

#endif
