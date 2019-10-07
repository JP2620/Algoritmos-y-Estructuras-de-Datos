/*
 * FuncionesUtiles.h
 *
 *  Created on: May 31, 2019
 *      Author: Juan Pablo
 */

#ifndef FUNCIONESUTILES_H_
#define FUNCIONESUTILES_H_

#include<iostream>
#include <fstream>
#include"Lista1.h"
#include"Lista2.h"
#include "Arbol.h"

using namespace std;
bool estaEnString(char caracter, string palabra){
	for(unsigned int i = 0; i<palabra.size();i++){
		if(caracter == palabra.at(i)) return true;
	}
	return false;
}

void insertarPalabra(Lista2* l2, Lista* l,Arbol* A, Nodo* nuevoNodo,int* cInsercion,void(Arbol::*insertar)(Nodo*)){

	//INSERCION EN LISTA
	tipolista data = nuevoNodo->get_dato();


	if(l->estaEnLista(data,cInsercion)){
		l->encontrarDato(data,cInsercion)->cabeza()->agregar_rep();
		return;
	}
	else{
		l2->add2(nuevoNodo);
		l->insertarEnLista(nuevoNodo, cInsercion);
		(A->*insertar)(nuevoNodo);
	}
}


void cargarPalabras(Lista2* l2, Lista* l,Arbol* A, int* cIns){
	cout<<"CREANDO LISTA\n";
	string linea;
	string palabra;
	void (Arbol::*insertar)(Nodo*) = NULL;
	bool opcion;
	//string alfabeto = "abcdefghijklmnñopqrstuvwxyzABCDEFGHIJKLMNÑOPQRSTUVWXYZÁÉÍÓÚáéíóú";


	//MENU
	cout<<"\n\nELIJA TIPO DE ARBOL: \n 1 : AVL\n 0 : BST ESTANDAR\n";
	cin>>opcion;
	(opcion)? insertar = &Arbol::insertarEnArbolAVL: insertar = &Arbol::insertarEnArbol;


	ifstream archivo("texto.txt");
	if(archivo.is_open()){
				while(getline(archivo,linea)){
					//cout<<linea<<"\n";
					if( palabra.length() > 0 ){
						insertarPalabra(l2, l, A, new Nodo(palabra),cIns,insertar);
						palabra = "";
					}
					for(unsigned int i=0; i<linea.length(); i++){
						char caracter = linea.at(i);
						if((caracter >= '0' && caracter <= '9') || (caracter >= 'a' && caracter <= 'z')
								|| (caracter >= 'A' && caracter <= 'Z') ){
							palabra.push_back(caracter);
						}
						else if( palabra.length() > 0 ){
							insertarPalabra(l2, l, A, new Nodo(palabra),cIns,insertar);
							palabra = "";
						}
					}
				}
				if( palabra.length() > 0 ){
					insertarPalabra(l2, l, A,new Nodo(palabra),cIns,insertar);
					palabra = "";
					cout<<"LISTA CREADA\n\n";
				}
				archivo.close();
	}	else cout<<"file is not open"<<endl;
	A->actualizarAlturas();
}

 // Encuentra el ultimo nodo de la lista*/
  Nodo *getUltimo(  Nodo *aux)
{
	while (aux != NULL && aux->get_next2() != NULL)
		aux = aux->get_next2();
	return aux;
}
/*hace la particion tomando el ultimo elemento de pivot
 * dejando todos los mayores a la derecha y menores a la izquierda
 * para hacer esto, deja a los menores donde estan (izquierda del pivot)
 * y a los mayores los pone a la derecha del ultimo
 */
  Nodo *partition(  Nodo *cabeza,   Nodo *final,
					  Nodo **newCabeza,   Nodo **newFinal, int* c)
{
	  Nodo *pivot = final;
	  Nodo *prev = NULL, *actual= cabeza, *ultimo = pivot;


	// cabeza y final pueden variar, estos cambios quedan en newHead y newFinal
	while (actual!= pivot)
	{
		*c = *c+1;
		if (actual->get_repeticiones() > pivot->get_repeticiones()){
			if ((*newCabeza) == NULL)
				(*newCabeza) = actual;

			prev = actual;
			actual = actual->get_next2();
		}
		else
		{
			/*movemos el actual al final (derecha del ultimo)
			 * y el actual de la siguiente iteracion es el siguiente
			 * al anterior actual
			 */
			if (prev)
				prev->set_next2(actual->get_next2());
			Nodo *tmp = actual->get_next2();
			actual->set_next2(NULL);
			ultimo->set_next2(actual);
			ultimo = actual;
			actual = tmp;
		}
		*c = *c+1;
	}


	// si el pivot es el mas chico (no cambie el null de *newCabeza),
	// entonces el pivot pasa a ser la cabeza
	if ((*newCabeza) == NULL)
		(*newCabeza) = pivot;

	// actualizo newFinal ya que seguro cambio el ultimo nodo
	(*newFinal) = ultimo;

	// retorna el pivot
	return pivot;
}
//here the sorting happens exclusive of the final node
  Nodo *quickSort(  Nodo *cabeza,   Nodo *final, int* k)
{
	// condicion de corte
	if (!cabeza || cabeza == final){
		*k = *k+1;
		return cabeza;
	}

	Nodo *newCabeza = NULL, *newFinal = NULL;

	// Parte la lista con los mayores que el pivot (final) a la derecha del mismo
	// y los menores a la izquierda
	  Nodo *pivot = partition(cabeza, final, &newCabeza, &newFinal, k);

	// si el pivot era el menor elemento, no hace falta seguir
	// terminamos con la parte izquierda
	if (newCabeza != pivot)
	{
		// sino pone el nodo anterior al pivot en null (como si cortando la lista
		// antes del pivot
		  Nodo *tmp = newCabeza;
		while (tmp->get_next2() != pivot){
			*k = *k+1;
			tmp = tmp->get_next2();
		}
		tmp->set_next2(NULL);
		*k = *k+2;
		// hace la llamada recursiva con la sublista izquierda al pivot
		newCabeza = quickSort(newCabeza, tmp,k);

		// rearma la lista poniendo el next ultimo de la sublista izquierda,
		// que quedo en null post recursion, en pivot
		tmp = getUltimo(newCabeza);
		tmp->set_next2(pivot);
	}

	// recursion en la parte derecha (no hay que rearmar nada porque de todos modos
	// el ultimo de la derecha tiene que apuntar a null
	pivot->set_next2(quickSort(pivot->get_next2(), newFinal,k));

	//retorna la cabeza de la lista/sublista
	return newCabeza;
}


int cantDigitos(int n){
	unsigned int res = 1;
	while (n>9){
		n = n/10;
		res++;
	}
	return res;
}



void copiarEnNext2(Lista* l1, Lista2* l2){
	l2->setCzo2(l1->cabeza());
	Nodo* aux = l1->cabeza();
	while(aux->get_next() != NULL){
		aux->set_next2(aux->get_next());
		aux = aux->get_next();
	}
}














#endif /* FUNCIONESUTILES_H_ */
