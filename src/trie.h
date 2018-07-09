#ifndef trie_H_
#define trie_H_

#include <string>
#include <vector>

using namespace std;

template<typename T>
class trie {
public:
    /**
    CONSTRUCTOR
    * Construye un diccionario vacio.
    **/
    trie();

    /**
    CONSTRUCTOR POR COPIA
    * Construye un diccionario por copia.
    **/
    trie(const trie<T>& aCopiar);

    /**
    OPERADOR ASIGNACION
     */
    trie& operator=(const trie& d);

    /**
    DESTRUCTOR
    **/
    ~trie();

    /**
    operator[]
    * Acceso o definición de pares clave/valor
    **/


    T &operator[](const string &);
    T &operator[](const tuple<string, int>& clave_w);
    T &operator[](const tuple<string,string>& c);
    /**
    COUNT
    * Devuelve la cantidad de apariciones de la clave (0 o 1).
    * Sirve para identificar si una clave está definida o no.
    **/

    int count(const string &key) const;

    /**
    AT
    * Dada una clave, devuelve su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    -- Versión modificable y no modificable
    **/
    const T& at(const string& key) const;
    T& at(const string& key);

    /**
    ERASE
    * Dada una clave, la borra del diccionario junto a su significado.
    * PRE: La clave está definida.
    --PRODUCE ALIASING--
    **/
    void erase(const string& key);

    /**
     SIZE
     * Devuelve cantidad de claves definidas */
    int size() const;

    /**
     EMPTY
     * devuelve true si no hay ningún elemento en el diccionario */
    bool empty() const;


    int cv; //capcidad ventana
private:

    struct Nodo{
        Nodo** siguientes;
        T* definicion;
        string clave;
    };

    Nodo* raiz;
    int _size;
    Nodo* iniciarNodo();
    void copiarNivel(Nodo*&,Nodo*);
    void copiarNivel(Nodo*&,Nodo*,int);
    void borrarNodos(Nodo*);
    int cantHijosNodoAct(Nodo*);


public:
    //PRE clave pertenece al trie, es decir, count(clave)> 0
    Nodo* nodoSignificado(const string& clave);
    class ItDiccTrie{

        friend class trie<T>;

    public:
        ItDiccTrie();
        ~ItDiccTrie();
        ItDiccTrie(Nodo*);
        T& operator*() const;
        void borrarNodos(Nodo*);
        string claveActual() const;
        Nodo* getNodo();
    private:
        Nodo* _actual;
        string clave; //clave del nodo actual

    };

};

#include "trie.hpp"

#endif // trie_H_
