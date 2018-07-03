#include "Instruccion.h"

Instruccion::Instruccion(rutina r) {
    cout << "Nueva instruccion perteneciente a rutina: " << r<<endl;
    nombreRut = r;
    nombreVar = "";
    consNum = 0;
    op = oNada;
}


Instruccion::Instruccion() {
    cout << "Nueva instruccion sin rutina"<<endl;
    nombreRut = "";
    nombreVar = "";
    consNum = 0;
    op=oNada;
}

Instruccion::~Instruccion(){

}

void Instruccion::push(valor n){
    op = oPush;
    consNum = n;
}
void Instruccion::add(){
    op = oAdd;

}
void Instruccion::sub(){
    op = oSub;
}
void Instruccion::mul(){
    op = oMul;
}
void Instruccion::read(const variable& var){
    op = oRead;
    nombreVar = var;
}
void Instruccion::write(const variable& var){
    op = oWrite;
    nombreVar = var;
}
void Instruccion::jump(const rutina& r){
    op = oJump;
    nombreRut = r;
}
void Instruccion::jumpz(const rutina& r){
    op = oJumpz;
    nombreRut = r;
}


void Instruccion::setRutina(rutina r){
    nombreRut = r;
}
Operacion Instruccion::getOp(){
    return op;
}
valor Instruccion::constanteNumerica() const{
    return consNum;
}
variable Instruccion::nombreVariable() const{
    return nombreVar;
}
rutina Instruccion::nombreRutina() const{
    return nombreRut;
}