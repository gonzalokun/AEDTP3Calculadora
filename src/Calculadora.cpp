#include "Calculadora.h"


Calculadora::Calculadora() {
    cout << "Se inicializa la calculadora"<<endl;
}

Calculadora::~Calculadora() {

}


void Calculadora::nuevaCalculadora(Programa p, rutina r, int capVent){
    W = capVent;
    ejecutando = true;
    *programa = p;
    instanteActual = 0;
}
bool Calculadora::getEjecutando() const{
    return ejecutando;
}
void Calculadora::ejecutarUnPaso(){

}
void Calculadora::asignarVariable(variable x, valor v){

    if(variablePorNombre.count(x) > 0){ //si existe
        int instAct = get<0>((get<1>(variablePorNombre[x])).back());
        //int indiceVentana = (get<0>(variablePorNombre[x])).capacidad();
        //(get<1>(variablePorNombre[x])).push_back(make_tuple(instAct,v));
        //(get<0>(variablePorNombre[x]))[indiceVentana-1] = make_tuple(instAct, v);
    }
}
instante Calculadora::getInstanteActual() const{

}
rutina Calculadora::getRutinaActual() const{

}
int Calculadora::getIndiceInstruccionActual() const{

}
valor Calculadora::valorEnInstante(variable var, instante inst){

}
valor Calculadora::valorActualVariable(variable var){

}
const stack<valor>& Calculadora::getPila() const{

}
valor Calculadora::primeroPila() const{

}
valor Calculadora::segundoPila() const{

}
stack<valor> Calculadora::getPilaSinDos() const{

}
bool Calculadora::escribiendoVariable(variable &var) const{

}
bool Calculadora::haySalto() {

}
