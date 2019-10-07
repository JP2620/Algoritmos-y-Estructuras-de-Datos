/*
 * Lista2.h
 *
 *  Created on: Jun 5, 2019
 *      Author: Juan Pablo
 */

#ifndef LISTA2_H_
#define LISTA2_H_

#include <iostream>
#include "Nodo.h"
using namespace std;


class Lista2{
	protected:
	Nodo* czo2;

	public:
	void setCzo2(Nodo* n){czo2 = n;};
	Lista2(){Nodo* a = new Nodo(); czo2= a;};
	Lista2(Nodo* n){ czo2 = n;};
	void del2();
	void add2(tipolista d);
	void add2(Nodo* d);
	bool esvacia2();
	Nodo* cabeza2();
	Lista2* resto2();
	int size2();
	void printLista2();
	Nodo* ultimo2();
};

//METODOS

void Lista2::del2(){
	Nodo* aux;
	aux= czo2;
	czo2 = czo2->get_next2();
	delete aux;
}

void Lista2::add2(tipolista d){
    Nodo *nuevo=new Nodo(d);
    nuevo->set_next2(czo2);
    czo2=nuevo;
}

void Lista2::add2(Nodo* d){
	d->set_next2(czo2);
	czo2 = d;
}

bool Lista2::esvacia2(){
    return czo2->es_vacio2();
}

Nodo* Lista2::cabeza2(void){
	if(esvacia2()){
		cout<<"ERROR, CABEZA DE LISTA VACIA\n";
		return NULL;
	}
	return czo2;
}

Lista2* Lista2::resto2(){
	Lista2 *l = new Lista2(czo2->get_next2());
	return(l);
}

int Lista2::size2(){
	if(this->esvacia2()) return 0;
	return 1+this->resto2()->size2();
}

void Lista2::printLista2(){
	if(this->esvacia2()){
		cout<<"\n\n";
	}
	else{
		cout<<this->cabeza2()->get_dato()<<setw(28-this->cabeza2()->get_dato().length())
				<< this->cabeza2()->get_repeticiones()<<setw(10)<<this->cabeza2()<<"\n";
		this->resto2()->printLista2();
	}
}

Nodo* Lista2::ultimo2(){
	if(this->esvacia2()){
			cout<<"\n\n ERROR LISTA VACIA ULTIMO() \n\n";
			return NULL;
		}
		while(this->cabeza2()->get_next2()->get_next2() != NULL){
			return this->resto2()->ultimo2();
		}
		return this->cabeza2();
}























#endif /* LISTA2_H_ */
