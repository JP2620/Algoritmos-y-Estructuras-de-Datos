/*
 * Cola.h
 *
 *  Created on: Jun 20, 2019
 *      Author: Juan Pablo
 */

#ifndef COLA_H_
#define COLA_H_

#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

class Nodo{
    private:
        int dato;
        Nodo *next;
    public:
        Nodo() {next=NULL; dato=0;};
        Nodo(int a) {dato=a; next=NULL;};
        void set_dato(int a) {dato=a; };
        void set_next(Nodo *n) {next=n; };
        int get_dato() {return dato; };
        Nodo *get_next() {return next; };
        bool es_vacio() {return next==NULL;}
};

class Lista{
    protected: Nodo *czo;
    public:
            Lista() {czo=new Nodo();};
            Lista(Nodo *n) {czo=n;};
            //~Lista(void);
            void add(int d);
            bool esvacia(void);
            Nodo* cabeza(void);
            Lista *resto(void);
            string toPrint(string p);
            int suma(int i);
            void impre(void);
            int suma2(void);
            int size();
            void borrar(void); //borra la cabeza
            void borrar_last();//borra el ultimo
            void concat(Lista *l1);
            Lista *copy(void);
            void tomar(int n);
            int last();
};

//-------- Metodos de Lista -------------------
int Lista::last()
{ if(!this->esvacia()){
    if(this->resto()->esvacia())return this->cabeza()->get_dato();
    return this->resto()->last();
  }return 0;
}
int Lista::size()
{
     if (this->esvacia()) return 0;
     return 1+this->resto()->size();
}
void Lista::impre(void)
{ Nodo *aux;
  aux=czo;
    while(aux->get_next()!=NULL){
         cout<<aux->get_dato()<<"\t";
         aux=aux->get_next();
    }
  cout<<"\n";
}
void Lista::add(int d)
{
     Nodo *nuevo=new Nodo(d);
     nuevo->set_next(czo);
     czo=nuevo;
}
bool Lista::esvacia(void)
{
    return czo->es_vacio();
}
Nodo* Lista::cabeza(void)
{
  if(this->esvacia()){
                cout<<" Error, Cabeza de lista vacia";
                return NULL;
  }
  return czo;
}
Lista *Lista::resto(void)
{
      Lista *l=new Lista(czo->get_next());
      return (l);
}
string Lista::toPrint(string p)
{
     if (this->esvacia()) {
        return p;
     } else {
       std::ostringstream stm;
       stm << this->cabeza()->get_dato()<<" - "<< this->resto()->toPrint(p) << endl;
      //cout<<endl<<" stm.str()= "<<stm.str()<<endl;
       return stm.str();
     }
}
int Lista::suma(int i)
{    //cout<<" i al entrar= "<<i<<endl;
     if (esvacia()) {return i;
     } else {

        //cout<<"this->cabeza()= "<<this->cabeza()<<endl;
        return resto()->suma(i+cabeza()->get_dato());
     }
}
int Lista::suma2(void){
     if (esvacia()) return 0;

     else return cabeza()->get_dato()+resto()->suma2();
}
void Lista::borrar(void)
{ //borra el nodo cabeza
  if(!this->esvacia()){
         Nodo *tmp=czo;
         czo=czo->get_next();
         delete tmp;
  }
}
void Lista::borrar_last()
{ // borra el ultimo nodo
   if(!this->esvacia()){
      if((czo->get_next())->get_next()==NULL){
         delete czo->get_next();
         czo->set_next(NULL);
      }
      else this->resto()->borrar_last();
   }
}
void Lista::concat(Lista *l1)
{// le transfiere los datos de l1 a this
   if (!(l1->esvacia())){
      this->concat(l1->resto());
      this->add(l1->cabeza()->get_dato());
   }
}


class Cola:public Lista{
  public:
      Cola(void){Lista();};
      ~Cola(void);
      int tope();
      bool colavacia(){return this->esvacia();};
      void encolar(int a) ;
      void desencolar();
      Nodo* ultimo();
      string imprimir(string s);
      int extraerMin(int*);
};
//-------- Metodos de Cola --------------------
int Cola::tope(void)
{  return this->last();
}
void Cola::encolar(int a)
{  this->add(a);
}
void Cola::desencolar(void)
{  this->borrar_last();
}
Nodo* Cola::ultimo(void)
{   return this->cabeza();
}
string Cola::imprimir(string s)
{  return this->toPrint(s);
}

int Cola::extraerMin(int* costo){

	int res = this->ultimo()->get_dato();
	Nodo* aux = this->ultimo();
	while(aux->get_next() != NULL){
		if(*(costo+aux->get_dato()) < *(costo+res)){
			res = aux->get_dato();
		}
		aux=aux->get_next();
	}


	if(res == this->ultimo()->get_dato()){
		czo = this->ultimo()->get_next();
		return res;
	}
	else{
		Nodo* actual = this->ultimo();
		Nodo* prev;
		while(actual != NULL){
			if(actual->get_dato() == res){
				prev->set_next(actual->get_next());
				return res;
			}
			prev = actual;
			actual = actual->get_next();
		}
	}
	cout<<"\nRES\n";
	cout<<this->ultimo()->get_dato()<<endl;
	return res;





}

























#endif /* COLA_H_ */
