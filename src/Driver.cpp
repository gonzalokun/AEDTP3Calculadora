#include "Driver.h"

Driver::Driver() : prog(new Programa), calc(new Calculadora()) {
	cout << "Se crea nuevo driver"<<endl;
}

Driver::~Driver() {
	// COMPLETAR
}

// Operaciones para agregar instrucciones

void Driver::begin(string rutina) {
	rutinaActual = rutina;
	instAct = new Instruccion(rutina);
}

void Driver::end(string rutina) {
	rutinaActual = rutina;
	delete instAct;
	instAct = nullptr;
}

void Driver::push(int n) {
	instAct->push(n);
	prog->agregarInstruccion(rutinaActual, *instAct);
}

void Driver::add() {
	instAct->add();
	prog->agregarInstruccion(rutinaActual, *instAct);
}

void Driver::sub() {
	instAct->sub();
	prog->agregarInstruccion(rutinaActual, *instAct);
}

void Driver::mul() {
	instAct->mul();
	prog->agregarInstruccion(rutinaActual, *instAct);
}

void Driver::read(string variable) {
	instAct->read(variable);
	prog->agregarInstruccion(rutinaActual, *instAct);
}

void Driver::write(string variable) {
	instAct->write(variable);
	prog->agregarInstruccion(rutinaActual, *instAct);
}

void Driver::jump(string rutina) {
	instAct->jump(rutina);
	prog->agregarInstruccion(rutinaActual, *instAct);
}

void Driver::jumpz(string rutina) {
	instAct->jumpz(rutina);
	prog->agregarInstruccion(rutinaActual, *instAct);

}

// Operaciones para ejecutar programas

void Driver::comenzarEjecucion(string rutina, int capacidadVentana) {
	calc->nuevaCalculadora(*prog,rutina, capacidadVentana);
}

void Driver::asignarVariable(string x, int valor) {
    calc->asignarVariable(x,valor);
}

bool Driver::ejecucionFinalizada() const {
	return not (calc->getEjecutando());
}

void Driver::ejecutarInstruccionActual() {
	// COMPLETAR
}

int Driver::topePila() const {
	return calc->primeroPila();
}

int Driver::valorVariable(string x) const {
	// COMPLETAR
}

int Driver::valorHistoricoVariable(string x, int t) const {
	// COMPLETAR
}

int Driver::instanteActual() const {
	return calc->getInstanteActual();
}
