#include "Solicitud.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

int main(int argc, char*argv[]) {
	struct timeval timeout;
    timeout.tv_sec = 2;
    timeout.tv_usec = 500000;
	
	char arreglo[4000] ="";
	char val1[49];
	char val2[49];
	char val3[2] = "/";
	char *ip;
	int puerto;
	int operacion = 1;

	ip =argv[1];
	puerto = atoi(argv[2]);
	
	memcpy(val1, argv[3], sizeof(argv[3]));	
	memcpy(val2, argv[4], sizeof(argv[4]));
	strcat(arreglo,val1);
	strcat(arreglo," ");
	strcat(arreglo,val2);
	cout<<arreglo<<endl;
	Solicitud cliente = Solicitud();	
	cliente.doOperation(ip, puerto, operacion, arreglo);
	return 0;
}
