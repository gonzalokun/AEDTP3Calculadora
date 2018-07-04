#include "Calculadora.h"
#include <tuple>

Calculadora::Calculadora() {
    //cout << "Se inicializa la calculadora"<<endl;

    //get<0>(rutinaActual) = "";
    //get<1>(rutinaActual) = nullptr;
}

Calculadora::~Calculadora() {

}

Calculadora::superInstruccion::~superInstruccion() {
    //delete itRut;
}

void Calculadora::nuevaCalculadora(Programa p, rutina r, int capVent){
    //cout << "SE CONSTRUYE NUEVA CALCULADORA"<<endl;
    W = capVent;
    ejecutando = true;
    instanteActual = 0;
    indiceInstruccionActual = 0;
    variablePorNombre.cv = W;
    rutinasProg.cv = W;


    //pasada 1: recorremos rutinas de p y las guardamos
    list<rutina>::const_iterator it = (p.getRutinas()).begin();
    while (it != (p.getRutinas()).end()) {
        //Habria que tener contada la cantidad de instrucciones de cada rutina!!
        rutinasProg[*it] = vector<superInstruccion>();

        if(*it == r) { //si es la rutina con la que hay que empezar
            //cout <<"--iniciando rutinaactual"<<endl;
            rutinaActual = trie<vector<superInstruccion>>::ItDiccTrie(rutinasProg.nodoSignificado(r));
            ////cout <<"LA CLAVE ASOCIADA A LA RUTINA ACTUAL ES: " <<(*rutinaActual).back().itRut->claveActual()<<endl;
        }
        it++;
    }
    //terminadas de pasar las rutinas

    //cout << "EMPIEZA PASADA 2"<<endl;
    //pasada 2: variables
    //recorro instrucciones de rutina para ver las variables
    it = (p.getRutinas()).begin();
    while (it != (p.getRutinas()).end()) {
        ////cout << "PASANDO POR RUTINA " <<  p.instruccion(*it,0).nombreRutina()<<" QUE TIENE #INST = "<< p.longitud(*it)<<endl;
        for (int i = 0; i < p.longitud(*it); ++i) { //recorro instrucciones de la rutina actual
            ////cout << "INSTRUCCION I: "<< i<< "OPERACION : " << p.instruccion(*it,i).getOp()<<endl;
            if(p.instruccion(*it,i).getOp() == oWrite || p.instruccion(*it,i).getOp() == oRead) {
                ////cout << "INSTRUCCION I: "<< i<< "OPERACION : " << p.instruccion(*it,i).getOp()<<endl;
                estructuraDeVariablePorNombre est = estructuraDeVariablePorNombre(capVent);
                est.vent.registrar(make_tuple(0,0));
                est.valorHistorico.push_back(make_tuple(0,0));
                variablePorNombre[make_tuple(p.instruccion(*it,i).nombreVariable(), capVent)] = est;

            }
        }
        it++;
    }

    //cout << "TERMINA PASADA 2"<<endl;
    //pasada 3: lista de instrucciones a cada rutinas.
    it = (p.getRutinas()).begin();
    ////cout << "cnatidad de rutinas: "<<p.getRutinas().size()<<endl;
    while(it!= (p.getRutinas()).end()) {
        //cout << "ANALIZANDO RUTINA: "<<(*it)<<endl;
        vector<superInstruccion> vec;
        if(p.longitud(*it) == 0) {
            rutinasProg[*it] = vec;
        }
        //si tiene instrucciones
        for (int i = 0; i < p.longitud(*it); ++i) {
            Operacion op;
            int cNum;
            op = p.instruccion(*it,i).getOp();
            Instruccion instr = p.instruccion(*it,i);
            cNum = p.instruccion(*it,i).constanteNumerica();
            trie<estructuraDeVariablePorNombre>::ItDiccTrie auxItVar;
            auxItVar = trie<estructuraDeVariablePorNombre>::ItDiccTrie(variablePorNombre.nodoSignificado(""));

            if(op == oRead || op == oWrite) {
                auxItVar = trie<estructuraDeVariablePorNombre>::ItDiccTrie(variablePorNombre.nodoSignificado(p.instruccion(*it,i).nombreVariable()));
            }else{
                //auxItVar =  trie<estructuraDeVariablePorNombre>::ItDiccTrie(variablePorNombre.nodoSignificado(""));
            }

            trie<vector<superInstruccion>>::ItDiccTrie* auxItRut;

            if(oJump == op || op == oJumpz) {
                ////cout <<"EL NOMBRE DE LA RUTINA DEL JUMP -------------"<<p.instruccion(*it,i).getRutinaJump()<<endl;
                auxItRut = new trie<vector<superInstruccion>>::ItDiccTrie(rutinasProg.nodoSignificado(p.instruccion(*it,i).getRutinaJump()));
            }else {
                auxItRut = new trie<vector<superInstruccion>>::ItDiccTrie(rutinasProg.nodoSignificado(""));
            }
            superInstruccion sp;
            sp.constanteNumerica=cNum;
            sp.op = op;
            sp.i = instr;
            sp.itVarNombre = auxItVar;
            sp.itRut = auxItRut;
            vec.push_back(sp);
            rutinasProg[*it] = vec;
        }
        it++;
    }
    //cout << "size rutinas prog: "<<rutinasProg.size()<<endl;
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
    superInstruccion superIns = (*rutinaActual)[indiceInstruccionActual];

    Operacion op = superIns.op;
    /*//cout <<"el tipo de operacion de la instrucciona  ejecutar es: "<<op<<endl;
    if(op==6){
        //cout<<"la rutina a la q apunta es: "<<(superIns.itRut)->claveActual()<<endl;
    }
    //cout <<"LA CLAVE ASOCIADA A LA RUTINA ACTUAL ES: " <<(*rutinaActual).back().itRut->claveActual()<<endl;
*/
    bool jumpValido;

    if((op != oJump && op != oJumpz)){

        //Operaciones Push, Add, Sub, Mul, Read, Write
        //indiceInstruccionActual++;
        //instanteActual++;
    }

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
        int tamVent = (*it).vent.tam();

        //Si la variable tiene cosas en la ventana se usa, sino es 0
        //cout << "creo nueva ventana de valores en instante "<<instanteActual <<endl;
        if((*it).vent.tam() > 0){

            valor valorAPushear = get<1>((*it).vent[tamVent - 1]);
            (*it).vent.registrar(make_tuple(instanteActual,valorAPushear));
            (*it).valorHistorico.push_back(make_tuple(instanteActual,valorAPushear));
            pila.push(valorAPushear);
        }
        else{
            (*it).vent.registrar(make_tuple(instanteActual,0));
            (*it).valorHistorico.push_back(make_tuple(instanteActual,0));
            pila.push(0);
        }

    }
    else if(op == oWrite){ // Idem
        int v;
        if(pila.empty()){
            v = 0;
        }else {
            v = pila.top();
            pila.pop();
        }
        tuple<instante, valor> t;
        get<0>(t) = instanteActual;
        get<1>(t) = v;
        //cout <<"ESTOY EN WRITE Y MI INSTANTE ACTUAL DONDE VOY A CREAR ES "<< instanteActual<<endl;
        //cout <<"con valor: "<<v<<endl;
        trie<estructuraDeVariablePorNombre>::ItDiccTrie it = superIns.itVarNombre;
        //Se registra directamente en la variable
        (*it).vent.registrar(t);
        (*it).valorHistorico.push_back(t);

    }
    else if(op == oJump){ // Utiliza nombre de rutina
        // necesito acceder al vector de isntrucciones de la rutina asociada al jump de la rutina actual
        //cout << "----*-*-cantidad de instrucciones de la rutina: " << (*rutinaActual).size() <<endl;
        //cout <<"nombre de la instruccion " << (*rutinaActual)[indiceInstruccionActual].i.getRutinaJump();
        rutina rJump=(*rutinaActual)[indiceInstruccionActual].i.getRutinaJump();

        if((*superIns.itRut).claveActual() == ""){ //pasa si el jump tiene una rutina inex
            jumpValido = false;
        }else {
            jumpValido = true;
        }

    }
    else if(op == oJumpz){ // Idem

        if((*superIns.itRut).claveActual() == ""){ //pasa si el jump tiene una rutina inex
            jumpValido = false;
        }else {//el jump es de rutina valida
            jumpValido = true;
        }
    }

    if(op == oJump){
        //Jump a otra rutina
        instanteActual++;
        if(jumpValido){
            indiceInstruccionActual = 0;
            rutinaActual = *(superIns.itRut);
        }
        else{
            //cout << "ES JUMP INCORRECTO"<<endl;
            //Jump incorrecto, se termina la ejecucion
            ejecutando = false;
        }
    }
    else if(op == oJumpz){
        //Jumpz
        indiceInstruccionActual++;
        instanteActual++;

        bool topeCero = ((not pila.empty() && pila.top() == 0) || pila.empty());
        if(topeCero) {
            if(jumpValido){
                indiceInstruccionActual = 0;
                rutinaActual = *(superIns.itRut);
            }
            else{
                //cout << "ES JUMP INCORRECTO"<<endl;
                //Jump incorrecto, se termina la ejecucion
                ejecutando = false;
            }
        }

    }
    else{
       // if(instanteActual==0){
            indiceInstruccionActual++;
            instanteActual++;
        //}
    }
    //cout <<"NOMBRE DE RUTINA ACTUAL : " << (*rutinaActual).back().itRut->claveActual()<<endl;
    //cout << "cant inst: " <<(*rutinaActual).size()<<endl;
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
    //cout << "TERMINADA instante actual " <<instanteActual<<endl;
}

void Calculadora::asignarVariable(variable x, valor v){
    //si el ultimo instante de la variable x es el instante actual, modificamos el valor
    //si el ultimo instante es menor al isntante actual, creamos un nuevo nodo en la lista
    //cout <<"-------------ASIGNAR VAR "<< x << " "<<v<<" en instante "<<instanteActual<<"------------------"<<endl;
    if(variablePorNombre.count(x) > 0 ){ //si existe
        //cout << "Existe la variable a asignar"<<endl;
        int tam = variablePorNombre[make_tuple(x,W)].vent.tam();

        if(tam == 0) {
            //cout << "como no tiene ventana registrada, entro aca"<<endl;
            variablePorNombre[make_tuple(x,W)].vent.registrar(make_tuple(instanteActual,v));
            variablePorNombre[make_tuple(x,W)].valorHistorico.push_back(make_tuple(instanteActual,v));
        }else {
            int ultInst = get<0>(variablePorNombre[make_tuple(x,W)].vent[tam-1]);
            //cout << "instante actual: "<< instanteActual<< " ultimo inst regist: "<<ultInst<<endl;

            if(ultInst == instanteActual) {
                get<1>(variablePorNombre[make_tuple(x,W)].vent[tam-1]) = v;
                get<1>(variablePorNombre[make_tuple(x,W)].valorHistorico.back()) = v;
            }else {
                variablePorNombre[make_tuple(x,W)].vent.registrar(make_tuple(instanteActual,v));
                variablePorNombre[make_tuple(x,W)].valorHistorico.push_back(make_tuple(instanteActual,v));
                //cout << "tam inicial: "<<tam<<endl;
                //cout << "ahora la capacidad queda: "<<variablePorNombre[make_tuple(x,W)].vent.tam()<<endl;
            }
        }

    }else { //si no existe todavia la variable
        //CREAMOS LA VARIABLE CON VALOR V

        ////cout << "no existe la var " << x << endl;
        estructuraDeVariablePorNombre est(W);
        est.vent.registrar(make_tuple(instanteActual,v));
        est.valorHistorico.push_back(make_tuple(instanteActual,v));
        variablePorNombre[make_tuple(x,W)] = est;
        ////cout << "ahora el count de var es: "<< variablePorNombre.count(x)<<endl;
    }
    //int tam = variablePorNombre[make_tuple(x,W)].vent.tam();
    ////cout << "despues de asigna, vale: "<< get<1>(variablePorNombre[make_tuple(x,W)].vent[tam-1])<<endl;
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

int Calculadora::indiceInstante(int i,int s,instante busc,variable var){
    if(variablePorNombre[make_tuple(var,W)].vent.tam()>0) {
        int med = (s - i) / 2;
        if (med == 1 && get<0>(variablePorNombre[make_tuple(var,W)].vent[med]) != busc && get<0>(variablePorNombre[make_tuple(var,W)].vent[med]) > busc)
            return get<0>(variablePorNombre[make_tuple(var,W)].vent[med - 1]);
        else if (med == 1 && get<0>(variablePorNombre[make_tuple(var,W)].vent[med]) != busc && get<0>(variablePorNombre[make_tuple(var,W)].vent[med]) < busc)
            return get<0>(variablePorNombre[make_tuple(var,W)].vent[med + 1]);
        if (get<0>(variablePorNombre[make_tuple(var,W)].vent[med]) == busc)
            return med;

        if (get<0>(variablePorNombre[make_tuple(var,W)].vent[med]) > busc)
            return indiceInstante(i, med, busc, var);

        if (get<0>(variablePorNombre[make_tuple(var,W)].vent[med]) < busc)
            return indiceInstante(med, s, busc, var);
        return 0;
    }else {
        return 0;
    }
}


valor Calculadora::valorEnInstante(variable var, instante inst){
    //cout << "CONSULTANDO VALOR EN INSTANTE, VAR: "<<var<< " inst: "<< inst<< " inst act:"<<instanteActual<<endl;
    ////cout << "W:" <<W<<endl;
   /* if(instanteActual - inst < W) {
        if(variablePorNombre.count(var) > 0){
            //cout << "LA VAR QUE BUSCO EXISTE"<<endl;
            int cantInstantesVar = (variablePorNombre[make_tuple(var,W)].vent).tam();
            //cout << "cant de vent de la var: "<< cantInstantesVar<<endl;
            if(cantInstantesVar>instanteActual-inst){
                int tam = variablePorNombre[make_tuple(var,W)].vent.tam();
                int indice = indiceInstante(0,tam,inst,var);
                return get<1>((variablePorNombre[make_tuple(var,W)].vent)[indice]);//cantInstantesVar-1-(instanteActual-inst)
            }else {
                variablePorNombre[make_tuple(var,W)].vent.registrar(make_tuple(instanteActual,0));
                variablePorNombre[make_tuple(var,W)].valorHistorico.push_back(make_tuple(instanteActual,0));
                return 0;
            }

        }else {
        }
    } else {*/
        //cout << "busco valor en historico"<<endl;
        //valorHistorico::const_iterator it = (variablePorNombre[make_tuple(var,W)].valorHistorico).end();

        valorHistorico::const_iterator itend = (variablePorNombre[make_tuple(var,W)].valorHistorico).end();
        valorHistorico::const_iterator it = (variablePorNombre[make_tuple(var,W)].valorHistorico).begin();
        while(get<0>(*it) < inst && it !=itend ){
            //cout << "comparando inst: "<<get<0>(*it) << " con: " <<inst <<endl;
            it++;
        }
        if(it == itend || get<0>(*it) > inst) it--;
        //cout <<"devolviendo instante: " << get<0>(*it)<<" valor: "<<get<1>(*it)<<endl;
        return get<1>(*it);
    //}
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
    //cout << "estoy consultando getPila: "<< pila.empty()<<endl;
    ////cout << "pila top: "<< pila.top()<<endl;
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
