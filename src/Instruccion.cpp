#include "Instruccion.h"

Instruccion::Instruccion(rutina r) {
    ////cout << "Nueva instruccion perteneciente a rutina: " << r<<endl;
    nombreRut = r;
    nombreVar = "";
    consNum = 0;
    op = oNada;
    rutinaJump="";
}


Instruccion::Instruccion() {
    ////cout << "Nueva instruccion sin rutina"<<endl;
    nombreRut = "";
    nombreVar = "";
    consNum = 0;
    op=oNada;
    rutinaJump="";
}

Instruccion::~Instruccion(){

}

void Instruccion::push(valor n){
    op = oPush;
    consNum = n;
    nombreVar = "";
}
void Instruccion::add(){
    op = oAdd;
    nombreVar = "";
    consNum = 0;
}
void Instruccion::sub(){
    op = oSub;
    nombreVar = "";
    consNum = 0;
}
void Instruccion::mul(){
    op = oMul;
    nombreVar = "";
    consNum = 0;
}
void Instruccion::read(const variable& var){
    op = oRead;
    nombreVar = var;
    consNum = 0;
}
void Instruccion::write(const variable& var){
    op = oWrite;
    nombreVar = var;
    consNum = 0;
}
void Instruccion::jump(const rutina& r){
    op = oJump;
    rutinaJump=r;
    nombreVar = "";
    consNum = 0;
}
void Instruccion::jumpz(const rutina& r){
    op = oJumpz;
    rutinaJump=r;
    nombreVar = "";
    consNum = 0;
}

rutina Instruccion::getRutinaJump() {
    return rutinaJump;
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
