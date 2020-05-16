#include "PaqueteDatagrama.h"
#include "Solicitud.h"
#include "SocketDatagrama.h"
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <pthread.h>
#include <thread>


#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <iterator> 
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <cstdlib>      // std::rand, std::srand
using namespace std;
//5504289502
struct registro{
	char celular[11];
	char CURP[19];
	char partido[4];
};

void prueba1(int num){


	Solicitud request=Solicitud();
	char c;
	string dato="",cad2="",cad3="",cad1="";
	char ip[]="127.0.0.1";
 	int puerto, nn=0, res;
	char *respuesta, cad11[11]="",cad12[19]="",cad13[4]="";

	struct registro reg1;
	int destino=open("registros.txt", O_RDONLY,0666);

	if(destino!=-1)
	{
	//LEER EL ARCHIVO
	//El archivo se lee caracter por caracter
		while(read(destino,&c,sizeof(c)!=0)){
			dato= dato+c;

			if(nn==33){
				cad1= dato.substr(0,10);
				cad2= dato.substr(11,19);
				cad3= dato.substr(30,34);
				strcpy(cad11,cad1.c_str());
				strcpy(cad12,cad2.c_str());
				strcpy(cad13,cad3.c_str());
				//cout<<dato<<endl;
				dato="";
				nn=0;
				
				memcpy(reg1.celular,cad11,11);
				memcpy(reg1.CURP,cad12,19);
				memcpy(reg1.partido,cad13,4);
				
				
				if((reg1.celular[9]-'0')%2==0){
					puerto=9002;
					respuesta=request.doOperation(ip,puerto,suma,(char*)&reg1);
				}
				printf("envió %s\n",respuesta);
			}
			else{
				nn++;
			}
		}
		close(destino);
	}
		 
	else{
		printf("\nEl archivo no existe");
	}
}

void prueba2(int num){


	Solicitud request=Solicitud();
	char c;
	string dato="",cad2="",cad3="",cad1="";
	char ip[]="10.100.79.90";
 	int puerto,nn=0, res;
	char *respuesta, cad11[11]="",cad12[19]="",cad13[4]="";

	struct registro reg1;
	int destino=open("registros.txt", O_RDONLY,0666);

	if(destino!=-1)
	{
	//LEER EL ARCHIVO
	//El archivo se lee caracter por caracter
		while(read(destino,&c,sizeof(c)!=0)){
			dato= dato+c;

			if(nn==33){
				cad1= dato.substr(0,10);
				cad2= dato.substr(11,19);
				cad3= dato.substr(30,34);
				strcpy(cad11,cad1.c_str());
				strcpy(cad12,cad2.c_str());
				strcpy(cad13,cad3.c_str());
				//cout<<dato<<endl;
				dato="";
				nn=0;
				
				memcpy(reg1.celular,cad11,11);
				memcpy(reg1.CURP,cad12,19);
				memcpy(reg1.partido,cad13,4);
				
				
				if((reg1.celular[9]-'0')%2!=0){
					puerto=9000;
					respuesta=request.doOperation(ip,puerto,suma,(char*)&reg1);
				}
				printf("envió %s\n",respuesta);
			}
			else{
				nn++;
			}
		}
		close(destino);
	}
		 
	else{
		printf("\nEl archivo no existe");
	}
}


int main(int argc, char** argv){

	thread serv1(prueba1, 0);
	thread serv2(prueba2, 1);//puerto 9002 puerto9000

	serv1.join();
	serv2.join();

	cout<<"termino"<<endl;
	
	return 0;
}
//5504289502