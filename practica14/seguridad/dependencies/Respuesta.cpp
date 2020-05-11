#include "SocketDatagrama.h"
#include "Respuesta.h"

Respuesta::Respuesta(int pl, struct timeval timeout) {
	timeoutSocket = timeout;
	socketlocal = new SocketDatagrama(pl, timeout);

}

struct mensaje* Respuesta::getRequest() {

	PaqueteDatagrama paq(sizeof(mensaje));
	socketlocal->recibeTimeout(paq,timeoutSocket.tv_sec,timeoutSocket.tv_usec);
	palabras = (struct mensaje*) paq.obtieneDatos();
	palabras->puerto = paq.obtienePuerto();
	memcpy(palabras->IP,paq.obtieneDireccion(),16);
	// Request info
	// cout << "Peticion de: "<< palabras->IP <<" puerto:" << palabras->puerto << " IdOp:" << palabras->operationId << endl;
	// cout << "Type: " << palabras->messageType << " Data: " <<  palabras->arguments << endl;
	return palabras;
}

void Respuesta::sendReply(char * respuesta, char * ipCliente, int puertoCliente) {

	struct mensaje *m1;
	m1 = (struct mensaje *) respuesta;
	PaqueteDatagrama paq((char*) m1, 100, ipCliente, puertoCliente);
	socketlocal->envia(paq);
	cout<<"Request answered...\n";
}
