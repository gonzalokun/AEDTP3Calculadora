#ifndef SOLUCION_CALCULADORA_H
#define SOLUCION_CALCULADORA_H

#include <stack>
#include "Ventana.h"
#include "Programa.h"

using namespace std;

class Calculadora{
public:

    Calculadora(int W);

    // Operaciones para ejecutar programas según Driver.h
    void comenzarEjecucion(Id rutina, int capacidadVentana);//Quiza no hace falta

    void asignarVariable(Id idVariable, int valor);

    bool ejecucionFinalizada() const;

    void ejecutarInstruccionActual();

    int topePila() const; // Si la pila está vacía, devuelve 0.

    int valorVariable(Id idVariable) const;

    int valorHistoricoVariable(Id idVariable, int t) const;

    int instanteActual() const;

    // Otras Operaciones según diseño pedido TP2

    Id rutinaActual() const; //Según TP2 debe ser en O(1) por lo que debería ser por & creo

    //list<int>& pila() const;

    stack<int>& pila() const;

    int indiceInstActual() const;


private:

    struct superInstruccion; //es la instruccion pero con punteros en lugar de IdVariable/Rutina

    int _W;
    DiccTrie< Ventana <pair<int,int>> > _variablePorNombre;
    DiccTrie< vector<superInstruccion> > _rutinasProg;
    int _instanteActual;
    bool _ejecutando;
    int _indiceInstActual;
    stack<int> _pila;

    struct superInstrucciob{
        Operacion _op;
        int _valor;
        DiccTrie< Ventana <pair<int,int>> >::ItDiccTrie _itVarNombre;
        DiccTrie< vector<superInstruccion> >::ItDiccTrie _itRut;

    };

};

#endif //SOLUCION_CALCULADORA_H
