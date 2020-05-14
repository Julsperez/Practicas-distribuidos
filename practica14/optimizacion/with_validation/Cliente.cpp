#include "./dependencies/Solicitud.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

int main(int argc, char*argv[]) {
	
	char arreglo[100];
	char *ip, *registros;
	int puerto;
	int operacion = 1;
	
	struct timeval timeout;
  	timeout.tv_sec = 2;
	timeout.tv_usec = 500000;

	ip = argv[1];
	puerto = atoi(argv[2]);
	registros = argv[3];

	Solicitud cliente = Solicitud(timeout);

	memcpy(arreglo, registros, sizeof(strlen(registros) + 1));
	
	cliente.doOperation(ip, puerto, operacion, arreglo);

	return 0;
}
