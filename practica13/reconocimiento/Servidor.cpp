#include <cstdlib>
#include <iostream>
#include <string>
#include "./dependencies/Respuesta.h"

using namespace std;


int main(int argc, char const *argv[]) {
	struct timeval timeout;
	timeout.tv_sec = 100;
	timeout.tv_usec = 500000;
	long int expected = 0, prev = -1;
	
	Respuesta respuesta(atoi(argv[1]),timeout);
	char confirmacion[] = "Ok computer";

	while(1) {
		struct mensaje msj;
		struct mensaje m1;
		
		FILE *archivo = NULL;
	  	archivo = fopen(argv[2], "a+");
	  	if (archivo == NULL) {
	    	cout << "Server error: No se encontro el archivo " << argv[2] << endl;
	  	}

	  	cout << "\nEscuchando: "<< expected << ":"<< endl;
	  	//Request info
		memcpy(&msj, respuesta.getRequest(), sizeof(struct mensaje));

		switch(msj.operationId) {
			
			case 1: // Op:1:Guarda datos
				if(msj.requestId == expected){
					fputs(msj.arguments, archivo);
					fclose(archivo);
					// Lleva control de registros
					prev = expected;
					expected++;
				} 
				else if(msj.requestId == prev) { // repeticion de registro, no escribe en archivo
					fclose(archivo);					
				} else { // Inconsistencia: requestID != (prev, expected) 
					fclose(archivo);	
					cout << "Action ignored" << endl;
				}

				// Prepara respuesta m1
		        m1.messageType = 1;
		        m1.puerto = msj.puerto;
		        m1.requestId = msj.requestId;
        		memcpy(m1.arguments, confirmacion, strlen(confirmacion)+1);
		        memcpy(m1.IP, msj.IP, 16);

		        // Envia respuesta
				respuesta.sendReply((char*) m1.arguments,m1.IP, msj.puerto);

				cout << ": Operacion terminada ---" << endl;
			break;

			default:
				cout << "Server error: No existe operacion " << msj.operationId  << ", conexion ignorada."<< endl;
		}
	}
	return 0;
}
