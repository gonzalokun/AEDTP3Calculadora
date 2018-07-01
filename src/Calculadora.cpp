#include "Calculadora.h"

Calculadora::Calculadora() {
    cout << "Se inicializa la calculadora"<<endl;
}

Calculadora::~Calculadora() {

}

void Calculadora::nuevaCalculadora(Programa p, rutina r, int capVent){
    W = capVent;
    ejecutando = true;

    //pasada 1: recorremos rutinas de p y las guardamos
    list<rutina>::iterator it;


    //pasada 2: variables

    //pasada 3: lista de instrucciones a cada rutinas.

    *programa = p;
    instanteActual = 0;
}
bool Calculadora::getEjecutando() const{
    return ejecutando;
}
void Calculadora::ejecutarUnPaso(){
}

void Calculadora::asignarVariable(variable x, valor v){
    cout << "aca no entra-----------------------------------" <<endl;
    if(variablePorNombre.count(x) > 0){ //si existe
        int instAct = get<0>(((variablePorNombre[make_tuple(x,W)]).valorHistorico).back());
        //int indiceVentana = (get<0>(variablePorNombre[x])).capacidad();
        //(get<1>(variablePorNombre[x])).push_back(make_tuple(instAct,v));
        //(get<0>(variablePorNombre[x]))[indiceVentana-1] = make_tuple(instAct, v);
    }
}
instante Calculadora::getInstanteActual() const{
    return instanteActual;
}

rutina Calculadora::getRutinaActual() const{
    return get<0>(rutinaActual);
}

int Calculadora::getIndiceInstruccionActual() const{
    return indiceInstruccionActual;
}

valor Calculadora::valorEnInstante(variable var, instante inst){
    if(instanteActual - inst <= W) {
        if(variablePorNombre.count(var) > 0){
            //return get<1>((get<0>(variablePorNombre.at(var)))[inst]);
        }
    }
    else {
        //
    }
}

valor Calculadora::valorActualVariable(variable var){

}

const stack<valor>& Calculadora::getPila() const{
    return pila;
}

valor Calculadora::primeroPila() const{
    return (pila.empty()) ? 0 : (pila.top());
}

valor Calculadora::segundoPila() {

    if(pila.size() >= 2){
        valor v = pila.top();
        pila.pop();
        valor segundoPila = pila.top();
        pila.emplace(v);

        return segundoPila;
    }
    else{
        return 0;
    }
}

stack<valor>& Calculadora::getPilaSinDos() {
    pila.pop();
    pila.pop();
    return pila;
}

bool Calculadora::escribiendoVariable(variable &var) const{
    Operacion opActual = get<0>((*(get<1>(rutinaActual)))[indiceInstruccionActual]);

    if(opActual == oWrite){
        //
        return true;
    }
    else{
        return false;
    }
}

bool Calculadora::haySalto() {

    //superInstruccion instActual = (*(get<1>(rutinaActual)))[indiceInstruccionActual];

    Operacion opActual = get<0>((*(get<1>(rutinaActual)))[indiceInstruccionActual]);

    return (opActual == oJump || opActual == oJumpz);
}
