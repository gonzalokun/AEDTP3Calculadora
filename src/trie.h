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

    T &operator[](const string &key);

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

private:

    struct Nodo {
        Nodo** siguientes;
        T* definicion;

    };

    Nodo* raiz;
    int _size;

    Nodo* iniciarNodo();
    void copiarNivel(Nodo*&,Nodo*);
    void borrarNodos(Nodo*);
    int cantHijosNodoAct(Nodo*);

};

#include "trie.hpp"

#endif // trie_H_
