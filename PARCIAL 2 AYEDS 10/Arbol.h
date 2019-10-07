/*
 * Arbol.h
 *
 *  Created on: Jun 4, 2019
 *      Author: Juan Pablo
 */

#ifndef ARBOL_H_
#define ARBOL_H_

#include <iostream>
#include "Nodo.h"
using namespace std;

class Arbol{
	private:
	Nodo* raiz;

	public:
	Arbol(){raiz = NULL;};
	Arbol(Nodo* n){raiz = n;}
	Nodo* getRaiz(){return raiz;};
	void setRaiz(Nodo* r){raiz = r;};
	void insertarEnArbol(Nodo* n);
	void insertarEnArbolAVL(Nodo* n);
	Nodo* encontrarenArbol(tipolista n);
	Nodo* getPadre(Nodo* raizArbol, Nodo* hijo);
	int altura();
	void printArbol();
	void actualizarAlturas();
	bool esBalanceado(Nodo* desbalance = new Nodo());
};

Nodo* Arbol::getPadre(Nodo* quizaPadre, Nodo* hijo){
	if(quizaPadre->esHoja() || raiz == hijo) return NULL;
	else if(quizaPadre->get_hi() == hijo || quizaPadre->get_hd() == hijo) return quizaPadre;
	else if(compararAlfabet(quizaPadre->get_dato(), hijo->get_dato())){
		return this->getPadre(quizaPadre->get_hi(),hijo);
	}
	else{
		return this->getPadre(quizaPadre->get_hd(), hijo);
	}
}
void Arbol::printArbol(){
	this->getRaiz()->printArbol();
	cout<<"\n";
}


void Arbol::actualizarAlturas(){
	this->getRaiz()->actualAlturas();
}

Nodo* Arbol::encontrarenArbol(tipolista palabra){
	return this->getRaiz()->encontrarPalabra(palabra);
}
int Arbol::altura(){
	return this->getRaiz()->altura();
}

bool Arbol::esBalanceado(Nodo* n){
	return this->getRaiz()->es_balanceado(n);
}

void Arbol::insertarEnArbol(Nodo* nuevoNodo){
	if(this->getRaiz()==NULL){
		this->setRaiz(nuevoNodo);
		return;
	}
	Nodo* aux = this->getRaiz();
	while(true){
			//if(nuevoNodo->get_dato() == aux->get_dato()){ return; };
			if(compararAlfabet(nuevoNodo->get_dato(),aux->get_dato())){
				if(aux->get_hd()->esANulo()){
					aux->set_hd(nuevoNodo);
					break;
				}
				else{
					aux = aux->get_hd();
				}
			}
			else{
				if(aux->get_hi()->esANulo()){
					aux->set_hi(nuevoNodo);
					break;
				}
				else{
					aux = aux->get_hi();
				}
			}
	}
}

void Arbol::insertarEnArbolAVL(Nodo* nuevoNodo){

	/* aux es el nodo cuyos hijos tienen alturas que difieren en mas de uno
	 * subRoot es el nodo sub raiz de aux
	 * newRaiz es el resultado de la rotacion que es el nodo que tiene que reemplazar a aux en el arbol
	 */
	this->insertarEnArbol(nuevoNodo); this->actualizarAlturas();
	Nodo* desbalance = new Nodo();
	if(! this->esBalanceado(desbalance)){

		Nodo* padre;Nodo* newHijo; bool esHizq;
		desbalance = this->encontrarenArbol(desbalance->get_dato());

		//se guarda el padre de desbalance en Subroot, padre es NULL si desbalance es la raiz(no tiene padre)
		padre = this->getPadre(this->getRaiz(), desbalance);
		//this->getRaiz()->encontrarRaizDesbalance(this->getRaiz(), pSubRoot);

		//me fijo si desbalance es hijo izquierdo o no de padre (siempre y cuando desbalance tenga padre(raiz))
		if(padre != NULL) (desbalance->get_dato() == padre->get_hi()->get_dato())?esHizq = true:esHizq = false;

		//Desbalanceos en rama izquierda
		if((desbalance->get_hi()->get_altura() > (desbalance->get_hd()->get_altura()+1)))
		{
			//CASO 1: Desbalance en la rama izquierda de la rama izquierda
			if(desbalance->get_hi()->get_hi()->get_altura() > desbalance->get_hd()->get_altura()){
				newHijo = desbalance->rotacionDer();
			}
			//CASO 3: Desbalance en la rama derecha de la rama izquierda
			else{
				//same con rotacion extra
				desbalance->set_hi(desbalance->get_hi()->rotacionIzq());
				newHijo = desbalance->rotacionDer();
			}
		}

		//Desbalanceos en rama derecha
		else //if((aux->get_hd()->get_altura()) > (aux->get_hi()->get_altura() +1))
		{
			//CASO 2: Desbalance en la rama derecha de la rama derecha
			if(desbalance->get_hd()->get_hd()->get_altura() > desbalance->get_hi()->get_altura()){
				newHijo = desbalance->rotacionIzq();
			}
			//CASO 4: Desbalance en la rama izquierda de la rama derecha
			else{
				desbalance->set_hd(desbalance->get_hd()->rotacionDer());
				newHijo = desbalance->rotacionIzq();
			}
		}
		/* si padre es NULL, voy a tener una nueva raiz, sino reemplazo el hijo
		 * de padre que corresponda por el resultado de la rotacion.*/
		(padre == NULL)? this->setRaiz(newHijo) : (esHizq)? padre->set_hi(newHijo):padre->set_hd(newHijo);
		this->actualizarAlturas(); //importante
		// padre = new Nodo();  desbalance = new Nodo(); si pongo while en vez de if
	}
}

















#endif /* ARBOL_H_ */
