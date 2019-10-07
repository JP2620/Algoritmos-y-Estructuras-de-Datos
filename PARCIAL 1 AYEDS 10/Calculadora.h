/*
 * Calculadora.h
 *
 *  Created on: May 13, 2019
 *      Author: Juan Pablo
 */

#ifndef CALCULADORA_H_
#define CALCULADORA_H_
#include "ListaDeVar.h"

typedef int token;

class Token{
	void setValor(string s){ valor = s;}
	string getValor(){return valor;}
	private:
	string valor;
};
class NodoToken{
    protected:
        token dato;
        NodoToken *next;
    public:
        NodoToken() {next=NULL;};
        NodoToken(token a) {dato=a; next=NULL;};
        void set_dato(token a) {dato=a; };
        void set_next(NodoToken *n) {next=n; };
        token get_dato() {return dato; };
        NodoToken *get_next() {return next; };
        bool es_vacio() {return next==NULL;}
};

class ListaToken{
    protected: NodoToken *czo;
    public:
            ListaToken() {czo=new NodoToken();};
            ListaToken(NodoToken *n) {czo=n;};
            void del(void);
            void add(token d);
            bool esvacia(void);
            token cabeza(void);
            ListaToken *resto(void);
};

class PilaToken:public ListaToken{
      public:
             PilaToken(){ListaToken();};
             void apilar(token x){add(x);};
             token tope(void){return cabeza();};
             void desapilar(void){del();};
             bool pilavacia(){return esvacia();};
};



void ListaToken::del(void)
{    NodoToken *aux;
     aux=czo;
     czo=czo->get_next();
     delete aux;
}
void ListaToken::add(token d)
{
     NodoToken *nuevo=new NodoToken(d);
     nuevo->set_next(czo);
     czo=nuevo;
}
bool ListaToken::esvacia(void)
{
    return czo->es_vacio();
}

token ListaToken::cabeza(void)
{
  if(esvacia()){
                cout<<" Error, Cabeza de lista vacia";
                return ' ';
  }
  return czo->get_dato();
}

ListaToken *ListaToken::resto(void)
{
      ListaToken *l=new ListaToken(czo->get_next());
      return (l);
}
// funcion precedencia
// prcd(o1,'(') = 0 para todo o1 != de ')'
// prcd(o1,')') = 1 para todo o1 != de '('
// prcd('(',o2) = 0 para todo 02
// prcd(o1,o2)  = 1 para todo o1 >= precedencia que o2


bool contiene(string s,char a){
	bool res = false;
	for(unsigned int i=0; i<s.size(); i++){
		if(s.at(i) == a) return true;
	}
	return res;
}
bool legal(char a){
	if(contiene("1234567890abcdefghijklmnopqrstuvwxyz+-/*()",a)) return true;
	else return false;
}




int prcd(int o1,int o2)
{ if(o2=='(')
	 if(o1==')') return 1;
            else return 0;
  if(o2==')')
	 if(o1=='(') return 0;
		    else return 1;
  if(o1=='(') return 0;

  if((o1=='*')||(o1=='/')) return 1;
  if(((o1=='+')||(o1=='-'))&&((o2=='+')||(o2=='-'))) return 1;
						                        else return 0;
}


/*cadena
 * concateno a ecuacion1 hasta que encuentre un ! = < >
 * concateno el operador
 * concateno la otra ecuacion2
 *
 * segun el operador retorno la comparacion entre ecuacion 1 y ecuacion 2
 *
 * caracter es de la expresion
 *
 */
class Calculadora{
	public:
	string calcularBooleano(string cadena, ListaDeVar* l){

		string ecuacion1 = "";
		string ecuacion2 = "";
		string operador = "";
		for(unsigned int i=0; i<cadena.size();i++){
			char caracter = cadena.at(i);
			if(contiene("!=><",caracter)){
				operador.push_back(caracter);
				string cadena2 = cadena.substr(i+1,10000);
				for(unsigned int j=0; j<cadena2.size();j++){
					if(contiene("!=><",cadena2.at(j))){
						operador.push_back(cadena2.at(j));
					}
				if(legal(cadena2.at(j))){
				ecuacion2.push_back(cadena2.at(j));}
				}
				break;
			}
			if(legal(caracter)){
				ecuacion1.push_back(caracter);}
		}

		if(operador.length()!=0){
			int res1 = calcular(ecuacion1,l);
			int res2= calcular(ecuacion2,l);
			if(operador == "=="){
				return intToBooleano(res1 == res2);
			}
			else if(operador == "!="){
				return intToBooleano(res1 != res2);
			}
			else if(operador == ">"){
				return intToBooleano(res1 > res2);
			}
			else if(operador == "<"){
				return intToBooleano(res1 < res2);
			}
			else if(operador == "<="){
				return intToBooleano(res1 <= res2);
			}
			else if(operador == ">="){
				return intToBooleano(res1 >= res2);
			}
		}
		else{
			cout<<"\n\n\nERROR NO DETECTE OPERADOR RELACIONAL\n\n\n";
			return "true";
		}
	}
	int calcular(string cadena,ListaDeVar* l){
		string pf;
		PilaToken *p=new PilaToken();
		// chequeo de la correspondencia de los ()
		  int error=0;
		  for(unsigned int i=0;(i<cadena.length())&&(!error);i++){
		          if (cadena.at(i)=='{') p->apilar('{');
		          if (cadena.at(i)=='[') p->apilar('[');
		          if (cadena.at(i)=='(') p->apilar('(');

		          if (cadena.at(i)=='}'){
		                                 if (p->pilavacia()) error=1;
		                                 else
		                                     if(p->tope()!='{') error=1;
		                                     else p->desapilar();
		          }
		          if (cadena.at(i)==']'){
		                                 if (p->pilavacia()) error=1;
		                                 else
		                                     if(p->tope()!='[') error=1;
		                                     else p->desapilar();
		          }
		          if (cadena.at(i)==')'){
		                                 if (p->pilavacia()) error=1;
		                                 else
		                                     if(p->tope()!='(') error=1;
		                                     else p->desapilar();
		          }
		    }
		    //if((!error)&&p->pilavacia())cout<<endl<<"TOdo OK";
		    //else cout<<endl<<"ERROR";

		    //cout<<"\n Inicio conversion a POSFIJO de:"<<cadena<<endl;
		//conversion de entrefijo a posfijo



		      char d,p1;
		      for(unsigned int j=0;j<cadena.length();j++)
		      {   d=cadena.at(j);
			      if (((d>='0')&&(d<='9')) || (d>='a' && d<='z')){
		             pf.push_back(d);
			      }
			       else{
			    	   while((!p->pilavacia())&&(prcd(p->tope(),d)))
			           {p1=p->tope();p->desapilar();pf.push_back(p1);}
			           if((p->pilavacia())||(d!=')')) p->apilar(d);
				       else p->desapilar();
			      }
		      }
		      while(!p->pilavacia())
			      {p1=p->tope();p->desapilar();pf.push_back(p1);}



		      //cout<<"\n TERMINE la conversion a POSFIJO: "<<pf<<endl;
		 cout<<endl<<pf<<endl;




		// Evaluacion de la expresion en posfijo
		  int o1,o2;
		  for(unsigned int i=0;(i<pf.length())&&(!error);i++){
		     d=pf.at(i);
		     if(d>='0' && d<='9'){
		    	 p->apilar(d-'0');

		     }
		     if(d>='a' && d<='z'){
		    	 string token1 = string(1,d);
		    	 if(l->estaEnLista(token1)){
		    		 p->apilar(l->encontrarVar(token1)->cabeza().getValor());
		    	 }
		     }
		     if(d=='+'){
		               o2=p->tope(); p->desapilar();
		               o1=p->tope(); p->desapilar();
		               p->apilar(o1+o2);
		     }
		     if(d=='-'){
		               o2=p->tope(); p->desapilar();
		               o1=p->tope(); p->desapilar();
		               p->apilar(o1-o2);
		     }
		     if(d=='*'){
		               o2=p->tope(); p->desapilar();
		               o1=p->tope(); p->desapilar();
		               p->apilar(o1*o2);
		     }
		     if(d=='/'){
		    	 o2 = p->tope(); p->desapilar();
		    	 o1 = p->tope(); p->desapilar();
		    	 p->apilar(o1/o2);
		     }


		     }
		  //cout<<endl<<"\n\nResultado= "<<p->tope()<<endl;

		  cout<<endl;
		  return p->tope();
		}

	string intToBooleano(int res){
		if(res == 0) return "False";
		else return "True";
	}

	};



#endif /* CALCULADORA_H_ */
