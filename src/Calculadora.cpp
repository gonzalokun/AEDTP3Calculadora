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
            rutinaActual = trie<vector<superInstruccion>>::ItDiccTrie(rutinasProg.nodoSignificado(r));
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

//    while(it!= (p.getRutinas()).end()) {
//        itRut punteroRut;
//        int i = 0;
//
//        Operacion op = p.instruccion(*it,i).getOp();
//        int constNum = p.instruccion(*it,i).constanteNumerica();
//        rutinasProg[*it]->resize(p.longitud(*it));
//
//        itVarNombre punteroVar = (new tuple<Ventana<tuple<instante, valor> >, valorHistorico>((variablePorNombre[make_tuple(*it,capVent)]).vent,(variablePorNombre[make_tuple(*it,capVent)]).valorHistorico));
//
//        for (i = 0; i < p.longitud(*it); ++i) {
//            punteroRut->push_back(p.instruccion(*it,i));
//            //armo mi vector de instruccions, pasando de la lista de instruccion de programa
//        }
//        rutinasProg[*it]->push_back(make_tuple(op, constNum, punteroVar, punteroRut));
//    }

    while(it!= (p.getRutinas()).end()) {

        vector<superInstruccion> vec;


        for (int i = 0; i < p.longitud(*it); ++i) {
            Operacion op;
            int cNum;
            op = p.instruccion(*it,i).getOp();
            cNum = p.instruccion(*it,i).constanteNumerica();
            trie<estructuraDeVariablePorNombre>::ItDiccTrie auxItVar;
            if(op == oRead || op == oWrite) {
                 auxItVar = trie<estructuraDeVariablePorNombre>::ItDiccTrie(variablePorNombre.nodoSignificado(p.instruccion(*it,i).nombreVariable()));
            }else{
                auxItVar =  trie<estructuraDeVariablePorNombre>::ItDiccTrie(variablePorNombre.nodoSignificado(""));
            }
            trie<vector<superInstruccion>>::ItDiccTrie* auxItRut;
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
            rutinasProg[*it] = vec;
        }

    }

}
bool Calculadora::getEjecutando() const{
    return ejecutando;
}

void Calculadora::ejecutarUnPaso(){

    //superInstruccion superIns = (*(get<1>(rutinaActual)))[indiceInstruccionActual];

    superInstruccion superIns = (*rutinaActual)[indiceInstruccionActual];

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

            pila.push(v1);
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
    cout <<"---------------------------------"<<endl;
    if(variablePorNombre.count(x) > 0 ){ //si existe
        int tam = variablePorNombre[make_tuple(x,W)].vent.capacidad()-1;
        int ultInst = get<0>(variablePorNombre[make_tuple(x,W)].vent[tam]);
        if(ultInst == instanteActual) {
            get<1>(variablePorNombre[make_tuple(x,W)].vent[tam]) = v;
            get<1>(variablePorNombre[make_tuple(x,W)].valorHistorico.back()) = v;
        }else {
            variablePorNombre[make_tuple(x,W)].vent.registrar(make_tuple(instanteActual,v));
            variablePorNombre[make_tuple(x,W)].valorHistorico.push_back(make_tuple(instanteActual,v));
        }
    }else { //si no existe todavia la variable
        estructuraDeVariablePorNombre est(W);
        est.vent.registrar(make_tuple(instanteActual,v));
        est.valorHistorico.push_back(make_tuple(instanteActual,v));
        variablePorNombre[make_tuple(x,W)] = est;
    }

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
    if(instanteActual - inst <= W) {
        if(variablePorNombre.count(var) > 0){
            return get<1>((variablePorNombre[make_tuple(var,W)].vent)[inst]);
        }
    } else {
        valorHistorico::const_iterator it = (variablePorNombre[make_tuple(var,W)].valorHistorico).end();
        int i = instanteActual;
        while(i >=inst && it != (variablePorNombre[make_tuple(var,W)].valorHistorico).begin()) {
            i--;
            --it;
        }
        return get<0>(*it);
    }
}

valor Calculadora::valorActualVariable(variable var){
    return get<0>(variablePorNombre[make_tuple(var,W)].vent[W-1]);
}

const stack<valor>& Calculadora::getPila() const{
    return pila;
}

valor Calculadora::primeroPila() const{
    return (pila.empty()) ? 0 : (pila.top());
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
