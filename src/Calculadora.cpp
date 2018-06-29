
#include "Calculadora.h"

Calculadora::Calculadora(int W) {
    //
}

bool Calculadora::ejecucionFinalizada() const {
    return (not _ejecutando);
}

int Calculadora::instanteActual() const {
    return _instanteActual;
}