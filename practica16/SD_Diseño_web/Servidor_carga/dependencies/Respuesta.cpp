#include "SocketDatagrama.h"
#include "Respuesta.h"

Respuesta::Respuesta(int pl, struct timeval timeout) {
	timeoutSocket = timeout;
	socketlocal = new SocketDatagrama(pl, timeout);
	
}

struct mensaje* Respuesta::getRequest() {
	PaqueteDatagrama paq(sizeof(mensaje));
	if(socketlocal->setBroadcast() < 0){
		exit(-1);
	}
	socketlocal->recibeTimeout(paq,timeoutSocket.tv_sec,timeoutSocket.tv_usec);
	message = (struct mensaje*) paq.obtieneDatos();
	message->puerto = paq.obtienePuerto();
	memcpy(message->IP,paq.obtieneDireccion(),16);
	cout << "Peticion de: "<< message->IP <<" puerto:" << message->puerto << " IdOp:" << message->operationId << endl;
	cout << "msgType: " << message->messageType << " reqId: " << message->requestId << " Data: " <<  message->arguments << endl;
	return message;
}

void Respuesta::sendReply(char * respuesta, char * ipCliente, int puertoCliente) {
	struct mensaje *m1;
	m1 = (struct mensaje *) respuesta;
	PaqueteDatagrama paq((char*) m1, 4000, ipCliente, puertoCliente);
	if(socketlocal->setBroadcast() < 0){
		exit(-1);
	}
	socketlocal->envia(paq);
	// cout<<"\n--- Respuesta enviada ";
}
