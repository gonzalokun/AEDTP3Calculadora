#include "Calculadora.h"
#include <tuple>

Calculadora::Calculadora() {
    cout << "Se inicializa la calculadora"<<endl;
    //get<0>(rutinaActual) = "";
    //get<1>(rutinaActual) = nullptr;
}

Calculadora::~Calculadora() {
}

void Calculadora::nuevaCalculadora(Programa p, rutina r, int capVent){
    cout << "SE CONSTRUYE NUEVA CALCULADORA"<<endl;
    W = capVent;
    ejecutando = true;
    instanteActual = 0;
    indiceInstruccionActual = 0;

    //pasada 1: recorremos rutinas de p y las guardamos
    list<rutina>::const_iterator it = (p.getRutinas()).begin();
    while (it != (p.getRutinas()).end()) {
        //Habria que tener contada la cantidad de instrucciones de cada rutina!!
        rutinasProg[*it] = vector<superInstruccion>();

        if(*it == r) { //si es la rutina con la que hay que empezar
            //entonces definimos un puntero hacia la rutina
            //get<0>(rutinaActual) = (*it);
            //get<1>(rutinaActual) = rutinasProg[r];
            cout << "def rutinaActual"<<endl;
            rutinaActual = trie<vector<superInstruccion>>::ItDiccTrie(rutinasProg.nodoSignificado(r));
            cout << "clave def: "<<rutinaActual.claveActual()<<endl;
        }
        it++;
    }
    //terminadas de pasar las rutinas

    //pasada 2: variables
    //recorro instrucciones de rutina para ver las variables
    it = (p.getRutinas()).begin();
    while (it != (p.getRutinas()).end()) {
        for (int i = 0; i < p.longitud(*it); ++i) { //recorro instrucciones de la rutina actual
            if(p.instruccion(*it,i).getOp() == oWrite || p.instruccion(*it,i).getOp() == oRead) {
                variablePorNombre[make_tuple(p.instruccion(*it,i).nombreVariable(), capVent)] = estructuraDeVariablePorNombre(capVent);
            }
        }
        it++;
    }


    //pasada 3: lista de instrucciones a cada rutinas.
    it = (p.getRutinas()).begin();
    cout << "cnatidad de rutinas: "<<p.getRutinas().size()<<endl;
    while(it!= (p.getRutinas()).end()) {
        cout << "ANALIZANDO RUTINA: "<<(*it)<<endl;
        vector<superInstruccion> vec;
        if(p.longitud(*it) == 0) {
            cout << "se define el vec vacio en rutinasProg"<<endl;
            rutinasProg[*it] = vec;
        }
        //si tiene instrucciones
        for (int i = 0; i < p.longitud(*it); ++i) {
            cout << "i: "<<i<<endl;
            Operacion op;
            int cNum;
            op = p.instruccion(*it,i).getOp();
            cNum = p.instruccion(*it,i).constanteNumerica();
            trie<estructuraDeVariablePorNombre>::ItDiccTrie auxItVar;
            auxItVar = trie<estructuraDeVariablePorNombre>::ItDiccTrie(variablePorNombre.nodoSignificado(""));
            cout <<"sigue1"<<endl;
            if(op == oRead || op == oWrite) {
                auxItVar = trie<estructuraDeVariablePorNombre>::ItDiccTrie(variablePorNombre.nodoSignificado(p.instruccion(*it,i).nombreVariable()));
            }else{
                //auxItVar =  trie<estructuraDeVariablePorNombre>::ItDiccTrie(variablePorNombre.nodoSignificado(""));
            }
            cout <<"sigue2"<<endl;

            trie<vector<superInstruccion>>::ItDiccTrie* auxItRut;
            cout <<"sigue3"<<endl;

            if(oJump == op || op == oJumpz) {
                auxItRut = new trie<vector<superInstruccion>>::ItDiccTrie(rutinasProg.nodoSignificado(p.instruccion(*it,i).nombreRutina()));
            }else {
                auxItRut = new trie<vector<superInstruccion>>::ItDiccTrie(rutinasProg.nodoSignificado(""));
            }
            superInstruccion sp;
            sp.constanteNumerica=cNum;
            sp.op = op;
            sp.itVarNombre = auxItVar;
            sp.itRut = auxItRut;
            vec.push_back(sp);
            cout <<"p1"<<endl;
            rutinasProg[*it] = vec;
            cout << "p2"<<endl;
        }
        it++;
    }
    cout << "size rutinas prog: "<<rutinasProg.size()<<endl;
    if(rutinasProg.size() == 0){
        ejecutando = false;
    } else {
        //if(rutinasProg.count(rutinaActual.claveActual()) == 0) ejecutando = false;
    }


}
bool Calculadora::getEjecutando() const{
    return ejecutando;
}
void Calculadora::ejecutarUnPaso(){

    //superInstruccion superIns = (*(get<1>(rutinaActual)))[indiceInstruccionActual];

cout << "1"<<endl;
cout << "clave de rutinasact: "<< rutinaActual.claveActual()<<endl;
cout << "indice rut act: "<<indiceInstruccionActual<<endl;
cout << "tam vec sup: "<<(*rutinaActual).size()<<endl;
    superInstruccion superIns = (*rutinaActual)[indiceInstruccionActual];
cout << "2"<<endl;
    Operacion op = superIns.op;

    bool jumpValido;


    if(op == oPush){ // Utiliza valor
        int valor = superIns.constanteNumerica;
        pila.push(valor);
    }
    else if(op == oAdd){ // Sin parametros

        if(pila.size() >= 2){
            int v1 = pila.top();
            pila.pop();
            int v2 = pila.top();
            pila.pop();

            pila.push(v1+v2);
        }
        else if(pila.size() == 1){
            int v1 = pila.top();
            pila.pop();

            pila.push(v1);
        }
        else{
            pila.push(0);
        }

    }
    else if(op == oSub){ // Idem
        if(pila.size() >= 2){
            int v1 = pila.top();
            pila.pop();
            int v2 = pila.top();
            pila.pop();

            pila.push(v2-v1);
        }
        else if(pila.size() == 1){
            int v1 = pila.top();
            pila.pop();

            pila.push(-v1);
        }
        else{
            pila.push(0);
        }
    }
    else if(op == oMul){ // Idem
        if(pila.size() >= 2){
            int v1 = pila.top(); // USAR PRIMEROPILA Y SEGUNDOPILA ?
            pila.pop();
            int v2 = pila.top();
            pila.pop();

            pila.push(v2*v1);
        }
        else if(pila.size() == 1){
            int v1 = pila.top();
            pila.pop();

            pila.push(v1*0);
        }
        else{
            pila.push(0);
        }
    }
    else if(op == oRead){ // Utiliza nombre de variable
        trie<estructuraDeVariablePorNombre>::ItDiccTrie it = superIns.itVarNombre;

        // Podria cambiar segun como implementemos el diccTrie.
//        if(it != NULL){ // Verificar que esto se puede hacer.
//            int v = get<0>((get<0>(*it))[get<0>(*it).tam()]);
//            pila.push(v);
//        }else{
//            pila.push(0);
//        }

        int tamVent = (*it).vent.tam();

        //Si la variable tiene cosas en la ventana se usa, sino es 0
        if((*it).vent.tam() > 0){
            valor valorAPushear = get<1>((*it).vent[tamVent - 1]);
            pila.push(valorAPushear);
        }
        else{
            pila.push(0);
        }

    }
    else if(op == oWrite){ // Idem
        int v = pila.top();
        pila.pop();

        tuple<instante, valor> t;
        get<0>(t) = instanteActual;
        get<1>(t) = v;

        // Podria cambiar segun como implementemos el diccTrie.
        //itVarNombre it = get<2>(superIns);

        trie<estructuraDeVariablePorNombre>::ItDiccTrie it = superIns.itVarNombre;

        //Se registra directamente en la variable
        (*it).vent.registrar(t);
        (*it).valorHistorico.push_back(t);

//        if(it != NULL){ // El iterador existe
//            (get<0>(*it)).registrar(t);
//            (get<1>(*it)).push_back(t);
//        }
//        else{ // Si no existe, creo un nuevo iterador y le agrego los valores correspondientes.
//            itVarNombre* newIt = new itVarNombre;
//            get<2>(superIns) = *newIt;
//            it = get<2>(superIns);
//
//            (get<0>(*it)).registrar(t);
//            (get<1>(*it)).push_back(t);
//        }
    }
    else if(op == oJump){ // Utiliza nombre de rutina
        //itRut it = get<3>(superIns);

        trie<vector<superInstruccion>>::ItDiccTrie* punteroIt = superIns.itRut;
        trie<vector<superInstruccion>>::ItDiccTrie it = *(punteroIt);

        if((*it).empty()){
            //Hay instrucciones en la nueva rutina
            jumpValido = true;
        }
        else{
            //No hay instrucciones, la rutina ingresada no es válida
            jumpValido = false;
        }

    }
    else if(op == oJumpz){ // Idem
        //

        trie<vector<superInstruccion>>::ItDiccTrie* punteroIt = superIns.itRut;
        trie<vector<superInstruccion>>::ItDiccTrie it = *(punteroIt);

        if((*it).empty()){
            //Hay instrucciones en la nueva rutina
            jumpValido = true;
        }
        else{
            //No hay instrucciones, la rutina ingresada no es válida
            jumpValido = false;
        }
    }

    if(op == oJump){
        //Jump a otra rutina
        if(jumpValido){
            indiceInstruccionActual = 0;
            rutinaActual = *(superIns.itRut);
            instanteActual++;
        }
        else{
            //Jump incorrecto, se termina la ejecucion
            ejecutando = false;
        }
    }
    else if(op == oJumpz){
        //Jumpz
        if(pila.top() == 0){
            if(jumpValido){
                indiceInstruccionActual = 0;
                rutinaActual = *(superIns.itRut);
                instanteActual++;
            }
            else{
                //Jump incorrecto, se termina la ejecucion
                ejecutando = false;
            }
        }
        else{
            indiceInstruccionActual++;
            instanteActual++;
        }
    }
    else{
        //Operaciones Push, Add, Sub, Mul, Read, Write
        indiceInstruccionActual++;
        instanteActual++;
    }

    if(indiceInstruccionActual >= (*rutinaActual).size()){
        //Llegamos al final de la rutina
        ejecutando = false;
    }

//    if(op == oPush || op == oAdd || op == oSub || op == oMul){
//        indiceInstruccionActual++;
//        instanteActual++;
//    }
//    else if(op == oRead || op == oWrite){
//        indiceInstruccionActual++;
//        instanteActual++;
//    }
//    else{
//        if(jumpValido){
//            indiceInstruccionActual = 0;
//        }
//        else{ // No saltó por algun motivo. (Z o normal?)
//            indiceInstruccionActual++;
//        }
//        instanteActual++;
//
//    }

}

void Calculadora::asignarVariable(variable x, valor v){
    //si el ultimo instante de la variable x es el instante actual, modificamos el valor
    //si el ultimo instante es menor al isntante actual, creamos un nuevo nodo en la lista
    cout <<"-------------ASIGNAR VAR "<< x << " "<<v<<"------------------"<<endl;
    if(variablePorNombre.count(x) > 0 ){ //si existe
        cout << "Existe la variable a asignar"<<endl;
        int tam = variablePorNombre[make_tuple(x,W)].vent.tam();

        if(tam == 0) {
            cout << "como no tiene ventana registrada, entro aca"<<endl;
            variablePorNombre[make_tuple(x,W)].vent.registrar(make_tuple(instanteActual,v));
            variablePorNombre[make_tuple(x,W)].valorHistorico.push_back(make_tuple(instanteActual,v));
        }else {
            int ultInst = get<0>(variablePorNombre[make_tuple(x,W)].vent[tam-1]);
            cout << "instante actual: "<< instanteActual<< " ultimo inst regist: "<<ultInst<<endl;

            if(ultInst == instanteActual) {
                get<1>(variablePorNombre[make_tuple(x,W)].vent[tam-1]) = v;
                get<1>(variablePorNombre[make_tuple(x,W)].valorHistorico.back()) = v;
            }else {
                variablePorNombre[make_tuple(x,W)].vent.registrar(make_tuple(instanteActual,v));
                variablePorNombre[make_tuple(x,W)].valorHistorico.push_back(make_tuple(instanteActual,v));
            }
        }

    }else { //si no existe todavia la variable
    cout << "como la var no existe"<<endl;
        estructuraDeVariablePorNombre est(W);
        est.vent.registrar(make_tuple(instanteActual,v));
        est.valorHistorico.push_back(make_tuple(instanteActual,v));
        variablePorNombre[make_tuple(x,W)] = est;
        cout << "ahora el count de var es: "<< variablePorNombre.count(x)<<endl;
    }
    cout << "fin"<<endl;
}
instante Calculadora::getInstanteActual() const{
    return instanteActual;
}

rutina Calculadora::getRutinaActual() const{
    //return get<0>(rutinaActual);
    return rutinaActual.claveActual();
}

int Calculadora::getIndiceInstruccionActual() const{
    return indiceInstruccionActual;
}

valor Calculadora::valorEnInstante(variable var, instante inst){
    cout << "CONSULTANDO VALOR EN INSTANTE, VAR: "<<var<< " inst: "<< inst<< " inst act:"<<instanteActual<<endl;
    cout << "W:" <<W<<endl;
    if(instanteActual - inst < W) {
        if(variablePorNombre.count(var) > 0){
            cout << "LA VAR QEU BUSCO EXISTE"<<endl;
            int cantInstantesVar = (variablePorNombre[make_tuple(var,W)].vent).tam();
            if(cantInstantesVar>instanteActual-inst){
                return get<1>((variablePorNombre[make_tuple(var,W)].vent)[instanteActual-inst]);
            }else {
                variablePorNombre[make_tuple(var,W)].vent.registrar(make_tuple(instanteActual,0));
                variablePorNombre[make_tuple(var,W)].valorHistorico.push_back(make_tuple(instanteActual,0));
                return 0;
            }

        }else {
            cout << "la var que busco NO Exisgte"<<endl;
        }
    } else {
        valorHistorico::const_iterator it = (variablePorNombre[make_tuple(var,W)].valorHistorico).end();
        int i = instanteActual;
        while(i >= inst && it != (variablePorNombre[make_tuple(var,W)].valorHistorico).begin()) {
            i--;
            --it;
        }
        return get<1>(*it);
    }
}

valor Calculadora::valorActualVariable(variable var){
    if(variablePorNombre.count(var) > 0) {
        int tam = variablePorNombre[make_tuple(var,W)].vent.tam();
        if(tam == 0) {
            return 0;
        }else{
            return get<1>((variablePorNombre[make_tuple(var,W)].vent)[tam-1]);

        }
    }
//QUE PASA SI PREGUNTAMOS POR UNA VAR QUE NO EXISTE??
//SEGUN EL TP1 HAY QUE CREARLA CON VALOR 0
}

const stack<valor>& Calculadora::getPila() const{
    return pila;
}

valor Calculadora::primeroPila() const{
    cout << "estoy consultando getPila: "<< pila.empty()<<endl;
    //cout << "pila top: "<< pila.top()<<endl;
    return (pila.empty())? 0 : (pila.top());
}

valor Calculadora::segundoPila() {

    if(pila.size() >= 2){
        valor v = pila.top();
        pila.pop();
        valor segundoPila = pila.top();
        pila.emplace(v);

        return segundoPila;
    }
    else{
        return 0;
    }
}

stack<valor>& Calculadora::getPilaSinDos() {
    pila.pop();
    pila.pop();
    return pila;
}

bool Calculadora::escribiendoVariable(variable &var) const{
    //Operacion opActual = get<0>((*(get<1>(rutinaActual)))[indiceInstruccionActual]);

    //Operacion opActual = get<0>((*(*rutinaActual))[indiceInstruccionActual]);

    Operacion  opActual = (*rutinaActual)[indiceInstruccionActual].op;

    if(opActual == oWrite){
        //Tengo que ver si la variable que esta en la instrucción actual es la que ingrese
        variable varDeInstActual = (*rutinaActual)[indiceInstruccionActual].itVarNombre.claveActual();

        if(var == varDeInstActual){
            return true;
        }
        else{
            return false;
        }
    }

    return false;
}

bool Calculadora::haySalto() {
    //VERSION COMENTADA SIN EL ITER
    //superInstruccion instActual = (*(get<1>(rutinaActual)))[indiceInstruccionActual];
    //Operacion opActual = get<0>((*(get<1>(rutinaActual)))[indiceInstruccionActual]);

    Operacion  opActual = (*rutinaActual)[indiceInstruccionActual].op;

    return (opActual == oJump || opActual == oJumpz);
}
