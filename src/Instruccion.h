#ifndef SOLUCION_INSTRUCCION_H
#define SOLUCION_INSTRUCCION_H


#include "Utiles.h"

class Instruccion {
public:
    // Precondición: la operación es PUSH
    Instruccion(Operacion operacion, int valor);

    // Precondición: la operación es ADD, SUB o MUL
    Instruccion(Operacion operacion);

    // Precondición: la operación es READ, WRITE, JUMP o JUMPZ
    Instruccion(Operacion operacion, Id nombre);

    Operacion operacion() const;

    // Precondición: la operación es PUSH
    int valor() const;

    // Precondición: la operación es READ, WRITE, JUMP o JUMPZ
    Id nombre() const;

private:
    Operacion _operacion;
    int _valor;
    Id _nombre;

};

#endif /*__INSTRUCCION_H__*/