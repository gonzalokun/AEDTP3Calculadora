#ifndef PROJECT_DICCIONARIOTRIE_H
#define PROJECT_DICCIONARIOTRIE_H

#include <string>
#include <stack>

using namespace std;

template<class T>
class DiccTrie{
public:

    DiccTrie();

    void definir(DiccTrie dic, string clave, T& def);

    void estaDefinido(const DiccTrie, string clave) const;

    T& significado(const DiccTrie dic, string clave) const;

    ~DiccTrie();

private:

    struct Nodo{
        Nodo** siguientes;
        T* definicion;
        string clave;
        Nodo();
    };

    Nodo* _raiz;

    //INSERTE aux DE QUIEN QUIERA PONER SU TALLER

public: //ITERADOR

    class ItDiccTrie{

        friend class DiccTrie<T>;

    public:

        ItDiccTrie();

        T& operator*() const;

        string claveActual() const;

//        bool operator==(const ItDiccTrie& otro) const;
//
//        void operator++();
//
//        void operator--();

    private:
        Nodo* _actual;
        stack<Nodo*> _recorridos;

        ItDiccTrie(Nodo*,  stack<Nodo*>);
    };

//    ItDiccTrie begin();
//
//    ItDiccTrie end();

};

#endif //PROJECT_DICCIONARIOTRIE_H