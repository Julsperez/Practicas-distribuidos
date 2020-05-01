#include "SocketDatagrama.h"
#include "Respuesta.h"

Respuesta::Respuesta(int pl) {

	socketlocal = new SocketDatagrama(pl);

}

struct mensaje* Respuesta::getRequest() {

	PaqueteDatagrama paq(sizeof(mensaje));
	socketlocal->recibe(paq);
	palabras = (struct mensaje*) paq.obtieneDatos();
	cout << "El id es: " <<  palabras->operationId << endl;
	cout << "Los argumentos son: " <<  palabras->arguments << endl;
	cout << "La IP: " << palabras->IP << endl;
	cout << "El tipo es: " << palabras->messageType << endl;
	palabras->puerto = paq.obtienePuerto();
	memcpy(palabras->IP,paq.obtieneDireccion(),16);
	cout << "puerto: " << palabras->puerto << endl;
	return palabras;
}

void Respuesta::sendReply(char * respuesta, char * ipCliente, int puertoCliente) {

	struct mensaje *m1;
	m1 = (struct mensaje *) respuesta;
	cout<< "***********************************\n";
	cout << "Preparando respuesta: " << m1->arguments << endl;
	cout << "ip Cliente: " << ipCliente << endl;
	cout << "puerto Cliente: " << puertoCliente << endl;
	PaqueteDatagrama paq((char*) m1, 100, ipCliente, puertoCliente);
	cout << "paq datos: " << paq.obtieneDatos() << endl;
	cout << "paq ip: " << paq.obtieneDireccion() << endl;
	socketlocal->envia(paq);
	cout<<"************************************\n";
}
