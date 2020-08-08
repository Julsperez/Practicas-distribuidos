#include <iostream>
#include "Respuesta.h"

using namespace std;

int main(int argc, char *argv[]) {
	int puerto = 0;

	if(argc == 2) {
		puerto = atoi(argv[1]);
	} else {
		cout << "Ingrese el comando de forma correcta" << endl;
		cout << "\t ./Servidor <puerto>";
		exit(-2);
	}

	Respuesta srv(puerto);
	unsigned int nbd = 0;
	unsigned int idProcesada = 0;
	cout << "Escuchando..." << endl;
	while(1) {
		struct Mensaje *pet = srv.getRequest();
		
		switch(pet->operationId) {
			case 1:
				cout << "Operacion Lectura" << endl;
				memcpy((unsigned int *)pet->arguments, &nbd, sizeof(unsigned int));
				cout << "nbd enviado" << endl;
				idProcesada = pet->requestId;
			break;
			case 2:
				idProcesada++;
				cout << "Operacion escritura" << endl;
				int nbdCliente;
				memcpy(&nbdCliente,(unsigned int *)pet->arguments, sizeof(unsigned int));
				if(idProcesada == pet->requestId)
					nbd += nbdCliente;
				else
					cout << "Mensaje duplicado, accion ignorada" << endl;
				memcpy((unsigned int *)pet->arguments, &nbd, sizeof(unsigned int));
				cout << "nuevo saldo enviado" << endl;
			break;
		}
		srv.sendReply(pet);
	}
}
