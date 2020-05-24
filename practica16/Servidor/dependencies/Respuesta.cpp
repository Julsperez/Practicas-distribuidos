#include "SocketDatagrama.h"
#include "Respuesta.h"

Respuesta::Respuesta(int pl, struct timeval timeout) {
	timeoutSocket = timeout;
	socketlocal = new SocketDatagrama(pl, timeout);

}

struct mensaje* Respuesta::getRequest() {
	PaqueteDatagrama paq(sizeof(mensaje));
	socketlocal->recibeTimeout(paq,timeoutSocket.tv_sec,timeoutSocket.tv_usec);
	message = (struct mensaje*) paq.obtieneDatos();
	message->puerto = paq.obtienePuerto();
	memcpy(message->IP,paq.obtieneDireccion(),16);
	cout << "Peticion de: "<< message->IP <<" puerto:" << message->puerto << " IdOp:" << message->operationId << endl;
	cout << "msgType: " << message->messageType << "reqId: " << message->requestId << " Data: " <<  message->arguments << endl;
	return message;
}

void Respuesta::sendReply(char * respuesta, char * ipCliente, int puertoCliente) {
	struct mensaje *m1;
	m1 = (struct mensaje *) respuesta;
	PaqueteDatagrama paq((char*) m1, 100, ipCliente, puertoCliente);
	socketlocal->envia(paq);
	// cout<<"\n--- Respuesta enviada ";
}
