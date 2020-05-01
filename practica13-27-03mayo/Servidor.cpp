#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include "Respuesta.h"

using namespace std;

int main(int argc, char const *argv[]) {

	Respuesta respuesta(atoi(argv[1]));
  	char confirmacion[] = "Nuevo registro almacenado";


	while(1) {
		struct mensaje msj;
    	struct mensaje m1;
		FILE *archivo = NULL;
	  	archivo = fopen(argv[2], "r+");

	  	if (archivo == NULL) {
	    	cout << "Error al abrir el archivo (SERVIDOR)" << endl;
	  	}

		cout << "\nEsperando conexion : " << endl;
		memcpy(&msj, respuesta.getRequest(), sizeof(struct mensaje));

    cout << "Estos son los argumentos antes de la operacion: " << msj.arguments << endl;
		cout << "id: " << msj.operationId << endl;
		cout<< "IP: " <<msj.IP<<endl;
		cout << "Los argumentos son : " << msj.arguments << endl;
		fputs(msj.arguments,archivo);
		switch(msj.operationId) {
			case 1:
				//cout << "Id encontrado :  1" << endl;


				fclose(archivo);
        memcpy(m1.arguments, confirmacion, strlen(confirmacion)+1);

        m1.messageType = 1;
        memcpy(m1.IP, msj.IP, 16);//------------------
        m1.puerto = msj.puerto;
        m1.requestId = msj.requestId;
				respuesta.sendReply((char*) m1.arguments,m1.IP, msj.puerto);

				cout << "Fin del servicio" << endl;
        break;
			default:
				cout << "Error en el numero de operación" << endl;
				cout << "numero: " << msj.operationId << endl;
				exit(-1);
		}
	}


	return 0;
}
