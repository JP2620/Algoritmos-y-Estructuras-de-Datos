/*
 * Main.cpp
 *
 *  Created on: May 31, 2019
 *      Author: Juan Pablo
 */

#include <iostream>
#include<iomanip>
#include "Lista1.h"
#include "Lista2.h"
#include "Arbol.h"
#include "FuncionesUtiles.h"
using namespace std;



int main(){

	Lista* l1 = new Lista();
	Lista2* l2 = new Lista2();
	Arbol* A1 = new Arbol();
	int* cont_Insercion = new int(0);
	int* cont_QS = new int(0);






	//INSERCION EN LISTA Y ARBOL
	cargarPalabras(l2, l1,A1,cont_Insercion);
	cout<<endl<<endl;
	cout<<"ARBOL:  \n\n\n";
	A1->printArbol();
	cout<<"LISTA 1: \n\n\n";
	l1->printLista();


	//cout<<A1->getRaiz()->get_dato()<<endl<<endl;
	//copiarEnNext2(l1,l2);
	//l2->printLista2();





	//ESCRIBO LA LISTA EN ORDEN ALFABETICO EN EL ARCHIVO
	cout<<"ESCRIBIENDO EN ARCHIVO LISTA\n";
	ofstream file_;
	file_.open("resultados.txt");
	Nodo* aux1 = l1->cabeza();
	file_ << "LISTA EN ORDEN ALFABETICO \n\n";
	while(aux1->get_next() != NULL){
		file_ << aux1->get_dato()<<setw(20-aux1->get_dato().length());
		file_<<"  "<<aux1->get_repeticiones()<<"\n";
		aux1 = aux1->get_next();
	}
	cout<<"\nTERMINE DE ESCRIBIR EN ARCHIVO";



	//QUICK SORT CON EL CUARTO PUNTERO
	cout<<"\nEMPIEZO QUICKSORT\n";

	/* Con numeros uniformemente distribuidos da O(n log n)
	Nodo* test = l2->cabeza2();
	while(test != NULL){
		test->set_repeticiones(rand()%10000);
		test = test->get_next2();
	}*/

	Nodo* cabeza = l2->cabeza2();
	l2->setCzo2(quickSort(cabeza, getUltimo(cabeza), cont_QS));
	cout<<"\n TERMINE QUICKSORT\n\nLISTA 2 ORDENADA :\n\n";
	l2->printLista2();








	//ESCRIBO LA LISTA EN ORDEN DESCENDENTE SEGUN REPETICIONES
	cout<<"ESCRIBIENDO LISTA EN ARCHIVO\n";
	aux1 = l2->cabeza2();
	file_ << "\n\nLISTA EN ORDEN DESCENDENTE SEGUN REPETICIONES \n\n";
	while(aux1 != NULL && aux1->get_next2() != NULL){
		file_<< aux1->get_repeticiones() <<setw(10-cantDigitos((aux1->get_repeticiones())));
		file_<<"  "<< aux1->get_dato()<<"\n";
		aux1 = aux1->get_next2();
	}
	file_.close();

	cout<<"\nTERMINE DE ESCRIBIR EN ARCHIVO\n\n";




	//FINAL


	cout<<"\nTAMAÑO DE LAS ESTRUCTURAS:   "<<l1->size()<<"\n\n\n";
	Nodo* raiz = A1->getRaiz();
	cout<<"COMPARACIONES PARA LA INSERCION: \n"<<*cont_Insercion<<"\n";
	cout<<"COMPARACIONES PARA EL QUICKSORT: \n"<<*cont_QS<<"\n";
	cout<<"\nALTURA:  \n\n\n\t\t\t"<<A1->altura()<<"\n\t"<<A1->getRaiz()->get_hi()->get_altura()<<"\t\t\t\t"<<A1->getRaiz()->get_hd()->get_altura()<<"\n";
	cout<<raiz->get_hi()->get_hi()->get_altura()<<"\t\t"<<raiz->get_hi()->get_hd()->get_altura()
			<<"\t\t"<<raiz->get_hd()->get_hi()->get_altura()<<"\t\t"<<raiz->get_hd()->get_hd()->get_altura()<<"\n";
}


