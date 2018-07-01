#include "Calculadora.h"


Calculadora::Calculadora() {
    cout << "Se inicializa la calculadora"<<endl;
    get<0>(rutinaActual) = "";
    get<1>(rutinaActual) = nullptr;
}

Calculadora::~Calculadora() {

}


void Calculadora::nuevaCalculadora(Programa p, rutina r, int capVent){
    W = capVent;
    ejecutando = true;
    instanteActual = 0;
    indiceInstruccionActual = 0;

    //pasada 1: recorremos rutinas de p y las guardamos
    list<rutina>::const_iterator it = (p.getRutinas()).begin();
    while (it != (p.getRutinas()).end()) {
        rutinasProg[r] = new vector<superInstruccion>();

        if(*it == r) { //si es la rutina con la que hay que empezar
            //entonces definimos un puntero hacia la rutina
            get<0>(rutinaActual) = (*it);
            get<1>(rutinaActual) = rutinasProg[r];
        }
    }
    //terminadas de pasar las rutinas


    //pasada 2: variables
    //recorro instrucciones de rutina para ver las variables
    it = (p.getRutinas()).begin();
    while (it != (p.getRutinas()).end()) {
        for (int i = 0; i < p.longitud(*it); ++i) { //recorro instrucciones de la rutina actual
            if(p.instruccion(*it,i).getOp() == oWrite || p.instruccion(*it,i).getOp() == oRead) {
                variablePorNombre[make_tuple(p.instruccion(*it,i).nombreVariable(), capVent)] = estructuraDeVariablePorNombre(capVent);
            }
        }
    }


    //pasada 3: lista de instrucciones a cada rutinas.

    it = (p.getRutinas()).begin();
    while(it!= (p.getRutinas()).end()) {
        itRut punteroRut;
        int i = 0;
        Operacion op = p.instruccion(*it,i).getOp();
        int constNum = p.instruccion(*it,i).constanteNumerica();
        rutinasProg[*it]->resize(p.longitud(*it));
        itVarNombre punteroVar = (new tuple<Ventana<tuple<instante, valor> >, valorHistorico>((variablePorNombre[make_tuple(*it,capVent)]).vent,(variablePorNombre[make_tuple(*it,capVent)]).valorHistorico));
        for (i = 0; i < p.longitud(*it); ++i) {
            punteroRut->push_back(p.instruccion(*it,i));
            //armo mi vector de instruccions, pasando de la lista de instruccion de programa
        }
        rutinasProg[*it]->push_back(make_tuple(op,constNum,punteroVar,punteroRut));
    }


}
bool Calculadora::getEjecutando() const{
    return ejecutando;
}
void Calculadora::ejecutarUnPaso(){

}
void Calculadora::asignarVariable(variable x, valor v){
    //si el ultimo instante de la variable x es el instante actual, modificamos el valor
    //si el ultimo instante es menor al isntante actual, creamos un nuevo nodo en la lista
    if(variablePorNombre.count(x) > 0){ //si existe
        int actual = get<0>(variablePorNombre[make_tuple(x,W)].valorHistorico.back());
        if(actual < instanteActual) {
            //trie
            variablePorNombre[make_tuple(x,W)].valorHistorico.push_back(make_tuple(instanteActual,v));
            //lista
            variablePorNombre[make_tuple(x,W)].vent.registrar(make_tuple(instanteActual,v));

        }else {
            get<1>(variablePorNombre[make_tuple(x,W)].valorHistorico.back()) = v;
            int tam = (variablePorNombre[make_tuple(x,W)].vent).tam();
            get<1>((variablePorNombre[make_tuple(x,W)].vent)[tam-1]) = v;
        }


    }
}
instante Calculadora::getInstanteActual() const{
    return instanteActual;
}
rutina Calculadora::getRutinaActual() const{

}
int Calculadora::getIndiceInstruccionActual() const{
    return indiceInstruccionActual;
}
valor Calculadora::valorEnInstante(variable var, instante inst){
    if(instanteActual - inst <= W) {
        if(variablePorNombre.count(var) > 0){
            return get<1>((variablePorNombre[make_tuple(var,W)].vent)[inst]);
        }
    }else {
        valorHistorico::const_iterator it = (variablePorNombre[make_tuple(var,W)].valorHistorico).end();
        int i = instanteActual;
        while(i >=inst && it != (variablePorNombre[make_tuple(var,W)].valorHistorico).begin()) {
            i--;
            --it;
        }
        return get<0>(*it);
    }
}
valor Calculadora::valorActualVariable(variable var){
    return get<0>(variablePorNombre[make_tuple(var,W)].vent[W-1]);
}
const stack<valor>& Calculadora::getPila() const{
    return pila;

}
valor Calculadora::primeroPila() const{

}
valor Calculadora::segundoPila(){

}
stack<valor> Calculadora::getPilaSinDos() const{

}
bool Calculadora::escribiendoVariable(variable &var) const{

}
bool Calculadora::haySalto() {

}
