#include "Programa.h"
#include <iostream>
Programa::Programa(){

    cout << "Se crea nuevo programa"<<endl;
}


Programa::~Programa(){
}

void Programa::nuevaRutina(const rutina r) {
    rutinas.push_back(r);
    list<Instruccion> aux = list<Instruccion>();
    aux.push_back(Instruccion());
    cout << "A"<<endl;
    rutinasPorNombre[r] = aux;
    cout << "s"<<endl;
}

void Programa::agregarInstruccion(rutina r, Instruccion i){
    i.setRutina(r);
    cout << "d"<<endl;
    if(rutinasPorNombre[r].back().nombreRutina() == "") {
        rutinasPorNombre[r].back() = i;
    }else {
        rutinasPorNombre[r].push_back(i);
    }
    cout << "w"<<endl;
}

const list<rutina>& Programa::getRutinas() const{
    return rutinas;
}
list<rutina>& Programa::getRutinas(){
    return rutinas;
}
//PRE, 0 <= iesima < rutinas.size()
Instruccion Programa::instruccion(const rutina r, const int iesima){
    list<Instruccion>::const_iterator it = (rutinasPorNombre[r]).begin();
    int rest = iesima;
    while(rest >= 0 && it != (rutinasPorNombre[r]).end()) {
        it++;
        rest--;
    }
    return (*it);
}


Operacion Programa::instruccion2(const rutina r, const int iesima){
    cout << "entro a inst2"<<endl;
    list<Instruccion>::iterator it = (rutinasPorNombre[r]).begin();
    int rest = iesima;
    while(rest >= 0 && it != (rutinasPorNombre[r]).end()) {
        it++;
        rest--;
    }
    return (*it).getOp();
}
int Programa::longitud(rutina r) {
    return (rutinasPorNombre[r]).size();
}
