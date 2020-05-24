#include "Solicitud.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

int main(int argc, char*argv[]) {
	
	struct timeval timeout;
  	timeout.tv_sec = 2;
  	timeout.tv_usec = 500000;
	char arreglo[4000]="Cadena a enviar";
	char *ip, *registros;
	int puerto;
	int operacion = 1;
	ip =argv[1];
	puerto = atoi(argv[2]);
	Solicitud cliente = Solicitud(timeout);
	cliente.doOperation(ip, puerto, operacion, arreglo);
	return 0;
}
