#define CANTCHAR 256
#include <stack>
#include "triee.h"


template <typename T>
triee<T>::triee(){
    //Creo el diccionario vacio
    _size = 0;
    raiz = new Nodo;
    raiz->siguientes = new Nodo*[CANTCHAR];

    //Pongo nulo en todos los hijos de la raiz
    for(int i = 0; i < CANTCHAR; i++){
        raiz->siguientes[i] = nullptr;
    }

    raiz->definicion = nullptr;
}

template <typename T>
triee<T>::triee(const triee<T>& aCopiar) : triee() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
triee<T>& triee<T>::operator=(const triee<T>& d) {
    //Borro lo viejo
    delete raiz;

    //Cambio el tamaño
    _size = d.size();

    raiz = copiarNodos(d.raiz);
}

template <typename T>
typename triee<T>::Nodo * triee<T>::copiarNodos(Nodo *nodoACopiar) {
    if (nodoACopiar == nullptr){
        return nodoACopiar;
    }

    Nodo* nuevoNodo = new Nodo;

    if(nodoACopiar->definicion == nullptr){
        nuevoNodo->definicion = nullptr;
    }
    else{
        nuevoNodo->definicion = new T;
        *(nuevoNodo->definicion) = *(nodoACopiar->definicion);
    }

    nuevoNodo->siguientes = new Nodo*[CANTCHAR];

    for(int i = 0; i < CANTCHAR; i++){
        nuevoNodo->siguientes[i] = copiarNodos(nodoACopiar->siguientes[i]);
    }

    return nuevoNodo;
}

template <typename T>
triee<T>::~triee(){
    delete raiz;

    //std::cout << "BORRE LA RAIZ" << std::endl;

    raiz = nullptr;
    _size = 0;
}

//

template <typename T>
triee<T>::Nodo::~Nodo() {

    delete definicion;

    //std::cout << "BORRE LA DEF" << std::endl;

    for(int i = 0; i < CANTCHAR; i++){
        delete (siguientes[i]);
    }

    delete[] siguientes;

    //std::cout << "BORRE LOS SIGUIENTES" << std::endl;

}

//

template <typename T>
T& triee<T>::operator[](const string& clave){

    Nodo* nodoActual = raiz;

    //Recorro por todos los caracteres del string
    for(int i = 0; i < clave.length(); i++){
        int pos = clave.at(i);

        if(nodoActual->siguientes[pos] == nullptr){
            //No existe el nodo, lo creo

            nodoActual->siguientes[pos] = new Nodo;

            nodoActual->siguientes[pos]->definicion = nullptr;
            nodoActual->siguientes[pos]->siguientes = new Nodo*[CANTCHAR];

            for(int j = 0; j < CANTCHAR; j++){
                nodoActual->siguientes[pos]->siguientes[j] = nullptr;
            }
        }

        nodoActual = nodoActual->siguientes[pos];
    }

    if(nodoActual->definicion == nullptr){
        nodoActual->definicion = new T;
        _size++;
    }

    //nodoActual esta posicionado en el lugar correcto
    return *(nodoActual->definicion);
}


template <typename T>
int triee<T>::count(const string& clave) const{
    Nodo* nodoActual = raiz;

    for(int i = 0; i < clave.length(); i++){
        int pos = clave.at(i);

        nodoActual = nodoActual->siguientes[pos];

        if(nodoActual == nullptr){
            return 0;
        }
    }

    //Llegue al nodo final, si la definicion no es nula devuelvo 1
    //Sino 0

    if(nodoActual->definicion == nullptr){
        return 0;
    }

    return 1;
}

template <typename T>
const T& triee<T>::at(const string& clave) const {
    Nodo* nodoActual = raiz;

    //Recorro por todos los caracteres del string
    for(int i = 0; i < clave.length(); i++){
        int pos = clave.at(i);

        nodoActual = nodoActual->siguientes[pos];
    }

    //nodoActual esta posicionado en el lugar correcto
    return nodoActual->definicion;
}

template <typename T>
T& triee<T>::at(const string& clave) {
    Nodo* nodoActual = raiz;

    //Recorro por todos los caracteres del string
    for(int i = 0; i < clave.length(); i++){
        int pos = clave.at(i);

        nodoActual = nodoActual->siguientes[pos];
    }

    //nodoActual esta posicionado en el lugar correcto
    return nodoActual->definicion;
}

template <typename T>
void triee<T>::erase(const string& clave) {
    //Hay que borrar el nodo con la clave

    std::stack<std::pair<Nodo*, int>> padres;

    //Llego al nodo con la clave
    Nodo* nodoActual = raiz;

    //Recorro por todos los caracteres del string
    for(int i = 0; i < clave.length(); i++){
        int pos = clave.at(i);

        //Cargo la lista de padres
        padres.emplace(nodoActual, pos);

        nodoActual = nodoActual->siguientes[pos];
    }

    //Nodo Actual esta donde debe, hay que borrar el nodo si no tiene hijos
    //Antes borro la definicion guardada
    delete nodoActual->definicion;
    nodoActual->definicion = nullptr;

    _size--;

    //Ahora hay que borrar el nodo si todos los hijos son nulos

    while(!padres.empty()){
        nodoActual = padres.top().first;
        int vinoDe = padres.top().second;

        if(sonHijosNulos(nodoActual->siguientes[vinoDe])){
            delete nodoActual->siguientes[vinoDe];
            nodoActual->siguientes[vinoDe] = nullptr;
        }

        //Saco el padre actual asi avanza el ciclo
        padres.pop();
    }
}

template <typename T>
bool triee<T>::sonHijosNulos(Nodo *nodoARevisar) {
    bool sonNulos = true;

    for(int i = 0; i < CANTCHAR; i++){
        if(nodoARevisar->siguientes[i] != nullptr){
            sonNulos = false;
            break;
        }
    }

    return sonNulos;
}

template <typename T>
int triee<T>::size() const{
    return _size;
}

template <typename T>
bool triee<T>::empty() const{
    return _size == 0;
}