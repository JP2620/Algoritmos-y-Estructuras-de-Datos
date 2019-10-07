/*
 * Variable.h
 *
 *  Created on: May 12, 2019
 *      Author: Juan Pablo
 */

#ifndef VARIABLE_H_
#define VARIABLE_H_

#include <iostream>
using namespace std;

class Variable
{
	protected:
		int valor;
        string nombre;


	public:
        Variable(){
        	valor = 0;
        	nombre = "";}
        Variable(string a){
        	valor = 0;
        	nombre = a;}

		Variable(int d, string s){
			valor = d;
			nombre=s;}
		int getValor(){return valor;}
        string get_nombre(){return nombre;}
        void setValor(int k){valor=k;}
        void setNombre(string l){nombre=l;}
        void printVar(){
        	cout<< "nombre de la var: " << nombre <<endl;
        	cout<< "valor de la var: "<<valor<<"\n\n";

        }
};



#endif /* VARIABLE_H_ */
