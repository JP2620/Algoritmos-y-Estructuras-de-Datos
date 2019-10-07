/*
 * ListaDeInstr.h
 *
 *  Created on: May 12, 2019
 *      Author: Juan Pablo
 */

#ifndef LISTADEINSTR_H_
#define LISTADEINSTR_H_

#include <iostream>
#include "Instruccion.h"
using namespace std;


typedef Instruccion tipolista;

class Nodo{
    protected:
        tipolista dato;
        Nodo *next;

    public:
        Nodo() {next=NULL;};
        Nodo(tipolista a) {dato=a; next=NULL;};
        void set_instr(tipolista a) {dato=a; };
        void set_instr(Nodo *n) {next=n; };
        tipolista get_instr() {return dato; };
        Nodo *get_nextInst() {return next; };
        bool es_vacio() {return next==NULL;}
        };

class ListaDeInstr{
    protected: Nodo *czo;
    public:
    		ListaDeInstr() {czo=new Nodo();};
    		ListaDeInstr(Nodo *n) {czo=n;};
            //~Lista(void);
            //tipolista Lista::ultimo(tipolista x);
            void del(void);
            void addInstr(tipolista* d);
            bool esvacia(void);
            tipolista cabeza(void);
            ListaDeInstr *resto(void);
            void toPrint();
            int size();
            ListaDeInstr* encontrarInstr(int n);

};

void ListaDeInstr::del(void)
{    Nodo *aux;
     aux=czo;
     czo=czo->get_nextInst();
     delete aux;
}
void ListaDeInstr::addInstr(tipolista* d)
{
     Nodo *nuevo=new Nodo(*d);
     nuevo->set_instr(czo);
     czo=nuevo;
}
bool ListaDeInstr::esvacia(void)
{
    return czo->es_vacio();
}

tipolista ListaDeInstr::cabeza(void)
{
  if(esvacia()){
                cout<<" Error, Cabeza de lista vacia";
  }
  return czo->get_instr();
}

ListaDeInstr *ListaDeInstr::resto(void)
{
	  ListaDeInstr *l=new ListaDeInstr(czo->get_nextInst());
      return (l);
}

void ListaDeInstr::toPrint()
{
     if (this->esvacia()) {
        return ;
     } else {
       string asd = this->cabeza().getSentencia();
       cout<< asd<<endl;
       this->resto()->toPrint();
       return;
     }
}

int ListaDeInstr::size(){

	 if (this->esvacia()) return 0;
    return 1+this->resto()->size();
}
ListaDeInstr *ListaDeInstr::encontrarInstr(int n){
	if(this->esvacia()){
		cout<<"ERROR VARIABLE NO GUARDADA"<<endl;
		return NULL;
	}
	else if(*(this->cabeza().getId()) == n){
		return this;
	}

	return this->resto()->encontrarInstr(n);
}



#endif /* LISTADEINSTR_H_ */
