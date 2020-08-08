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
	
	struct Mensaje *resp = (struct Mensaje *)cl.doOperation(ip , puerto,1,(char *)&pesos, 0);
	memcpy(&nbdLocal,(unsigned int *)resp->arguments, sizeof(unsigned int));
	memcpy(&nbdServidor,(unsigned int *)resp->arguments, sizeof(unsigned int));
	cout << "nbd recibido: " << nbdLocal << endl;
	cout << "\nHaciendo " << nVeces << " deposito de " << pesos << endl;

	for(int i = 0 ; i < nVeces ; i++) {
		cout << "\nDeposito no: " << i + 1  << " de " << pesos << endl;
		nbdLocal += pesos;
		struct Mensaje *resp = (struct Mensaje *)cl.doOperation(ip , puerto,2,(char *)&pesos, i + 1);
		memcpy(&nbdServidor,(unsigned int *)resp->arguments, sizeof(unsigned int));
		cout << "nbd recibido: " << nbdServidor << endl;
		if(nbdLocal != nbdServidor) {
			cout << "Inconcistencia de BD" << endl;
			exit(-3);
		}
	}

	return 0;
}