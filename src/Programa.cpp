#include "Programa.h"
#include <iostream>
Programa::Programa(){

    cout << "Se crea nuevo programa"<<endl;
}


Programa::~Programa(){

}

void Programa::agregarInstruccion(rutina r, Instruccion i){
    i.setRutina(r);
    if(rutinasPorNombre.count(r) != 0) {  //si existe
        rutinasPorNombre[r].listaInstr.push_back(i);
        rutinas.push_back(r);
    }else { //si no existe
        rutinasPorNombre[r].listaInstr = list<Instruccion>();
        rutinasPorNombre[r].listaInstr.push_back(i);
    }
}

const list<rutina>& Programa::getRutinas() const{
    return rutinas;
}
list<rutina>& Programa::getRutinas(){
    return rutinas;
}
//PRE, 0 <= iesima < rutinas.size()
Instruccion Programa::instruccion(const rutina r, const int iesima){
    list<Instruccion>::iterator it = (rutinasPorNombre[r]).listaInstr.begin();
    int rest = iesima;
    while(rest >= 0) {
        it++;
        rest--;
    }
    return (*it);
}


Operacion Programa::instruccion2(const rutina r, const int iesima){
    cout << "entro a inst2"<<endl;
    list<Instruccion>::iterator it = (rutinasPorNombre[r]).listaInstr.begin();
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
