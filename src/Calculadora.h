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
    const instante getInstanteActual() const;
    const rutina getRutinaActual() const;
    const int getIndiceInstruccionActual() const;
    const valor valorEnInstante(variable const var, instante const inst);
    const valor valorActualVariable(variable const var);
    const stack<valor>& getPila() const;
    const valor primeroPila() const;
    const valor segundoPila();
    stack<valor>& getPilaSinDos();

    const bool escribiendoVariable(variable const &var) const;
    const bool haySalto() const;

private:
    struct estructuraDeVariablePorNombre{

        Ventana<tuple<instante,valor> > vent;
        list<tuple<instante,valor> > valorHistorico;
        estructuraDeVariablePorNombre(int w) : vent(Ventana<tuple<instante,valor> >(w)), valorHistorico(list<tuple<instante, valor> >()){        };
    };
    const int indiceInstante(int i,int s,instante busc,variable var)const;
    trie<estructuraDeVariablePorNombre> variablePorNombre;

    struct superInstruccion{
        ~superInstruccion();
        Operacion op;
        int constanteNumerica;
        trie<estructuraDeVariablePorNombre>::ItDiccTrie itVarNombre;
        trie<vector<superInstruccion>>::ItDiccTrie* itRut;
    };
    vector<rutina> vecRutinas; //lo usamos en el destructor.
    trie<vector<superInstruccion>> rutinasProg;

    trie<vector<superInstruccion>>::ItDiccTrie rutinaActual;

    stack<int> pila;
    int W;
    int instanteActual;
    bool ejecutando;
    int indiceInstruccionActual;
};

#endif
