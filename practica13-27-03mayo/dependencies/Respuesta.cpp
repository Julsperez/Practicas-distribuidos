#include "SocketDatagrama.h"
#include "Respuesta.h"

Respuesta::Respuesta(int pl) {

	socketlocal = new SocketDatagrama(pl);

}

struct mensaje* Respuesta::getRequest() {

	PaqueteDatagrama paq(sizeof(mensaje));
	socketlocal->recibe(paq);
	palabras = (struct mensaje*) paq.obtieneDatos();
	palabras->puerto = paq.obtienePuerto();
	memcpy(palabras->IP,paq.obtieneDireccion(),16);
	cout << "Peticion de: "<< palabras->IP <<" puerto:" << palabras->puerto << " IdOp:" << palabras->operationId << endl;
	cout << "Type: " << palabras->messageType << " Data: " <<  palabras->arguments << endl;
	return palabras;
}

void Respuesta::sendReply(char * respuesta, char * ipCliente, int puertoCliente) {

	struct mensaje *m1;
	m1 = (struct mensaje *) respuesta;
	PaqueteDatagrama paq((char*) m1, 100, ipCliente, puertoCliente);
	// cout << "ip Cliente: " << ipCliente << endl;
	// cout << "puerto Cliente: " << puertoCliente << endl;
	// cout << "paq datos: " << paq.obtieneDatos() << endl;
	// cout << "paq ip: " << paq.obtieneDireccion() << endl;
	socketlocal->envia(paq);
	/*
		zona de correccion de errores de envio
	*/
	cout<<"\n--- Respuesta enviada ";
}
