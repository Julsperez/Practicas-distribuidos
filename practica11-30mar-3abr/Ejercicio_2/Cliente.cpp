#include <iostream>
#include <cstring>
#include "Solicitud.h"
#include "Mensaje.h"
#include <time.h>

using namespace std;

int main(int argc, char *argv[]) {

	srand(time(0)); 
	int nVeces, puerto = 0;
	char *ip;

	if(argc == 4) {
		ip = argv[1];
		puerto = atoi(argv[2]);
		nVeces = atoi(argv[3]);
	} else {
		cout << "Ingrese el comando de forma correcta" << endl;
		cout << "\t ./Cliente <IP remota> <puerto> <numero de depositos>";
		exit(-2);
	}

	Solicitud cl(4201);
	unsigned int nbdLocal = 0;
	unsigned int nbdServidor = 0;
	int pesos = (rand() % 9) + 1;
	
	struct Mensaje *resp = (struct Mensaje *)cl.doOperation(ip , puerto, 1, (char *)&pesos, 0);
	memcpy(&nbdLocal,(unsigned int *)resp->arguments, sizeof(unsigned int));
	memcpy(&nbdServidor,(unsigned int *)resp->arguments, sizeof(unsigned int));
	cout << "nbd inicializado " << nbdLocal << endl;
	cout << "Haciendo " << nVeces << " deposito de " << pesos << " pesos." << endl;

	for(int i = 0 ; i < nVeces ; i++) {
    	cout << "\nDeposito " << i+1 << " de " << pesos << " pesos iniciado" << endl;
		nbdLocal += pesos;

		resp = (struct Mensaje *)cl.doOperation(ip , puerto, 2, (char *)&pesos, i + 1);
		memcpy(&nbdServidor,(unsigned int *)resp->arguments, sizeof(unsigned int));

		cout << "Deposito recibido" << endl;
		cout << "\tTipo: " << resp->messageType << endl;
		cout << "\tId: " << resp->requestId << endl;
		cout << "\tOperacion: " << resp->operationId << endl;
		cout << "\tSaldo actual: " << nbdServidor << endl;
		

		if(nbdLocal != nbdServidor) {
			cout << "Inconsistencia de BD" << endl;
			cout << "En peticion " << resp->requestId << ", BD => Local(" << nbdLocal << ") vs (" << nbdServidor << ")" << endl;
			exit(-3);
		}
	}

	return 0;
}
