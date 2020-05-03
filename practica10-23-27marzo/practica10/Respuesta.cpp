#include "SocketDatagrama.h"
#include "Respuesta.h"

Respuesta::Respuesta(int pl) {
	socketlocal = new SocketDatagrama(pl);

}

struct mensaje* Respuesta::getRequest() {

	PaqueteDatagrama paq(sizeof(mensaje));
	socketlocal->recibe(paq);
	palabras = (struct mensaje*) paq.obtieneDatos();
	cout << "ID de opercion: " <<  palabras->operationId << endl;
	cout << "Argumentos recibidos: " <<  palabras->arguments << endl;
	cout << "Desde IP: " << palabras->IP << endl;
	cout << "Mensaje tipo: " << palabras->messageType << endl;
	palabras->puerto = paq.obtienePuerto();
	memcpy(palabras->IP,paq.obtieneDireccion(),16);
	cout << "Puerto: " << palabras->puerto << endl;
	return palabras;
}

void Respuesta::sendReply(char * respuesta, char * ipCliente, int puertoCliente) {

	struct mensaje *m1;
	m1 = (struct mensaje *) respuesta;
	cout<< "***********************************\n";
	cout << "Preparando respuesta: " << m1->arguments << endl;
	cout << "IP Cliente: " << ipCliente << endl;
	cout << "puerto Cliente: " << puertoCliente << endl;
	PaqueteDatagrama paq((char*) m1, 100, ipCliente, puertoCliente);
	cout << "Paquete de datos: " << paq.obtieneDatos() << endl;
	cout << "Paquete IP: " << paq.obtieneDireccion() << endl;
	socketlocal->envia(paq);
	cout<<"************************************\n";
}
