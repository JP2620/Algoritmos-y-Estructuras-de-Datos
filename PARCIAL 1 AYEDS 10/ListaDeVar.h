/*
 * ListaDeVar.h
 *
 *  Created on: May 12, 2019
 *      Author: Juan Pablo
 */

#ifndef LISTADEVAR_H_
#define LISTADEVAR_H_
#include "Variable.h"
#include <iostream>

using namespace std;

typedef Variable tipolista2;

class NodoVar{
    protected:
        tipolista2 dato;
        NodoVar *next;
    public:
        NodoVar() {next=NULL;};
        NodoVar(tipolista2 a) {dato=a; next=NULL;};
        void set_dato(tipolista2 a) {dato=a; };
        void set_next(NodoVar *n) {next=n; };
        tipolista2 get_dato() {return dato; };
        NodoVar *get_next() {return next; };
        bool es_vacio() {return next==NULL;}
};

class ListaDeVar{
    protected: NodoVar *czo;
    public:
    		ListaDeVar() {czo=new NodoVar();};
    		ListaDeVar(NodoVar *n) {czo=n;};
            //~Lista(void);
            //tipolista Lista::ultimo(tipolista x);
            void del(void);
            void add(tipolista2 d);
            bool esvacia(void);
            tipolista2 cabeza(void);
            NodoVar* cabezaPuntero();
            ListaDeVar *resto(void);
            void toPrint();
            bool estaEnLista(string key);
            ListaDeVar *encontrarVar(string key);

};


class PiladeVar:public ListaDeVar{
      public:
             PiladeVar(){ListaDeVar();};
             void apilar(tipolista2 x){add(x);};
             tipolista2 tope(void){return cabeza();};
             void desapilar(void){del();};
             bool pilavacia(){return esvacia();};

};


void ListaDeVar::del(void)
{    NodoVar *aux;
     aux=czo;
     czo=czo->get_next();
     delete aux;
}
void ListaDeVar::add(tipolista2 d)
{

    NodoVar *nuevo= new NodoVar(d);
     nuevo->set_next(czo);
     czo=nuevo;
}
bool ListaDeVar::esvacia(void)
{
    return czo->es_vacio();
}

tipolista2 ListaDeVar::cabeza(void)
{
  if(esvacia()){
                cout<<" Error, Cabeza de lista vacia";
  }
  return czo->get_dato();
}

NodoVar* ListaDeVar::cabezaPuntero(void)
{
	if(esvacia()){
		return NULL;
	}
	return czo;
}

ListaDeVar *ListaDeVar::resto(void)
{
	ListaDeVar *l=new ListaDeVar(czo->get_next());
      return (l);
}

void ListaDeVar::toPrint(void)
{
     if (this->esvacia()) {
        return ;
     } else {
       this->cabeza().printVar();
       this->resto()->toPrint();
     }
}

bool ListaDeVar::estaEnLista(string cadena){
	if(this->esvacia()){
		return false;
	}

	else if((this->cabeza().get_nombre()) == cadena){
		return true;
	}

	return this->resto()->estaEnLista(cadena);

}

ListaDeVar *ListaDeVar::encontrarVar(string key){
	if(this->esvacia()){
		cout<<"ERROR VARIABLE NO GUARDADA"<<endl;
		return NULL;
	}
	else if(this->cabeza().get_nombre() == key){
		return this;
	}

	return this->resto()->encontrarVar(key);
}



#endif /* LISTADEVAR_H_ */
