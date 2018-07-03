#ifndef DRIVER_CALCULADORA_H
#define DRIVER_CALCULADORA_H
#include <iostream>
#include "Calculadora.h"

using namespace std;

class Driver {
public:

	Driver();
	~Driver();

	// Operaciones para agregar instrucciones
	void begin(string rutina);
	void end(string rutina);
	void push(int n);
	void add();
	void sub();
	void mul();
	void read(string variable);
	void write(string variable);
	void jump(string rutina);
	void jumpz(string rutina);

	// Operaciones para ejecutar programas
	void comenzarEjecucion(string rutina, int capacidadVentana);
	void asignarVariable(string idVariable, int valor);
	bool ejecucionFinalizada() const;
	void ejecutarInstruccionActual();
	int topePila() const; // Si la pila está vacía, devuelve 0.
	const int valorVariable(string idVariable);
	int valorHistoricoVariable(string idVariable, int t) const;
	int instanteActual() const;

private:
	// COMPLETAR
	bool comenzoEjecucion;
	rutina rutinaActual;
	Instruccion* instAct;
	//Calculadora* calc;
	Calculadora calc;
	Programa* prog;

};

#endif
