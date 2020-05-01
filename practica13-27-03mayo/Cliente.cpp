#include "./dependencies/Solicitud.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

int main(int argc, char*argv[]) {

	char arreglo[100];
	char *ip;
	int puerto;
	int operacion = 1;

	if(argc != 4){
		printf("Forma de uso: programa ip_server port_server data_file\n");
		exit(0);
	}  

	FILE *archivo = NULL;
	archivo = fopen(argv[3],"r+");
	if (archivo == NULL) {
		printf("%s\n", "App error: No se pudo abrir el archivo fuente");
	}

	ip =argv[1];
	cout << ip << endl;
	puerto = atoi(argv[2]);

	//memcpy(val1, argv[3], sizeof(argv[3]));
	//memcpy(val2, argv[4], sizeof(argv[4]));
	fgets(arreglo,100,archivo);
	fflush(archivo);
	fclose(archivo);
	cout<<arreglo<<endl;
	Solicitud cliente;
	printf("Servidor: %s\n", cliente.doOperation(ip, puerto, operacion, arreglo));

	return 0;
}
