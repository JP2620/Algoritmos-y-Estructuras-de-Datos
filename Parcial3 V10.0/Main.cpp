/*
 * Main.cpp
 *
 *  Created on: Jun 19, 2019
 *      Author: Juan Pablo
 */

#include <limits.h>
#include <stdio.h>
#include<iomanip>
#include "Cola.h"
#include <map>
#include <algorithm>
#include <chrono>


#define V 12
#define INF 100000
#define FUENTE -1

using namespace std::chrono;

void printArray(const int array[V]){
	cout<<"\n\n";
	for(int i=0; i<V; i++){
		cout<<array[i]<<"  ";
	}
	cout<<"\n\n";
}

//dijkstra clasico nada raro
void dijkstra(const int grafo[V][V], const int source, int* pred){

	//distancias desde source de cada vertice
	//pred es vector de predecesores
	int d[V];
	for(int i=0; i<V; i++) d[i] = INF;

	//Lista de vértices a los q le encontramos su shortest path
	Lista* S = new Lista();
	//distancia desde la fuente a la fuente es 0

	d[source] = 0;
	//Cola de prioridad para explorar (empieza con todos)
	Cola* Q = new Cola();
	for(int i=0; i<V; i++){
		Q->add(i);
	}
	//Q->impre();
	while(Q->size() != 0){
		int u = Q->extraerMin(d);
		S->add(u);
		//cout<<endl<<u<<endl;
		for(int v=0; v<V; v++){
			//Si existe el edge, lo relaja
			if(grafo[u][v] != INF){
				if(d[v] > d[u]+grafo[u][v]){
					d[v] = d[u]+grafo[u][v];
					pred[v]=u;
				}
			}
		}
	}
	return;
}


//dfs con poda y guarda camino minimo en resultado
void DFS(const int prof,const int actual,const int grafo[V][V], const int predAntes[V], int* resultado,
		int* DistMin = new int(INF),const int profActual=0, const int distancia= 0,const int pred=FUENTE){

    int predActual[V];
    for(int i=0; i<V; i++){
    	predActual[i] = predAntes[i];
    }
    predActual[actual]=pred;

    //poda
    if(distancia> *(DistMin)) return;
    //corto porque llegue a la profundidad deseada
    if(profActual == prof){
    	//updateo distancia minima y resultado
    	if(actual == 9){
    		*DistMin = distancia;
    		for(int i=0; i<V; i++)   resultado[i] = predActual[i];
    	}
    	return;
    }
    //recursion de dfs
    int delta;
    for(int j=0;j<V;j++){
        if(predActual[j] == INF && grafo[actual][j]!=INF){
        	delta = grafo[actual][j];
            DFS(prof,j,grafo,predActual, resultado, DistMin, profActual+1, distancia+delta, actual);
        }
    }
}


//presenta los resultados de la dfs
void printPathDFS(const int resultado[V],const map<int, string> *mapa,const int grafo[V][V]){
    int inicio; int final;
	for(int i=0; i<V; i++){
		if(resultado[i] == FUENTE){
			inicio = i;
			break;
		}
	}
    bool cond = true; int acumulado = 0;
    while(true){
    	for(int i=0; i<V; i++){
    		if(resultado[i] == inicio) final = i;
    	}
    	if(cond && grafo[inicio][final] != INF){
    		acumulado += grafo[inicio][final];
        	cout<<setw(20)<<mapa->at(inicio)<<setfill(' ')<<setw(20)<<
        			mapa->at(final)<< setw(20)<<acumulado<<"\n";
        	inicio = final;
    	}
    	else{
    		break;
    	}
    }
}


int main()
{

	/*
	int grafo[V][V];
	for(int i=0; i<V; i++){
		for(int j=0; j<V; j++){
			grafo[i][j] = (i != j)? rand()%1000  :  INF;
		}
	}*/


	//                   	  MA    BA    RO    PA    LO    AM     ZU   BE    VA    MO    VI    BU
    const int grafo[V][V]= {{ INF , 150 , 250 , 210 , 340 , INF , 300 , INF , INF , INF , INF , INF }, // MA
                    	    { INF , INF , 220 , 200 , 350 , 695 , INF , INF , INF , INF , INF , INF }, // BA
							{ INF , 210 , INF , 350 , 440 , INF , 150 , INF , INF , 900 , 250 , 320 }, // RO
							{ INF , INF , 370 , INF ,  95 , 100 , INF , 200 , INF , INF , 320 , INF }, // PA
							{ INF , INF , 320 ,  95 , INF , 150 , 240 , INF , INF , 1200, INF , INF }, // LO
							{ INF , INF , 335 ,  90 , 140 , INF , 200 , 160 , INF , INF , INF , INF }, // AM
							{ INF , 290 , 145 , INF , 240 , 200 , INF , 120 , INF , INF , 450 , 380 }, // ZU
							{ INF , INF , 200 , 195 , 330 , 160 , 110 , INF ,  60 , 470 ,  80 ,  90 }, // BE
							{ INF , INF , INF , INF , 1000, 570 , 500 ,  10 , INF , 220 ,  60 ,  35 }, // VA
							{ INF , INF , INF , INF , INF , INF , INF , INF , INF , INF , INF , INF }, // MO
							{ INF , INF , 250 , INF , INF , 180 , 150 ,  90 ,  50 , INF , INF ,  15 }, // VI
							{ INF , INF , 300 , INF , INF , INF , INF ,  90 ,  20 , 180 , 10  , INF }};// BU


    std::map<int , string> ciudades;
    ciudades[0]  = "Madrid"    ;    ciudades[1]  = "Barcelona"   ;   ciudades[2]  = "Roma"      ;
    ciudades[3]  = "Paris"     ;    ciudades[4]  = "Londres"     ;   ciudades[5]  = "Amsterdam" ;
    ciudades[6]  = "Zurich"    ;    ciudades[7]  = "Berlin"      ;   ciudades[8]  = "Varsovia"  ;
    ciudades[9]  = "Moscu"     ;    ciudades[10] = "Viena"       ;   ciudades[11] = "Budapest"  ;
    ciudades[12] = "Praga"     ;    ciudades[13] = "Kiev"        ;   ciudades[14] = "Munich"    ;
    ciudades[15] = "Bruselas"  ;    ciudades[16] = "Oslo"        ;   ciudades[17] = "Copenhagen";
    ciudades[18] = "Helsinki"  ;    ciudades[19] = "Estanbul"    ;   ciudades[20] = "Marsella"  ;
    ciudades[21] = "Lisboa"    ;    ciudades[22] = "Bratislava"  ;   ciudades[23] = "Atenas"    ;

    //EJERCICIO 1

	const int origen = 0; const int destino = 9;
	int res[V];
	for(int i=0; i<V; i++) res[i]= INF;
    dijkstra(grafo, origen, res);
    //reconstruyo camino
    Lista* l = new Lista(); //pila
    l->add(destino);
    int predecesor = res[destino]; int acumulado = 0;
    //empiezo desde el final, asi que los apilo
    while(predecesor!= INF){
    	l->add(predecesor);
    	predecesor = res[predecesor];
    }
    //printeo los resultados
    cout<<"\t\tCamino de costo mínimo de "<<ciudades[origen]<<" a "<<ciudades[destino]<<"\n\n";
    Nodo* aux = l->cabeza();
    cout<<setw(20)<<"ORIGEN"<<setw(20)<<"DESTINO"<<setw(20)<<"PRECIO ACUMULADO"<<"\n\n";
    while(aux->get_next()->get_next() != NULL){
    	int u = aux->get_dato(); int v = aux->get_next()->get_dato();
    	acumulado += grafo[u][v];
    	cout<<setw(20)<<ciudades[u]<<setfill(' ')<<setw(20)<<ciudades[v]<< setw(20)<<
    			acumulado<<"\n";
    	aux=aux->get_next();
    }


    auto start = high_resolution_clock::now();
    //EJERCICIO 2 camino hamiltoniano

	int resultado2[V];
	int pre2[V];
	for(int i=0; i<V; i++) pre2[i] = INF;
	DFS(V-1,0,grafo,pre2, resultado2);
	cout<<"\n\n\t\tCamino Hamiltoniano:\n\n";
	printPathDFS(resultado2, &ciudades, grafo);


	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	//cout<<"\n\nTardó "<< duration.count() <<" milisegundos en encontrar el camino hamiltoniano\n\n";



	//EJERCICIO 3

	int pre3[V];
	for(int i=0; i<V; i++) pre3[i] = INF;
	int resultado3[V]; int nroCiudades = 10;
	int* minimaD = new int(INF);
	DFS(nroCiudades-1,0,grafo,pre3, resultado3, minimaD);
	cout<<"\n\n\t\tCamino mínimo que recorre "<<nroCiudades<<" ciudades\n\n";
	printPathDFS(resultado3, &ciudades, grafo);

    return 0;
}
