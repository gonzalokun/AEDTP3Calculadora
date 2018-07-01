#ifndef VENTANA_H
#define VENTANA_H

template<class T>
class Ventana {
public:
	Ventana(int capacidad);
	Ventana(const Ventana& o);
	~Ventana();
	void registrar(const T& elem);
	int capacidad() const;
	int tam() const;
	T& operator[](int i) const; // pre: 0 <= i < tam()
	Ventana& operator=(const Ventana&);
private:
	int _capacidad;
	int _tam;
	int _start;
	T** _elems;
};

#include "Ventana.hpp"

#endif
