#include "Driver.h"

Driver::Driver() : prog(Programa()), calc(Calculadora()) {
	cout << "Se crea nuevo driver"<<endl;
    comenzoEjecucion = false;
}

Driver::~Driver() {
	// COMPLETAR
}

// Operaciones para agregar instrucciones

void Driver::begin(string rutina) {
    if(!comenzoEjecucion && rutina != rutinaActual)
    {
        prog.nuevaRutina(rutina);
        rutinaActual = rutina;
        instAct = new Instruccion(rutina);
    }

}

void Driver::end(string rutina) {
    if(!comenzoEjecucion)
    {
        rutinaActual =rutina;
        delete instAct;
        instAct = nullptr;
    }
}

void Driver::push(int n) {
    if(!comenzoEjecucion)
    {
        instAct->push(n);
        prog.agregarInstruccion(rutinaActual, *instAct);
    }

}

void Driver::add() {
    if(!comenzoEjecucion)
    {
        instAct->add();
        prog.agregarInstruccion(rutinaActual, *instAct);
    }

}

void Driver::sub() {
    if(!comenzoEjecucion)
    {
        instAct->sub();
        prog.agregarInstruccion(rutinaActual, *instAct);
    }

}

void Driver::mul() {
    if(!comenzoEjecucion)
    {
        instAct->mul();
        prog.agregarInstruccion(rutinaActual, *instAct);
    }

}

void Driver::read(string variable) {
    if(!comenzoEjecucion)
    {
        instAct->read(variable);
        prog.agregarInstruccion(rutinaActual, *instAct);
    }

}

void Driver::write(string variable) {
    if(!comenzoEjecucion)
    {
        instAct->write(variable);
        prog.agregarInstruccion(rutinaActual, *instAct);
    }

}

void Driver::jump(string rutina) {
    if(!comenzoEjecucion)
    {
        instAct->jump(rutina);
        prog.agregarInstruccion(rutinaActual, *instAct);
    }

}

void Driver::jumpz(string rutina) {
    if(!comenzoEjecucion)
    {
        instAct->jumpz(rutina);
        prog.agregarInstruccion(rutinaActual, *instAct);
    }


}

// Operaciones para ejecutar programas

void Driver::comenzarEjecucion(string rutina, int capacidadVentana) {

    if(!comenzoEjecucion) {
        comenzoEjecucion = true;
        calc.nuevaCalculadora(prog,rutina, capacidadVentana);
    }

}

void Driver::asignarVariable(string x, int valor) {
    calc.asignarVariable(x,valor);
}

bool Driver::ejecucionFinalizada() const {
	return not (calc.getEjecutando());
}

void Driver::ejecutarInstruccionActual() {
	// COMPLETAR
}

int Driver::topePila() const {
	return calc.primeroPila();
}

const int Driver::valorVariable(string x){
	return calc.valorEnInstante(x,calc.getInstanteActual());
}

int Driver::valorHistoricoVariable(string x, int t) const {
	// COMPLETAR
}

int Driver::instanteActual() const {
	return calc.getInstanteActual();
}
