
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

template<class T>
Ventana<T>::Ventana(const Ventana<T>& o) :
	_capacidad(0),
	_tam(0),
	_start(0),
	_elems(nullptr)
{
    *this = o;
}

template<class T>
Ventana<T>& Ventana<T>::operator=(const Ventana<T>& o) {
    for (int i = 0; i < _capacidad; i++) {
        if (_elems[i] != nullptr) {
            delete _elems[i];
        }
    }
	if (_elems != nullptr) {
    	delete [] _elems;
	}

    _capacidad = o._capacidad;
    _tam = o._tam;
    _start = o._start;

    _elems = new T*[_capacidad];
    for (int i = 0; i < _tam; i++) {
        _elems[i] = new T(*o._elems[i]);
    }
    for (int i = _tam; i < _capacidad; i++) {
        _elems[i] = nullptr;
    }
	return *this;
}

