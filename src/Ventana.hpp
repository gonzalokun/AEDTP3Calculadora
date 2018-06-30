
template<class T>
Ventana<T>::Ventana(int capacidad) {
	_capacidad = capacidad;
	_tam = 0;
	_start = 0;
	_elems = new T*[capacidad];
	for (int i = 0; i < _capacidad; i++) {
		_elems[i] = nullptr;
	}
}

template<class T>
Ventana<T>::~Ventana() {
	for (int i = 0; i < _capacidad; i++) {
		if (_elems[i] != nullptr) {
			delete _elems[i];
		}
	}
	delete [] _elems;
}

template<class T>
void Ventana<T>::registrar(const T& elem) {
	if (_tam < _capacidad) {
		_elems[_tam] = new T(elem);
		_tam++;
	} else {
		*_elems[_start] = elem;
		_start = (_start + 1) % _capacidad;
	}
}

template<class T>
int Ventana<T>::capacidad() const {
	return _capacidad;
}

template<class T>
int Ventana<T>::tam() const {
	return _tam;
}

template<class T>
T& Ventana<T>::operator[](int i) const {
	return *_elems[(_start + i) % _capacidad];
}

