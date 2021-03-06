#include "Calculadora.h"
#include <tuple>

Calculadora::Calculadora() {
    //cout << "Se inicializa la calculadora"<<endl;

    //get<0>(rutinaActual) = "";
    //get<1>(rutinaActual) = nullptr;
}

Calculadora::~Calculadora() {
    for (int i = 0; i < vecRutinas.size(); ++i)
    {
        for (int x = 0; x < rutinasProg[vecRutinas[i]].size(); ++x)
        {
            delete rutinasProg[vecRutinas[i]][x].itRut;
            rutinasProg[vecRutinas[i]][x].itRut = nullptr;
        }
    }

}

Calculadora::superInstruccion::~superInstruccion(   ) {
    //delete itRut;
    //recorrer rutinsa prog y eliminar la ref a itrut

}

void Calculadora::nuevaCalculadora(Programa p, rutina const r, int const capVent){
    //cout << "SE CONSTRUYE NUEVA CALCULADORA"<<endl;
    W = capVent;
    ejecutando = true;
    instanteActual = 0;
    indiceInstruccionActual = 0;
    variablePorNombre.cv = W;
    rutinasProg.cv = W;
    int rExist = false;
    list<rutina>::const_iterator it = (p.getRutinas()).begin();
    while (it != (p.getRutinas()).end()) {
        if(*it == r) { //si es la rutina con la que hay que empezar
            rExist = true;
        }
        it++;
    }
    if(rExist){ //tenemos una rutina con la cual empezar, si no ni cargamos la calculadora
        rutinaActual = trie<vector<superInstruccion>>::ItDiccTrie(rutinasProg.nodoSignificado(""));
        //pasada 1: recorremos rutinas de p y las guardamos
        it = (p.getRutinas()).begin();
        while (it != (p.getRutinas()).end()) {
            //cout <<" cargando rutina: "<< *it<<endl;
            rutinasProg[*it] = vector<superInstruccion>();
            vecRutinas.push_back(*it);
            if(*it == r) { //si es la rutina con la que hay que empezar
                //cout <<"--iniciando rutinaactual"<<endl;
                rutinaActual = trie<vector<superInstruccion>>::ItDiccTrie(rutinasProg.nodoSignificado(r));
            }
            it++;
        }

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
                sp.itVarNombre = auxItVar;
                sp.itRut = auxItRut;
                vec.push_back(sp);
                rutinasProg[*it] = vec;
            }
            it++;
        }


        if(rutinaActual.claveActual() == "") {
            ejecutando = false;
        }
        if(rutinasProg.size() == 0){
            ejecutando = false;
        } else {
            if(rutinasProg[rutinaActual.claveActual()].size()==0){
                ejecutando=false;
            }
        }
    }else {
        ejecutando = false;
    }


}
bool Calculadora::getEjecutando() const{
    return ejecutando;
}
void Calculadora::ejecutarUnPaso(){

    if(ejecutando) {
        superInstruccion superIns = (*rutinaActual)[indiceInstruccionActual];

        Operacion op = superIns.op;
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
                //(*it).vent.registrar(make_tuple(instanteActual,valorAPushear));
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

    }

}

void Calculadora::asignarVariable(variable const x, valor const v){
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
const instante Calculadora::getInstanteActual() const{
    return instanteActual;
}

const rutina Calculadora::getRutinaActual() const{
    //return get<0>(rutinaActual);
    return rutinaActual.claveActual();
}

const int Calculadora::getIndiceInstruccionActual() const{
    return indiceInstruccionActual;
}

const int Calculadora::indiceInstante(int const i,int const s,instante const busc,variable const var){
   //cout << "busco el valor de " << var << " en el instante: "<<busc<<endl;
    //hacemos busqueda binaria para buscar el valor de la variable en el instante perteneciente a la capcidad de VENTANA
    Ventana<tuple<instante,valor> > ventBusqueda = variablePorNombre[make_tuple(var,W)].vent;
    int medio = ((s-i)/2)+i;
    int tamTotal = variablePorNombre[make_tuple(var,W)].vent.tam();
   //cout << "i: "<< i<< " tope: "<< s <<"medio: "<<medio<<endl;
    for (int j = i; j < s; ++j)
    {
       //cout<< "instante j= "<<j<<" vale: "<<get<0>(ventBusqueda[j])<<endl;
    }
   //cout << "valor de medio: "<<medio<<endl;
    if(get<0>(ventBusqueda[medio]) == busc) {
        return medio;
    }

    if(s-i == 1){
   //cout << "por aca no sigue"<<endl;
        if(get<0>(ventBusqueda[medio]) > busc) {
            return 0;
        }else if(get<0>(ventBusqueda[medio]) < busc){
            if(medio+1 < tamTotal){
                if(get<0>(ventBusqueda[medio+1]) > busc){
                    return medio;
                }else {
                    return medio+1;
                }
            }else {
                return medio;
            }
        }
    }

    if(get<0>(ventBusqueda[medio]) > busc) {//significa que si el instante existe esta en la mitad izquierda
        return indiceInstante(i,medio,busc,var);
    }
    if(get<0>(ventBusqueda[medio]) < busc) { // significa que si el instante existe esta en la mitad derecha
        return indiceInstante(medio,s,busc,var);
    }


}


void Calculadora::ver(variable var) {
   //cout << "ENTRO A VER ------------------------"<<endl;
    for (int i = 0; i < variablePorNombre[make_tuple(var,W)].vent.tam(); ++i)
    {
       //cout << "instantes guardados: "<< get<0>(variablePorNombre[make_tuple(var,W)].vent[i])<<endl;
    }
}

const valor Calculadora::valorEnInstante(variable const var, instante const inst) {
   //cout << "busco "<<var << " en inst:"<<inst<<endl;
    if(instanteActual == inst) return valorActualVariable(var);
    if(instanteActual >= inst && inst >=0) {
       if(variablePorNombre.count(var) > 0){ //el valor esta comprendido en la capacidad de ventana

            if(instanteActual-inst < W){

                //busco el indice de instante
                int indiceEnVentana = indiceInstante(0,variablePorNombre[make_tuple(var,W)].vent.tam(),inst,var);
                //indexamos
               //cout << "indice de vent: "<<indiceEnVentana<<endl;
               //cout << "inst en ese indice: "<< (get<0>(variablePorNombre[make_tuple(var,W)].vent[indiceEnVentana]))<<endl;
               //cout << "retorno valor en ese indice: "<< (get<1>(variablePorNombre[make_tuple(var,W)].vent[indiceEnVentana]))<<endl;
                return (get<1>(variablePorNombre[make_tuple(var,W)].vent[indiceEnVentana]));

            }else {//el valor pertenece al valor historico y no hay complejidad para buscarlo
                valorHistorico::const_iterator itend = (variablePorNombre[make_tuple(var,W)].valorHistorico).end();
                valorHistorico::const_iterator it = (variablePorNombre[make_tuple(var,W)].valorHistorico).begin();
                while(get<0>(*it) < inst && it !=itend ){
                    //cout << "comparando inst: "<<get<0>(*it) << " con: " <<inst <<endl;
                    it++;
                }
                ///if(it == itend) it--;
                //cout <<"devolviendo instante: " << get<0>(*it)<<" valor: "<<get<1>(*it)<<endl;
                //cout << "siguiente instante: "<< get<0>(*(++it))<<" valor: "<<get<1>(*it)<<endl;
                return get<1>(*it);
            }

        }else {
            variablePorNombre[make_tuple(var,W)].vent.registrar(make_tuple(instanteActual,0));
            variablePorNombre[make_tuple(var,W)].valorHistorico.push_back(make_tuple(instanteActual,0));
            return 0;
        }

    }
}

const valor Calculadora::valorActualVariable(variable const var){
    if(variablePorNombre.count(var) > 0) {
        int tam = variablePorNombre[make_tuple(var,W)].vent.tam();
        if(tam == 0) {
            //variablePorNombre[make_tuple(var,W)].vent.registrar(make_tuple(instanteActual,0));
            //variablePorNombre[make_tuple(var,W)].valorHistorico.push_back(make_tuple(instanteActual,0));
            return 0;
        }else{
            return get<1>((variablePorNombre[make_tuple(var,W)].vent)[tam-1]);
        }
    }else {
        variablePorNombre[make_tuple(var,W)].vent.registrar(make_tuple(instanteActual,0));
        variablePorNombre[make_tuple(var,W)].valorHistorico.push_back(make_tuple(instanteActual,0));
        return 0;
    }

}

const stack<valor>& Calculadora::getPila() const{
    return pila;
}

const valor Calculadora::primeroPila() const{
    //cout << "estoy consultando getPila: "<< pila.empty()<<endl;
    ////cout << "pila top: "<< pila.top()<<endl;
    return (pila.empty())? 0 : (pila.top());
}

const valor Calculadora::segundoPila() {

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

const bool Calculadora::escribiendoVariable(variable const &var) const{
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

const bool Calculadora::haySalto() const{
    Operacion  opActual = (*rutinaActual)[indiceInstruccionActual].op;
    return (opActual == oJump || opActual == oJumpz);
}
