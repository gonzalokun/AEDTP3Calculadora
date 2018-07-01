#ifndef trie2_H_
#define trie2_H_

#include <string>

using namespace std;

template<typename T>
class triee {
public:
    /**
    CONSTRUCTOR
    * Construye un diccionario vacio.
    **/
    triee();

    /**
    CONSTRUCTOR POR COPIA
    * Construye un diccionario por copia.
    **/
    triee(const triee<T>& aCopiar);

    /**
    OPERADOR ASIGNACION
     */
    triee& operator=(const triee& d);

    /**
    DESTRUCTOR
    **/
    ~triee();

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
        ~Nodo();
        Nodo** siguientes;
        T* definicion;
    };

    bool sonHijosNulos(Nodo* nodoARevisar);

    Nodo* copiarNodos(Nodo* nodoACopiar);

    Nodo* raiz;
    int _size;
};

#include "triee.hpp"

#endif // trie2_H_
