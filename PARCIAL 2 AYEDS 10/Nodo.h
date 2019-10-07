/*
 * Nodo.h
 *
 *  Created on: Jun 4, 2019
 *      Author: Juan Pablo
 */

#ifndef NODO_H_
#define NODO_H_
#include<iostream>
using namespace std;
typedef string tipolista;

bool compararAlfabet(string s1, string s2){

	unsigned int l = min(s1.length(),s2.length());
	for(unsigned int i = 0; i<l; i++){
		if(s1.at(i) > s2.at(i)) return true;
		else if(s1.at(i) < s2.at(i)) return false;
	}
	if(s1.length() == l) return false;
	else return true;
}


class Nodo{
    private:
        tipolista dato;
        int repeticiones;
        int height;
        Nodo *next;
        Nodo *hd;
        Nodo *hi;
        Nodo *next2;
    public:
        Nodo() {dato = "";next=NULL;next2=NULL; repeticiones = 0;hd = NULL ;hi = NULL; height = 0;};
        Nodo(tipolista a) {dato=a; repeticiones=1; next=NULL;next2=NULL; hd= new Nodo(); hi= new Nodo();height = 1;};
        void set_altura(int h){height = h;};
        void set_dato(tipolista a) {dato=a; };
        void set_next(Nodo *n) {next=n; };
        void set_repeticiones(int k) {repeticiones = k; };
        void set_hi(Nodo* k){hi = k;};
        void set_hd(Nodo* k){hd = k;};
        void set_next2(Nodo *n){next2 = n;};
        void agregar_rep(){ repeticiones++;};
        tipolista get_dato() {return dato; };
        int get_repeticiones(){return repeticiones; };
        Nodo *get_next() {return next; };
        Nodo *get_hi() {return hi; };
        Nodo *get_hd() {return hd; };
        Nodo *get_next2(){return next2;};
        int get_altura(){return height;};
        bool es_vacio() {return next==NULL;}
        bool es_vacio2(){return next2==NULL;}



        bool esANulo(){return this->get_dato()=="";};
        bool esHoja(){return (hi->esANulo() && hd->esANulo())? true:false;}
        int altura();
        void printArbol();
        int actualAlturas();
        bool es_balanceado(Nodo* desbalance = new Nodo());
        Nodo* rotacionDer();
        Nodo* rotacionIzq();
        Nodo* encontrarPalabra(tipolista cadena);
};

bool Nodo::es_balanceado(Nodo* desbalance){
	if(this->esANulo()) return true;
	else{
		if(abs(this->get_hi()->get_altura() - this->get_hd()->get_altura()) < 2){
			return ((this->get_hi()->es_balanceado(desbalance)) && (this->get_hd()->es_balanceado(desbalance)));
		}
		else{
			*desbalance = *this;
			return false;
		}
	}
}



Nodo* Nodo::encontrarPalabra(tipolista cadena){
	if(compararAlfabet(cadena,this->get_dato())){
		return this->get_hd()->encontrarPalabra(cadena);
	}
	else if(! compararAlfabet(cadena,this->get_dato())){
		if(cadena == this->get_dato()) return this;
		return this->get_hi()->encontrarPalabra(cadena);
	}
	else return this;
}

void Nodo::printArbol(){
	if(!this->get_hi()->esANulo()) this->get_hi()->printArbol();
	cout<<this->get_dato()<<setw(28-this->get_dato().length())<<
			this<<endl;
	if(!this->get_hd()->esANulo()) this->get_hd()->printArbol();
}
int Nodo::altura(){
	if(this->esHoja()) {
		return 1;
	}
	else if(this->hi->esANulo() && !this->hd->esANulo()){
		return 1 + this->hd->altura();
	}
	else if(this->hd->esANulo() && !this->hi->esANulo()){
		return 1 + this->hi->altura();
	}
	else return 1 + max(this->hi->altura(),this->hd->altura());
}
int Nodo::actualAlturas(){
	int a,b;
	if(this->esHoja()){
		this->set_altura(1);
		return 1;
	}
	else if(!this->hd->esANulo() && this->hi->esANulo()){
		a = this->hd->actualAlturas()+1;
		this->set_altura(a);
		return a;
	}
	else if(!this->hi->esANulo() && this->hd->esANulo()){
		b = this->hi->actualAlturas()+1;
		this->set_altura(b);
		return b;
	}
	else{
		a = this->hd->actualAlturas()+1;
		b = this->hi->actualAlturas()+1;
		this->set_altura(max(a,b));
		return max(a,b);
	}
}
Nodo* Nodo::rotacionDer(){


	Nodo* k1 = this;
	Nodo* k2 = this->get_hi();
	Nodo* y = this->get_hi()->get_hd();

	k2->set_hd(k1);
	k1->set_hi(y);
	return k2;
}
Nodo* Nodo::rotacionIzq(){

	Nodo* k1 = this;
	Nodo* k2 = this->get_hd();
	Nodo* y = this->get_hd()->get_hi();

	k2->set_hi(k1);
	k1->set_hd(y);
	return k2;
}





















#endif /* NODO_H_ */
