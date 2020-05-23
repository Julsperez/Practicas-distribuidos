#include "SocketDatagrama.h"
#include "Respuesta.h"

Respuesta::Respuesta(int pl) {
	socketlocal = new SocketDatagrama(pl);
}

struct mensaje* Respuesta::getRequest() {
	PaqueteDatagrama paq(TAM_MAX_DATA);
	socketlocal->recibe(paq);
	msj = (struct mensaje*) paq.obtieneDatos();
	msj->puerto = paq.obtienePuerto();
	//cout << "->" << msj->lengthBytes << endl;
	//cout << "-->" << msj->operationId << endl;
	memcpy(msj->IP,paq.obtieneDireccion(),16);
	return msj;
}

void Respuesta::sendReply(char * respuesta, char * ipCliente, int puertoCliente, int lengthBytes) {
	struct mensaje *m1;
	m1 = (struct mensaje *) respuesta;
	PaqueteDatagrama paq((char*) m1, sizeof(struct mensaje), ipCliente, puertoCliente, lengthBytes);
	socketlocal->envia(paq);
}
