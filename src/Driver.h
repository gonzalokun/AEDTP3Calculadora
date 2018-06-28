#ifndef DRIVER_CALCULADORA_H
#define DRIVER_CALCULADORA_H

#include <string>

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
	int valorVariable(string idVariable) const;
	int valorHistoricoVariable(string idVariable, int t) const;
	int instanteActual() const;

private:
	// COMPLETAR
};

#endif
