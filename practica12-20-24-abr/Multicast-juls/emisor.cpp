#include <iostream>
#include "SocketMulticast.h"
#include "mensaje.h"
#include <cstring>

using namespace std;


// static const char * GROUP = "127.0.0.1";


int main(int argc, char **argv) {


	char *ipm;
    int puerto = 0;
    unsigned char ttl;
    char * arrc;

	if(argc == 5) {
		ipm = argv[1];
		puerto = atoi(argv[2]);
		ttl = (unsigned char *)argv[3];
        arrc = argv[4];
	} else {
		cout << "Ingrese el comando de forma correcta" << endl;
		cout << "\t ./emisor <IP Multicast> <puerto> <TTL> <cadena>";
		exit(-2);
	}



    SocketMulticast multicast(0); // Puerto para envio multicast

    int arr[2] = {2,7};

    PaqueteDatagrama paquete(arr, sizeof(arr), ipm, puerto);

    multicast.envia(paquete, ttl);
    
    cout << arr[0] << ", " << arr[1] << endl;

    auto vec = multicast.recibe();

    for (auto & p : vec) {
        int suma = *(int *)p.obtieneDatos();

        cout << p.obtieneDireccion() << ", suma : " << suma << endl;
    }

    return 0;
}
