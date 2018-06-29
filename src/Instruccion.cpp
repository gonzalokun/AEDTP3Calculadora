
#include "Instruccion.h"

Instruccion::Instruccion(Operacion operacion, int valor){
    _operacion = operacion;
    _valor = valor;
}
Instruccion::Instruccion(Operacion operacion){
    _operacion = operacion;
}
Instruccion::Instruccion(Operacion operacion, Id nombre){
    _operacion = operacion;
    _nombre = nombre;
}
int Instruccion::valor() const{
    return _valor;
}
Operacion Instruccion::operacion() const{
    return _operacion;
}
Id Instruccion::nombre() const{
    return _nombre;
}