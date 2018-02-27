/*
 * NotePAD.cpp
 * 
 * Copyright 2014 Victor <victor@VMorales>
 */

/* -------------------------------------------------------------------*/
#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <unistd.h>

/* -------------------------------------------------------------------*/
/*Mayúsculas*/
#define A 65
#define B 66
#define C 67
#define D 68
#define E 69
#define F 70
#define G 71
#define H 72
#define I 73
#define J 74
#define K 75
#define L 76
#define M 77
#define N 78
#define O 79
#define P 80
#define Q 81
#define R 82
#define S 83
#define T 84
#define U 85
#define V 86
#define W 87
#define X 88
#define Y 89
#define Z 90
/*Minúsculas*/
#define a 97
#define b 98
#define c 99
#define d 100
#define e 101
#define f 102
#define g 103 
#define h 104
#define i 105
#define j 106
#define k 107
#define l 108
#define m 109
#define n 110
#define o 111
#define p 112
#define q 113
#define r 114
#define s 115
#define t 116
#define u 117
#define v 118
#define w 119
#define x 120
#define y 121
#define z 122
/*Números*/
#define cero 48
#define uno 49
#define dos 50
#define tres 51
#define cuatro 52
#define cinco 53
#define seis 54
#define siete 55
#define ocho 56
#define nueve 57
/*Teclas de Función*/
#define _F3 27
#define _F4 27
#define _F6 27
#define _F8 27
#define _F11 27
#define _F12 27
/*Especiales*/
#define coma 44
#define punto 46
#define espac 32
#define enter 10
#define ESC 27
/*Funciones*/
#define _sig 62 // >
#define _atr 60 // <
#define _cop 45 // -
#define _peg 43 // +
#define _gua 42 // *
#define _car 47 // /
/*Otros*/
#define MAX_SCREEN_AREA 100

/* -------------------------------------------------------------------*/
/*Variables Globales*/
char linea[51];
int cont = 1;
int cont2 = 1;
char tmp[52];
int pagina = 1;
struct doc *rr = NULL;
using namespace std;

/* -------------------------------------------------------------------*/
	struct docX{
		char hori[50];
	};

	struct doc{
		struct doc *sig;
		struct doc *ant;
		int pag;
		struct docX texto[25];
	}documento;
	
	void ingTXT();
/* -------------------------------------------------------------------*/
	
	int getch(void){
		struct termios oldt,
		newt;
		int ch;
		tcgetattr( STDIN_FILENO, &oldt );
		newt = oldt;
		newt.c_lflag &= ~( ICANON | ECHO );
		tcsetattr( STDIN_FILENO, TCSANOW, &newt );
		ch = getchar();
		tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
		return ch;
	}
/* -------------------------------------------------------------------*/
	void crearDOC(struct doc **aa, int pa){
		struct doc *pp, *nn;
		pp = (*aa);
		nn = (*aa);
			if (pp == NULL){
				nn = (struct doc*) malloc(sizeof(struct doc));
				nn->pag = pa;
				nn->sig = NULL;
				nn->ant = NULL;
				//nn->texto = NULL;
				(*aa) = nn;
			}else{
			
			if(nn->pag > pa){
				crearDOC(&nn->sig,pa);
			}else{
				if(nn->pag < pa){
					crearDOC(&nn->ant,pa);
				}else{	
					printf("Datos iguales");
					(*aa)=nn;
				}	
			}
		}
	}
	
	struct doc * buscarDOC(struct doc *kk, int mm){
	struct doc *pp;
	int encontro=0;
	pp=kk;
	while((pp!=NULL)&&(encontro==0)){
		if(pp->pag>mm){
			pp=pp->ant;
		}else{
			if(pp->pag<m){
				pp=pp->sig;
			}else{
				encontro=1;
				printf("Dato encontrado:  ");
				printf("%d",pp->pag);
				return (pp);				
			}
		}
			
	}
	if(pp==NULL){
		return(0);
		printf("NO ESTA EL DATO");
	}
	return 0;
}
/* -------------------------------------------------------------------*/
	int gotoxy(int xx, int yy){
		char essq[MAX_SCREEN_AREA]={0}; 
		sprintf(essq, "\033[%d;%df", yy,xx);
		printf("%s", essq);
		return 0;
	}
/* -------------------------------------------------------------------*/
	void pintarHEAD(int ii){
		gotoxy(22,0);
		printf("Hoja No. ");
		printf("%d\n",ii);
	}
	
	void pintarHOJA(){
		int ii,jj;
			gotoxy(1,2);for (ii=1;ii<52;ii++){printf("=");}
		
			gotoxy(1,28);for (ii=0;ii<52;ii++){printf("=");}
			
			for (jj=1;j<27;jj++){gotoxy(2,jj+1);printf(":");}
			
			for (jj=1;jj<27;jj++){gotoxy(52,jj+1);printf(":");}			
	}
	
	void pintarBOTON(){	
		gotoxy(55,10);printf("=========== ===========");
		gotoxy(55,11);printf(":Anterior : :Siguiente:");
		gotoxy(55,12);printf(":    <    : :     >   :");
		gotoxy(55,13);printf("=========== ===========");
		gotoxy(55,14);printf("=========== ===========");
		gotoxy(55,15);printf(":  Copiar : :  Pegar  :");
		gotoxy(55,16);printf(":    -    : :    +    :");
		gotoxy(55,17);printf("=========== ===========");
		gotoxy(55,18);printf("=========== ===========");
		gotoxy(55,19);printf(":  Borrar : :  Cargar :");
		gotoxy(55,20);printf(":    *    : :     /   :");
		gotoxy(55,21);printf("=========== ===========");		
	}
/* -------------------------------------------------------------------*/	
	void copiar(){
		int lin_c = 0;
		strcpy(tmp,"\0");
		gotoxy(55,23);printf("Linea a copiar?: ");
		cin >> lin_c;
			switch(getch()){
				case enter: 
					strcpy(tmp,documento.texto[lin_c].hori);
				break;
			}
		sleep(1);
		gotoxy(55,23);printf("                  ");
		gotoxy(55,24);printf("Linea en memoria!");
			switch(getch()){
				case enter: 
					gotoxy(55,24);printf("                  ");
				break;
			}
		gotoxy(2,2+cont2);
		//printf("%s",tmp);
		lin_c = 0;
	}
	
	void pegar(){
		int lin_c2 = 0;
		gotoxy(55,23);printf("Linea a pegar?: ");
		cin >> lin_c2;
			switch(getch()){
				case enter: 
					strcpy(documento.texto[lin_c2].hori,tmp);
				break;
			}
		//int tm2 = lin_c2 + 3;
		gotoxy(2,2+lin_c2);printf("%s",documento.texto[lin_c2].hori);
		//gotoxy(2,tm2);
		sleep(1);gotoxy(55,23);printf("                  ");
			switch(getch()){
				case enter:
					gotoxy(2,2+cont2);
				break;
			}
		lin_c2 = 0;
		strcpy(tmp,"\0");
	}
	
	void siguiente(){
		if (pagina<3){
			pagina++;
			crearDOC(&rr,pagina);
			pintarHEAD(pagina);
			pintarBOTON();
			pintarHOJA();
				for(int xxx = 1;xxx < 25;xxx++){
					gotoxy(2,2+xxx);printf("                                                  ");
				}
			gotoxy(2,3);ingTXT();		
		}
	}
	
	
	void atras(){
		if(pagina>1){
			pagina--;
			buscarDOC(rr,pagina);
			pintarHEAD(pagina);
			pintarBOTON();
			pintarHOJA();
				for(int xxx = 1;xxx <= 25;xxx++){
					gotoxy(2,2+xxx);printf("%s",documento.texto[xxx].hori);
				}		
			gotoxy(2,3);ingTXT();		
		}
	}
	
	void ingTXT(){
		//int cont = 1;
		//int cont2 = 1;
		int ii = 3;
		//printf("Ingrese su texto: \n");
			do{
				do{
					switch(getch()){
						/*Mayúsculas*/
						case A: printf("A"); strcat(linea,"A"); cont++; break;
						case B: printf("B"); strcat(linea,"B"); cont++; break;
						case C: printf("C"); strcat(linea,"C"); cont++; break;
						case D: printf("D"); strcat(linea,"D"); cont++; break;
						case E: printf("E"); strcat(linea,"E"); cont++; break;
						case F: printf("F"); strcat(linea,"F"); cont++; break;
						case G: printf("G"); strcat(linea,"G"); cont++; break;
						case H: printf("H"); strcat(linea,"H"); cont++; break;
						case I: printf("I"); strcat(linea,"I"); cont++; break;
						case J: printf("J"); strcat(linea,"J"); cont++; break;
						case K: printf("K"); strcat(linea,"J"); cont++; break;
						case L: printf("L"); strcat(linea,"L"); cont++; break;
						case M: printf("M"); strcat(linea,"M"); cont++; break;
						case N: printf("N"); strcat(linea,"N"); cont++; break;
						case O: printf("O"); strcat(linea,"O"); cont++; break;
						case P: printf("P"); strcat(linea,"P"); cont++; break;
						case Q: printf("Q"); strcat(linea,"Q"); cont++; break;
						case R: printf("R"); strcat(linea,"R"); cont++; break;
						case S: printf("S"); strcat(linea,"S"); cont++; break;
						case T: printf("T"); strcat(linea,"T"); cont++; break;
						case U: printf("U"); strcat(linea,"U"); cont++; break;
						case V: printf("V"); strcat(linea,"V"); cont++; break;
						case W: printf("W"); strcat(linea,"W"); cont++; break;
						case X: printf("X"); strcat(linea,"X"); cont++; break;
						case Y: printf("Y"); strcat(linea,"Y"); cont++; break;
						case Z: printf("Z"); strcat(linea,"Z"); cont++; break;
						/*Minúsculas*/
						case a: printf("a"); strcat(linea,"a"); cont++; break;
						case b: printf("b"); strcat(linea,"b"); cont++; break;
						case c: printf("c"); strcat(linea,"c"); cont++; break;
						case d: printf("d"); strcat(linea,"d"); cont++; break;
						case e: printf("e"); strcat(linea,"e"); cont++; break;
						case f: printf("f"); strcat(linea,"f"); cont++; break;
						case g: printf("g"); strcat(linea,"g"); cont++; break;
						case h: printf("h"); strcat(linea,"h"); cont++; break;
						case i: printf("i"); strcat(linea,"i"); cont++; break;
						case j: printf("j"); strcat(linea,"j"); cont++; break;
						case k: printf("k"); strcat(linea,"k"); cont++; break;
						case l: printf("l"); strcat(linea,"l"); cont++; break;
						case m: printf("m"); strcat(linea,"m"); cont++; break;
						case n: printf("n"); strcat(linea,"n"); cont++; break;
						case o: printf("o"); strcat(linea,"o"); cont++; break;
						case p: printf("p"); strcat(linea,"p"); cont++; break;
						case q: printf("q"); strcat(linea,"q"); cont++; break;
						case r: printf("r"); strcat(linea,"r"); cont++; break;
						case s: printf("s"); strcat(linea,"s"); cont++; break;
						case t: printf("t"); strcat(linea,"t"); cont++; break;
						case u: printf("u"); strcat(linea,"u"); cont++; break;
						case v: printf("v"); strcat(linea,"v"); cont++; break;
						case w: printf("w"); strcat(linea,"w"); cont++; break;
						case x: printf("x"); strcat(linea,"x"); cont++; break;
						case y: printf("y"); strcat(linea,"y"); cont++; break;
						case z: printf("z"); strcat(linea,"z"); cont++; break;
						/*Números*/
						case cero: 	printf("0"); strcat(linea,"0"); cont++; break;
						case uno: 	printf("1"); strcat(linea,"1"); cont++; break;
						case dos: 	printf("2"); strcat(linea,"2"); cont++; break;
						case tres: 	printf("3"); strcat(linea,"3"); cont++; break;
						case cuatro:printf("4"); strcat(linea,"4"); cont++; break;
						case cinco: printf("5"); strcat(linea,"5"); cont++; break;
						case seis: 	printf("6"); strcat(linea,"6"); cont++; break;
						case siete: printf("7"); strcat(linea,"7"); cont++; break;
						case ocho: 	printf("8"); strcat(linea,"8"); cont++; break;
						case nueve: printf("9"); strcat(linea,"9"); cont++; break;
						/*Especiales*/
						case punto:	printf("."); strcat(linea,"."); cont++; break;
						case coma:	printf(","); strcat(linea,","); cont++; break;
						case espac: printf(" "); strcat(linea," "); cont++; break;
						//case enter: printf("\n");strcat(linea,"\n");cont=50; break;
						/*Funciones*/
						case _sig: siguiente();break;
						case _atr: atras();break;
						case _gua: break;
						case _car: break;
						case _cop: copiar();break;
						case _peg: pegar();break;

					}
				}while(cont <= 50);
			printf("\n"); ii++; gotoxy(2,ii);
			//printf("%s",linea);
			strcpy(documento.texto[cont2].hori,linea);
			strcpy(linea,"\0");
			cont2++; cont= 1;
			}while(cont2 <= 25);
		
	} 

int main(int argc, char **argv){

	do{	
		crearDOC(&rr,pagina);
		pintarHEAD(pagina);
		pintarBOTON();
		pintarHOJA();
		gotoxy(2,3);ingTXT();
	}while(getch()!=ESC);

	
}


