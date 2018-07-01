#ifndef INSTRUCCION_H
#define INSTRUCCION_H

#include <string>
#include <iostream>
using namespace std;

typedef string rutina;
typedef int valor;
typedef string variable;
enum Operacion {oAdd, oSub, oMul, oPush, oRead, oWrite, oJump, oJumpz};

class Instruccion
{
public:
    Instruccion(rutina r);
    ~Instruccion();
    void push(valor &n); //crea inst push
    void add(); //crea inst add
    void sub();
    void mul();
    void read(const variable& var);
    void write(const variable& var);
    void jump(const rutina& r);
    void jumpz(const rutina& r);
    Operacion getOp();
    valor constanteNumerica() const;
    variable nombreVariable() const;
    rutina nombreRutina() const;


private:
    Operacion op;
    int consNum;
    variable nombreVar;
    rutina nombreRut;
};

#endif
