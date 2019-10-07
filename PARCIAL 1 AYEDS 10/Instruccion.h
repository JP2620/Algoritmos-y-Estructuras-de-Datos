/*
 * Instruccion.h
 *
 *  Created on: May 12, 2019
 *      Author: Juan Pablo
 */

#ifndef INSTRUCCION_H_
#define INSTRUCCION_H_

#include <iostream>
#include "ListaDeVar.h"
#include "Calculadora.h"
using namespace std;
class Instruccion
{
	public:
		ListaDeVar* listaVar;
		virtual ~Instruccion();
		void setId(int* k){id =k;}
		int* getId(){return id;}
		void setSentencia(string s) {sentencia = s;}
		string getSentencia(){return sentencia;}
		void ejecutarInstruccion(int* p);

		Instruccion(string cadena, ListaDeVar* lv, int* k){
			id = k;
			this->setSentencia(cadena);
			listaVar = lv;
		}
		Instruccion(string s, ListaDeVar* lv) {
			sentencia = s;
			listaVar = lv;
			id = NULL;
		}
		Instruccion(){
			sentencia = "";
			listaVar = NULL;
			id = NULL;
		}


	private:
		string sentencia;
		int* id;


	};

//Verificar que el nombre de la variable este entre a y z.
class DeclaracionVar : public Instruccion{
	public:
		DeclaracionVar(string declaracion, ListaDeVar* lv, int* u){
			setId(u);
			setSentencia(declaracion); listaVar = lv ;
		}

		void ejecutarDeclaracion(){
			cout<<"-----------------------------------------------"<<endl<<"EJECUTANDO DECLARACION DE VARIABLE"<<endl;
			cout<<this->getSentencia()<<"   ";
			char letra = getSentencia().at(4);
			if(letra >= 'a' && letra <= 'z') cout<<"CUMPLE"<<endl;
			cout<<"I VALE: "<<*getId()<<"  I está en: "<<getId()<<endl;
			if(listaVar->estaEnLista(string(1,getSentencia().at(4)))){
				cout<<"RE-DECLARACION"<<endl;
				return;
			}
			else{
				if(letra >= 'a' && letra <= 'z'){
					listaVar->add(Variable(string(1,getSentencia().at(4))));
				}
				else cout<<"NO CUMPLE"<<endl;

				return;
			}
		}
};

class AsignacionVar : public Instruccion{
	public:
		AsignacionVar(string declaracion, ListaDeVar* l, int* p){
			setId(p);
			setSentencia(declaracion);
			listaVar = l;
		}
		string leerSentencia(){
			string res = "";
			string s = this->getSentencia();
			bool concatenar = false;
			for(unsigned int i=0; i< s.size() ; i++){
				if(s.at(i) == '=' && !concatenar){
					concatenar = true;
				}
				else if(concatenar && s.at(i) != ' '){
					res.push_back(s.at(i));
				}
			};
			return res;
		}

		void ejecutarAsignacion(){
			cout<<"------------------------------------------------------"<<endl<<"EJECUTANDO ASIGNACION"<<endl;
			cout<<this->getSentencia()<<"   ";
			cout<<"I VALE: "<<*getId()<<"  I está en: "<<getId()<<endl;
			string value = string(1,this->getSentencia().at(0));
			Variable* v = new Variable();
			string expresion = this->leerSentencia();
			Calculadora* calc = new Calculadora();
			if(listaVar->estaEnLista(value)){
				ListaDeVar* aux = listaVar->encontrarVar(value);
				/*
				aux->toPrint();
				aux->cabezaPuntero()->setNombre(value);
				aux->cabezaPuntero()->setValor(stoi(calc->calcular(expresion, listaVar)));*/
/*
				v->setNombre(value);
				v->setValor(stoi(calc->calcular(expresion, listaVar)));
				aux->del(); aux->add(*v);
				aux->toPrint();*/
				v->setNombre(value);
				v->setValor(calc->calcular(expresion, listaVar));
				aux->cabezaPuntero()->set_dato(*v);
				return;
			}
			else{
				cout<<"VARIABLE NO DECLARADA"<<endl;
				return;
			}
		}

};

class Condicional : public Instruccion{
	public:
		Condicional(string declaracion, ListaDeVar* l, int* o){
			setSentencia(declaracion);
			listaVar = l;
			setId(o);
		}

		string leerCondicion(){

			string res = "";
			string s = this->getSentencia();
			bool concatenar = false;
			for(unsigned int i=0; i<s.size(); i++){
				if(s.at(i) == 'T'){
					break;
				}
				else if(s.at(i) == 'F' && !concatenar){
					concatenar = true;
					i+=2;
				}
				else if(concatenar && s.at(i) != ' '){
					res.push_back(s.at(i));
				}
			}
			cout<<"---------------------------"<<endl<<"CONDICION: "<<res.substr(0, res.size()-1)<<endl;
			return res.substr(0, res.size()-1);
		}

		string leerInstruccion(){
			string instr = "";
			string s = this->getSentencia();
			instr = s.substr(s.find("THEN ")+5);
//			cout<<instr;
			return instr;
		}

		void ejecutarCondicional(){
			cout<<"-------------------------------------"<<endl<<"EJECUTANDO CONDICIONAL, I VALE: "<<*getId()<<"  Y ESTA EN: "<<getId()<<endl;
			cout<<this->getSentencia()<<"   ";

			string condicion = this->leerCondicion();
			Calculadora* calc = new Calculadora(); string res;
			//cout<<calc->calcular(condicion, listaVar)<<endl;
			res = calc->calcularBooleano(condicion, listaVar);
			//cout<<endl<<res;
			if(res == "False"){
				return;
			}
			if(res == "True"){
				string instruc = this->leerInstruccion();
				Instruccion* ins = new Instruccion(instruc,listaVar);
				ins->ejecutarInstruccion(this->getId());

			}

		}
};

class Show : public Instruccion{
public:
	Show(string s, ListaDeVar* l, int* m){
		setId(m);
		listaVar = l;
		setSentencia(s);
	}
	void ejecutarShow(){
		cout<<"----------------------------------"<<endl<<"EJECUTANDO SHOW"<<endl;
		cout<<"I VALE: "<<*getId()<<"  I está en: "<<getId()<<endl;
		Calculadora* calc = new Calculadora();
		string s = this->leerExp();
		if(contiene(s,'>') || contiene(s,'<') || contiene(s,'=')){
			cout<<calc->calcularBooleano(this->leerExp(), listaVar);
		}
		else{
			cout<< calc->calcular(this->leerExp(), listaVar)<<endl;
			}
	}
	/*
	void ejecutarInstruccion(){
		cout<<"EJECUTANDO SHOW"<<endl;
		cout<<this->getSentencia()<<"   ";
		Calculadora* calc = new Calculadora();
		cout<< calc->calcular(this->leerExp(), listaVar)<<endl;
	}*/
	string leerExp(){
		bool concatenar = false;
		string expresion = "";
		string cadena = this->getSentencia();
		for(unsigned int i=0; i<cadena.size(); i++){
			if(cadena.at(i) == 'W' && !concatenar){
				concatenar = true;
			}
			else if(concatenar && cadena.at(i) != ' '){
				expresion.push_back(cadena.at(i));
			}
		}
		return expresion;
	}
};

class Jump : public Instruccion{
	public:
	Jump(string s, ListaDeVar* l, int* n){
		setId(n);
//		cout<<this->getId()<<"\n\n";
		setSentencia(s);
		listaVar = l;
	}

	string leerJump(){
		bool concatenar = false;
		string expresion = "";
		string cadena = this->getSentencia();
		for(unsigned int i=0; i<cadena.size(); i++){
			if(cadena.at(i) == 'P' && !concatenar){
				concatenar = true;
			}
			else if(concatenar && cadena.at(i) != ' '){
				expresion.push_back(cadena.at(i));
			}
		}
		return expresion;
	}
	void ejecutarJump(){
		cout<<"----------------------------------------"<<endl<<"EJECUTANDO JUMP"<<endl;
		cout<<this->getSentencia()<<"   ";
		cout<<"I VALE: "<<*getId()<<"  I está en: "<<getId()<<endl;

		*(this->getId()) = stoi(this->leerJump())-1 ;

	}
};

Instruccion::~Instruccion(){};
void Instruccion::ejecutarInstruccion(int* p){


	string str = this->getSentencia();
	listaVar->toPrint();
	if(str.substr(0,3) == "INT"){
		DeclaracionVar* d = new DeclaracionVar(str,listaVar,p);
		d->ejecutarDeclaracion();
	}
	else if(str.at(2) == '='){
		AsignacionVar* e = new AsignacionVar(str,listaVar,p);
		e->ejecutarAsignacion();
	}
	else if(str.substr(0,4) == "SHOW"){
		Show* f = new Show(str,listaVar,p);
		f->ejecutarShow();
	}
	else if(str.substr(0,4) == "JUMP"){
		Jump* j = new Jump(str, listaVar, p);
		j->ejecutarJump();
	}
	else if(str.substr(0,2) == "IF"){
		Condicional* k = new Condicional(str, listaVar, p);
		k->ejecutarCondicional();

	}

};


#endif /* INSTRUCCION_H_ */
