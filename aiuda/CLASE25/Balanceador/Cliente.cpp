//#include "Solicitud.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

//const char ip1[16] = "10.100.74.141";
//const char ip2[16] = "10.100.74.144";
//const char ip2[16] = "10.100.74.145";
//const char servidor1[16] = "Servidor1.txt";
//const char servidor2[16] = "Servidor2.txt";
//const char servidor3[16] = "Servidor3.txt";

/*void funcion(char[] nombreArchivo){
	
}*/

int main(int argc, char*argv[]) {
	struct timeval timeout;
	string numeroTel = "";
  	timeout.tv_sec = 2;
  	timeout.tv_usec = 500000;
	char arreglo[119]="1234567891\n1234567892\n1234567893\n1234567894\n1234567895\n1234567896\n1234567897\n1234567898\n1234567899";
	for(int i=0; i<119; i++){
		numeroTel = numeroTel + arreglo[i];
		if(arreglo[i] == '\n'){
			cout<<"Enviando al servidor..."<<endl;
			string resultado = numeroTel.substr(9);
			
			cout<<"Numero final: " <<numeroFinal <<endl;
			switch(numeroFinal){
				case '0':
				case '1':
				case '2':
				case '3':
					cout<<"Enviando al servidor 1"<<endl;
					break;
				case '4':
				case '5':
				case '6':
					cout<<"Enviando al servidor 2"<<endl;
					break;
				case '7':
				case '8':
				case '9':
					cout<<"Enviando al servidor 3"<<endl;
					break;
				default:
					cout<<"Enviando al servidor 1"<<endl;
					break;
			}
		}
	}
	//////////////////////////
	/*char *ip, *registros;
	int puerto;
	int operacion = 1;

	ip =argv[1];
	puerto = atoi(argv[2]);
	registros = argv[3];

	memcpy(arreglo, registros, sizeof(strlen(registros) + 1));

	// arreglo contiene el numero de registros que serán leidos para ser enviados al servidor*/
	//Solicitud cliente = Solicitud(timeout);
	//cliente.doOperation(ip, puerto, operacion, arreglo);
	return 0;
}
