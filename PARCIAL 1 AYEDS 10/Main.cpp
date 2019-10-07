/*
 * Main.cpp
 *
 *  Created on: May 13, 2019
 *      Author: Juan Pablo
 */


//#include <cstdlib>
#include <iostream>
#include <fstream>
#include "ListaDeInstr.h"
#include "Instruccion.h"

using namespace std;


int main(){

		ListaDeInstr* instrList = new ListaDeInstr();
		ListaDeVar* varList = new ListaDeVar();
		string linea;
		ifstream archivo("codigo.txt");


		//CARGA DE INSTRUCCIONES
		int i = 1;
		if(archivo.is_open()){

			while(getline(archivo,linea)){
				instrList->addInstr(new Instruccion(linea,varList, new int(i)));
				i++;
			}
			archivo.close();
		}
		else cout<<"file is not open"<<endl;


		//EJECUCION INSTRUCCIONES
		cout<<"\n\n";
		for(int j=1; j<=instrList->size() ;j++){
			instrList->encontrarInstr(j)->cabeza().ejecutarInstruccion(&j);
		}

		return 1;
}


/*
INT k
INT a
k = 5*2-3
a = (k+5)-2
SHOW a*k
a = a-k
SHOW a
JUMP 5

INT a
INT b
a = 4
b = 1
IF (a<1) THEN JUMP 9
b = b*a
a = a-1
JUMP 5
SHOW b


INT a
INT b
a = 3
b = 9
IF (a*b > 5*2) THEN IF (9+9+9 == a*b) THEN SHOW a*b

INT a
INT b
a = 3
b = 9
SHOW a*b
IF (a*b > 5*2) THEN IF (b == 3*a) THEN SHOW a*b

INT a
INT b
INT c
INT i
a = 1
b = 1
i = 1
IF (i==9) THEN JUMP 14
c = a
a = a+b
b = c
i = i+1
JUMP 8
SHOW a
*/


