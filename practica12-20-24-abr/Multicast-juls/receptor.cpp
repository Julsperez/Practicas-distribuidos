#include <iostream>
#include <cstring>
#include "SocketMulticast.h"
#include "mensaje.h"

using namespace std;

// static const char * group = "127.0.0.1";

// static int nbd = 0;

int main(int argc, char **argv) {

    char *ipm;
    int puerto = 0;

	if(argc == 2) {
		ipm = argv[1];
		puerto = atoi(argv[2]);
	} else {
		cout << "Ingrese el comando de forma correcta" << endl;
		cout << "\t ./emisor <IP Multicast> <puerto>";
		exit(-2);
	}

    SocketMulticast multicast(puerto); // Puerto multicast a la escucha en 7272

    multicast.unirseGrupo(ipm);

    while (true) {
        auto vec = multicast.recibe();
        auto &paquete = vec[0];

        int *arr = (int *)paquete.obtieneDatos();

        int suma = arr[0] + arr[1];

        PaqueteDatagrama resp(&suma, sizeof(suma), paquete.obtieneDireccion(), paquete.puerto);

        multicast.envia(resp, 0);

        std::cout << "respondido a " << paquete.obtieneDireccion() << ":" << paquete.puerto << std::endl;
    }
}