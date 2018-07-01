#include "Programa.h"
#include <iostream>
Programa::Programa(){

    cout << "Se crea nuevo programa"<<endl;
}


Programa::~Programa(){

}

void Programa::agregarInstruccion(rutina r, Instruccion i){
    if(rutinasPorNombre.count(r) != 0) { //si no existe
        rutinasPorNombre[r].push_back(i);
        rutinas.push_back(r);
    }else { //si ya existe la rutina
        rutinasPorNombre[r] = list<Instruccion>();
        rutinasPorNombre[r].push_back(i);
    }
}

list<rutina>& Programa::getRutinas() const{
    return rutinas;
}

//PRE, 0 <= iesima < rutinas.size()
Instruccion Programa::instruccion(const rutina r, const int iesima){
    list<Instruccion>::iterator it = (rutinasPorNombre[r]).begin();
    int rest = iesima;
    while(rest >= 0) {
        it++;
        rest--;
    }
    return (*it);
}


Operacion Programa::instruccion2(const rutina r, const int iesima){
    cout << "entro a inst2"<<endl;
    list<Instruccion>::iterator it = (rutinasPorNombre[r]).begin();
    int rest = iesima;
    while(rest >= 0) {
        it++;
        rest--;
    }
    return (*it).getOp();
}
int Programa::longitud(rutina r) {
    //return (rutinasPorNombre[r]).size();
}
