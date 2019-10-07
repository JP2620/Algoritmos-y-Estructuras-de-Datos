/*
 * Lista1.h
 *
 *  Created on: Jun 4, 2019
 *      Author: Juan Pablo
 */

#ifndef LISTA1_H_
#define LISTA1_H_

#include <iostream>
#include "Nodo.h"
using namespace std;


class Lista{
	protected:
	Nodo*czo;

	public:
	Lista() {Nodo* a = new Nodo(); czo =a;};
	Lista(Nodo* n){czo = n;};
	void del();
	void add(tipolista d);
	void add(Nodo* d);
	bool esvacia();
	Nodo* cabeza();
	Lista* resto();
	int size();
	Lista* encontrarDato(string p, int*c);
	void printLista();
	void concat(Lista* l1);
	Nodo* ultimo();
	bool estaEnLista(tipolista s, int*c);
	void insertarEnLista(Nodo* n, int* c);
    void insertarPalabra(Nodo* s,int* c);
    void copiarEnNext2(Nodo** node);

};


//METODOS

void Lista::del(){
	Nodo* aux;
	aux= czo;
	czo = czo->get_next();
	delete aux;
}

void Lista::add(tipolista d){
    Nodo *nuevo=new Nodo(d);
    nuevo->set_next(czo);
    czo=nuevo;
}

void Lista::add(Nodo* d){
	d->set_next(czo);
	czo = d;
}

bool Lista::esvacia(){
    return czo->es_vacio();
}

Nodo* Lista::cabeza(void){
	if(esvacia()){
		//cout<<"ERROR, CABEZA DE LISTA VACIA\n";
		return NULL;
	}
	return czo;
}

Lista* Lista::resto(){
	Lista *l = new Lista(czo->get_next());
	return(l);
}

int Lista::size(){
	if(this->esvacia()) return 0;
	return 1+this->resto()->size();
}

void Lista::printLista(){
	if(this->esvacia()){
		cout<<"\n\n";
	}
	else{
		cout<<this->cabeza()->get_dato()<<setw(28-this->cabeza()->get_dato().length())
				<<this->cabeza()<<setw(10)<< this->cabeza()->get_repeticiones()<<"\n";
		this->resto()->printLista();
	}
}

bool Lista::estaEnLista(tipolista cadena, int*c){
	Nodo* current = this->cabeza();
	while(current != NULL){
		//cout<<"\nBUSCANDO: "<<cadena<<endl;
		if(current->get_dato() == cadena){
			*c = *c+1;
			return true;
		}
		current = current->get_next();
	}
	return false;
}


Nodo* Lista::ultimo(){
	if(this->esvacia()){
			cout<<"\n\n ERROR LISTA VACIA ULTIMO() \n\n";
			return NULL;
		}
		while(this->cabeza()->get_next()->get_next() != NULL){
			return this->resto()->ultimo();
		}
		return this->cabeza();
}

Lista* Lista::encontrarDato(tipolista s, int* c){
	if(this->esvacia()){
		//cout<<"NO ESTA \n"<<endl;
		return NULL;
	}
	else if(this->cabeza()->get_dato() == s){
		*c = *c+1;
		//cout<<"LO ENCONTRE"<<endl;
		//cout<<s<<endl;
		return this;
	}
	return this->resto()->encontrarDato(s, c);
}


void Lista::insertarEnLista(Nodo* nuevoNodo, int* c){

	if(this->esvacia()){
		this->add(nuevoNodo);
		return;
	}

	Nodo* aux1 = this->cabeza();
	Nodo* aux2;

	while((aux1 != NULL) && (compararAlfabet(nuevoNodo->get_dato(),aux1->get_dato()))){
		*c = *c + 1;
		aux2 = aux1;
		aux1 = aux1->get_next();
	}
	*c = *c + 1;
	if(aux1 == NULL){
		// si llega a NULL es porque hay q agregar s al final
		Lista* listaAux = new Lista();
		listaAux->add(nuevoNodo);
		this->concat(listaAux);
		*c = *c + 1;
		return;
	}
	else if(this->cabeza() == aux1){
		//*c = *c + 2;
		this->czo = nuevoNodo;
	}
	else{
		//*c = *c + 2;
		aux2 ->set_next(nuevoNodo);
	}
	nuevoNodo ->set_next(aux1);
}

void Lista::concat(Lista *l1)
{// le transfiere los datos de l1 a this
	this->ultimo()->set_next(l1->czo);
}



















#endif /* LISTA1_H_ */
