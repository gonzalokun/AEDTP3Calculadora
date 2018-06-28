#include "Driver.h"

Driver::Driver() {
	// COMPLETAR
}

Driver::~Driver() {
	// COMPLETAR
}

// Operaciones para agregar instrucciones

void Driver::begin(string rutina) {
	// COMPLETAR
}

void Driver::end(string rutina) {
	// COMPLETAR
}

void Driver::push(int n) {
	// COMPLETAR
}

void Driver::add() {
	// COMPLETAR
}

void Driver::sub() {
	// COMPLETAR
}

void Driver::mul() {
	// COMPLETAR
}

void Driver::read(string variable) {
	// COMPLETAR
}

void Driver::write(string variable) {
	// COMPLETAR
}

void Driver::jump(string rutina) {
	// COMPLETAR
}

void Driver::jumpz(string rutina) {
	// COMPLETAR
}

// Operaciones para ejecutar programas

void Driver::comenzarEjecucion(string rutina, int capacidadVentana) {
	// COMPLETAR
}

void Driver::asignarVariable(string x, int valor) {
	// COMPLETAR
}

bool Driver::ejecucionFinalizada() const {
	// COMPLETAR
}

void Driver::ejecutarInstruccionActual() {
	// COMPLETAR
}

int Driver::topePila() const {
	// COMPLETAR
}

int Driver::valorVariable(string x) const {
	// COMPLETAR
}

int Driver::valorHistoricoVariable(string x, int t) const {
	// COMPLETAR
}

int Driver::instanteActual() const {
	// COMPLETAR
}

