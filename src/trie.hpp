#include <stdio.h>
#include <iostream>
#include <tuple>
#include "trie.h"

template <typename T>

trie<T>::trie():_size(0){
    cout << "NUEVO TRIE"<<endl;
    raiz = iniciarNodo();
    raiz->clave = "";
}

template <typename T>
trie<T>::trie(const trie<T>& aCopiar) : trie() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
trie<T>& trie<T>::operator=(const trie<T>& d) {
    Nodo* nodoRecOrig = d.raiz;
    //cout << (raiz->siguientes==nullptr)<<endl<<(nodoRecOrig->siguientes==nullptr)<<endl;
    copiarNivel(raiz, nodoRecOrig,d.cv);
    _size = d._size;
    return *this;
}

template<typename T>
void trie<T>::copiarNivel(Nodo *&a,Nodo *b){
    //cout << "COPIANDO NIVELES:"<<endl;
        for (int i = 0; i < 256; i++)
        {
            if(b->siguientes[i] != nullptr) {

                if(a == nullptr) {
                    //cout <<"--------------ENTRO------------------------ i : "<<char(97+i)<<endl;
                    a = iniciarNodo();
                }
                if((b->siguientes[i])->definicion != nullptr) {
                    //cout << "copio definicion: "<< *(b->siguientes[i]->definicion)<<"------------";
                    a->siguientes[i] = iniciarNodo();
                    //cout << ((a->siguientes[i] == nullptr)? "es nul" : "no es nul")<<endl;
                    a->siguientes[i]->definicion = new T();
                    *(a->siguientes[i]->definicion) = *(b->siguientes[i]->definicion);
                }
                copiarNivel(a->siguientes[i], b->siguientes[i]);

            }
        }
}

template<typename T>
void trie<T>::copiarNivel(Nodo *&a,Nodo *b,int param){
    //cout << "COPIANDO NIVELES:"<<endl;
    for (int i = 0; i < 256; i++)
    {
        if(b->siguientes[i] != nullptr) {

            if(a == nullptr) {
                //cout <<"--------------ENTRO------------------------ i : "<<char(97+i)<<endl;
                a = iniciarNodo();
            }
            if((b->siguientes[i])->definicion != nullptr) {
                //cout << "copio definicion: "<< *(b->siguientes[i]->definicion)<<"------------";
                a->siguientes[i] = iniciarNodo();
                //cout << ((a->siguientes[i] == nullptr)? "es nul" : "no es nul")<<endl;
                a->siguientes[i]->definicion = new T(param);
                *(a->siguientes[i]->definicion) = *(b->siguientes[i]->definicion);
            }
            copiarNivel(a->siguientes[i], b->siguientes[i],param);

        }
    }
}

template <typename T>
trie<T>::~trie(){
    //cout << "DESTRUCTOR"<<endl;
    if(_size!=0) {
        borrarNodos(raiz);
    }
    delete[] raiz->siguientes;
    delete raiz;
}

template<typename T>
void trie<T>::borrarNodos(Nodo *nodo) {
    //cout << "entro a borrar Nodos"<<endl;
    for (int i = 0; i < 256; i++)
    {
        if(nodo->siguientes[i] != nullptr){
            //cout << "entro al nodo " << char(97+i)<< " y tiene hijos, elimino hijos y dspa  el"<<endl;
            //delete raiz->siguientes[i]->definicion;
            if(nodo->siguientes[i]->definicion != nullptr) {
                //cout << "borramos definicion en "<<char(97+i)<<"="<<*(nodo->siguientes[i]->definicion)<<endl;
                //cout << "borramos def------------------------------------------------------------------------"<<endl;
                delete nodo->siguientes[i]->definicion;
                nodo->siguientes[i]->definicion = nullptr;
            }

            borrarNodos(nodo->siguientes[i]);
            //cout << "----finalmente elimino ----" << char(97+i)<<endl;
            delete[] nodo->siguientes[i]->siguientes;
            delete nodo->siguientes[i];
            nodo->siguientes[i] = nullptr;
        }else {
            //cout << "    entro al nodo "<< char(97+i)<< " y no tiene hijos, asi q loelimino"<<endl;
            delete nodo->siguientes[i];
            nodo->siguientes[i] = nullptr;
        }
    }
}


template <typename T>
T& trie<T>::operator[](const string& clave){
    //veo si existe y devuelvo significado, si no la creo
    //cout << "inicio: "<< clave<<endl;
    if(count(clave) == 0) {//no existe
        //Puede pasar que este vacio el trie o no
        Nodo* nodoAct = raiz;
        Nodo* nodoPadre = raiz;
        //cout << "nodo raiz:"<<raiz->clave<<endl;
        //cout << "nodoact antes: "<< nodoAct->clave<<endl;
        for (int i = 0; i < clave.length(); i++)
        {
            //string au = string(clave[i] + string(""));
            //cout << "quiero nodo: "<< clave[i]<<endl;
            int indexAscii = int(clave[i]) - int('A');//lo centramos en 0 los index
            if(nodoAct->siguientes[indexAscii] != NULL) { //si existe
                //cout << "exis nodo"<<endl;
            }else {//si es null => lo creo
                //cout <<"t]engo q crearlo"<<endl;
                Nodo* nuevoNodo = iniciarNodo();
                nodoAct->siguientes[indexAscii] = nuevoNodo;
            }
            //cout << "nodoact antes: "<< nodoAct->clave<<endl;
            nodoAct = nodoAct->siguientes[indexAscii];
            nodoAct->clave = string(nodoPadre->clave) + string(clave[i] + string(""));
            //cout << "nodoActClave: "<< nodoAct->clave<< ", padre clave: "<<nodoPadre->clave<<endl;
            //cout << "clave[i]: "<<clave[i]<<" clave otra: "<< nodoAct->clave<<endl;
            nodoPadre=nodoAct;

        }
        //cout << "final clave: "<< nodoPadre->clave<<endl;
        nodoAct->definicion = new T();
        _size++;
        return *(nodoAct->definicion);
    }else { //existe
        Nodo* nodoAct = raiz;
        for (int i = 0; i < clave.length(); ++i)
        {
            int indexAscii = int(clave[i]) - int('A');//lo centramos en 0 los index
            nodoAct = nodoAct->siguientes[indexAscii];
        }
        //cout << "clave del nodo a retornar: "<< nodoAct->clave <<endl;
        return *(nodoAct->definicion);
    }
}
/*
template <typename T>
T& trie<T>::operator[](const tuple<string,string>& c){
    //veo si existe y devuelvo significado, si no la creo
    string clave = get<0>(c);
    if(count(clave) == 0) {//no existe
        //Puede pasar que este vacio el trie o no
        Nodo* nodoAct = raiz;
        Nodo* nodoPadre = raiz;
        for (int i = 0; i < clave.length(); i++)
        {
            //cout << "quiero nodo: "<< clave[i]<<endl;
            int indexAscii = int(clave[i]) - int('A');//lo centramos en 0 los index
            if(nodoAct->siguientes[indexAscii] != NULL) { //si existe
                //cout << "exis nodo"<<endl;
            }else {//si es null => lo creo
                //cout <<"t]engo q crearlo"<<endl;
                Nodo* nuevoNodo = iniciarNodo();
                nodoAct->siguientes[indexAscii] = nuevoNodo;
            }
            nodoAct->clave = string(nodoPadre->clave) + string(clave[i] + string(""));
            nodoPadre = nodoAct;
            nodoAct = nodoAct->siguientes[indexAscii];
        }

        nodoAct->definicion = new T(clave);
        _size++;
        return *(nodoAct->definicion);
    }else { //existe
        Nodo* nodoAct = raiz;
        for (int i = 0; i < clave.length(); ++i)
        {
            int indexAscii = int(clave[i]) - int('A');//lo centramos en 0 los index
            nodoAct = nodoAct->siguientes[indexAscii];
        }
        return *(nodoAct->definicion);
    }
}*/

template <typename T>
T& trie<T>::operator[](const tuple<string, int> &clave_w){
    //veo si existe y devuelvo significado, si no la creo
    string clave = get<0>(clave_w);
    int w = get<1>(clave_w);
    cv = w;
    if(count(clave) == 0) {//no existe
        //Puede pasar que este vacio el trie o no
        Nodo* nodoAct = raiz;
        Nodo* nodoPadre = raiz;
        for (int i = 0; i < clave.length(); i++)
        {
            //cout << "quiero nodo: "<< clave[i]<<endl;
            int indexAscii = int(clave[i]) - int('A');//lo centramos en 0 los index
            if(nodoAct->siguientes[indexAscii] != NULL) { //si existe
            }else {//si es null => lo creo
                Nodo* nuevoNodo = iniciarNodo();
                nodoAct->siguientes[indexAscii] = nuevoNodo;
            }
            //cout << "nodoact antes: "<< nodoAct->clave<<endl;
            nodoAct = nodoAct->siguientes[indexAscii];
            nodoAct->clave = string(nodoPadre->clave) + string(clave[i] + string(""));
            //cout << "nodoActClave: "<< nodoAct->clave<< ", padre clave: "<<nodoPadre->clave<<endl;
            //cout << "clave[i]: "<<clave[i]<<" clave otra: "<< nodoAct->clave<<endl;
            nodoPadre=nodoAct;
        }

        nodoAct->definicion = new T(w);
        _size++;
        return *(nodoAct->definicion);
    }else { //existe
        Nodo* nodoAct = raiz;
        for (int i = 0; i < clave.length(); ++i)
        {
            int indexAscii = int(clave[i]) - int('A');//lo centramos en 0 los index
            nodoAct = nodoAct->siguientes[indexAscii];
        }
        return *(nodoAct->definicion);
    }
}




template<typename T>
typename trie<T>::Nodo* trie<T>::iniciarNodo() {
    Nodo* nuevoNodo = new Nodo;

    nuevoNodo->siguientes = new Nodo *[256];
    for (int i = 0; i < 256; i++)
    {
        nuevoNodo->siguientes[i] = nullptr;
    }
    nuevoNodo->definicion = nullptr;
    nuevoNodo->clave = "";
    return nuevoNodo;
}


template <typename T>
int trie<T>::count(const string& clave) const{
    //chequeamos si esta definida la clave: return 1 o 0
    //cout << "entramos en count"<<endl;
    if(_size==0) {
        //cout << "0 cosas"<<endl;
        return 0;
    }else {
        //cout <<"hay cosas"<<endl;
        int indexAscii;
        Nodo* nodoAct = raiz;
        int i = 0;
        while(i < clave.length()){
            //cout << "revisando "<< clave[i]<<endl;
            indexAscii = int(clave[i]) - int('A'); //movido para que empiece en 0 los indices

            //antes era siguientes[indexAscii]
            if(nodoAct != nullptr && nodoAct->siguientes[indexAscii] != nullptr) {
                nodoAct = nodoAct->siguientes[indexAscii];
                //cout << "no es nul en: "<< clave[i]<<endl;
            }else return 0;
            i++;
        }
        if(i == clave.length())
        {
            //cout << "ACA ESTOY ENTRANDO PARAR REVISAR DE "<<clave<<endl;
            if (nodoAct->definicion!=nullptr){
                //cout << "ENTRA A QUE DEFINICION ESTA DEF"<<endl;
                return 1;
            }else {
                //cout << "ENTRA A QUE DEFINICION NO ESTA DEF"<<endl;
                return 0;
            }
        }else
        {
            return 0;
        }

    }

}

template <typename T>
const T& trie<T>::at(const string& clave) const {
    return (*this)[clave];
}

template <typename T>
T& trie<T>::at(const string& clave) {
    return (*this)[clave];
}

template <typename T>
void trie<T>::erase(const string& clave) {
    //PRE: LA CLAVE EXISTE
    Nodo* nodoEliminar = nullptr;
    Nodo* nodoRecorro = raiz;
    bool liberarNodos = false;
    int indiceDesde = 0;
    int indiceAdicional = 0;
    //cout << "ENTRO A BORRAR: "<<clave<<endl;
    for (int i = 0; i < clave.length(); i++)
    {
        //cout<< "actualmente en letra : "<< clave[i]<<endl;
        int index = int(clave[i]) - int('A');//centro en 0 el indice
        nodoRecorro = nodoRecorro->siguientes[index];
        if(i==clave.length()-1) {
            nodoEliminar = nodoRecorro;
            if(cantHijosNodoAct(nodoRecorro) == 0) {
                liberarNodos = true; //puedo liberar nodos ya que estoy eliminando una palabra q no es prefijo de ninguno
                indiceAdicional++;
            }else {
                //cout << "como tiene hijos entraaca"<<endl;
                delete nodoEliminar->definicion;
                nodoEliminar->definicion = nullptr;
            }

        }else {
            if(cantHijosNodoAct(nodoRecorro) == 1) {
                indiceAdicional++;
            }else {
                indiceAdicional = 0;
                indiceDesde = i+1;
            }
        }
    }
    _size--;
    //ahora libero los nodos que ya no tienen motivo de ser
    if(liberarNodos) {
        int index;
        nodoRecorro = raiz;
        Nodo* nodoAux = nullptr;
        int i = 0;
        if(indiceDesde!=0) {
            for (i = 0; i <= indiceDesde; ++i)
            {
                index = int(clave[i]) - int('A');
                nodoRecorro = nodoRecorro->siguientes[index];
                if(i +1 == indiceDesde) nodoEliminar = nodoRecorro;
            }
            nodoAux = nodoRecorro;
            borrarNodos(nodoRecorro);
            delete[] nodoAux->siguientes;
            delete nodoAux;
            nodoEliminar->siguientes[index] = nullptr;
        }else {
            index = int(clave[0]) -int('A');
            nodoRecorro = raiz->siguientes[index];
            nodoEliminar = raiz;
            nodoAux = nodoRecorro;
            borrarNodos(nodoRecorro);
            delete[] nodoAux->siguientes;
            delete nodoAux;
            raiz->siguientes[index] = nullptr;
        }
    }
}

template<typename T>
int trie<T>::cantHijosNodoAct(Nodo* nodo) {
    int cantHijos = 0;
    for (int i = 0; i < 256; i++)
    {
        if(nodo->siguientes[i] != NULL) cantHijos++;
    }
    return cantHijos;
}


template <typename T>
int trie<T>::size() const{
    return _size;
}

template<typename T>
typename trie<T>::Nodo* trie<T>::nodoSignificado(const string& clave) {
    Nodo* nodoAct = raiz;
    if(count(clave) > 0 && clave != ""){
        for (int i = 0; i < clave.length(); ++i)
        {
            int indexAscii = int(clave[i]) - int('A');//lo centramos en 0 los index
            nodoAct = nodoAct->siguientes[indexAscii];

        }
    }
    return nodoAct;
}

template <typename T>
bool trie<T>::empty() const{
    return (_size==0)? true:false;
}


template<typename T>
trie<T>::ItDiccTrie::ItDiccTrie(){
}

template<typename T>
trie<T>::ItDiccTrie::ItDiccTrie(Nodo *nodo){
    cout << "INICIO DIC CON NODO DE CLAVE: "<< nodo->clave<<endl;
    if(nodo->clave!="") {
        _actual = nodo;
        _actual->definicion = nodo->definicion;
        _actual->siguientes = nodo->siguientes;
        _actual->clave = nodo->clave;
        clave = nodo->clave;
    }else {
        _actual = nodo;
        _actual->clave = "";
        clave = "";
    }

}

template<typename T>
T& trie<T>::ItDiccTrie::operator*() const{
    if(_actual->clave != ""){
        return *(_actual->definicion);
    }
    /*else {
        T* aux = new T;
        return *aux;
    }*/
}
template<typename T>
string trie<T>::ItDiccTrie::claveActual() const{
    return _actual->clave;
}
