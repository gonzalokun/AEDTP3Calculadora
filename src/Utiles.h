
#ifndef SOLUCION_UTILES_H
#define SOLUCION_UTILES_H

#include "string"
#include "Instruccion.h"
#include "Programa.h"
#include "Ventana.h"
#include <queue>
#include <map>
#include <stack>
#include <tuple>

using namespace std;

typedef int Operacion;
typedef string rutina;
typedef int valor;
typedef string variable;
enum Operacion {oAdd, oSub, oMul, oPush, oRead, oWrite, oJump, oJumpz, oNada};
typedef int instante;
typedef list<tuple<instante,valor> > valorHistorico;


#endif //SOLUCION_UTILES_H
