#include "Solicitud.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

int main(int argc, char*argv[]) {
	struct timeval timeout;
  timeout.tv_sec = 2;
  timeout.tv_usec = 500000;


	char arreglo[100]="";
	char *ip, *registros;
	int puerto;
	int operacion = 1;

	ip =argv[1];
	puerto = atoi(argv[2]);
	registros = argv[3];

	memcpy(arreglo, registros, sizeof(strlen(registros) + 1));

	// arreglo contiene el numero de registros que serán leidos para ser enviados al servidor
	Solicitud cliente = Solicitud(timeout);
	cliente.doOperation(ip, puerto, operacion, arreglo);

	return 0;
}
