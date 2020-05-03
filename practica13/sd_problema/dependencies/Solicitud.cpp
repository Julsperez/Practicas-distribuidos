#include "SocketDatagrama.h"
#include "Solicitud.h"
#include "mensaje.h"

Solicitud::Solicitud() {
	//timeoutSocket = timeout;
	socketlocal = new SocketDatagrama(0);
}

char * Solicitud::doOperation(char* IP, int puerto, int operationId, char* arguments) {
	struct mensaje msj;
	char* resultado;
	int res = 0;

	msj.messageType = 0;
	msj.requestId = id;
	id++;
	memcpy(msj.IP, IP, 16);
	msj.puerto = puerto;
	msj.operationId = operationId;
	memcpy(msj.arguments, arguments, strlen(arguments)+1);
	PaqueteDatagrama paq((char*) &msj, sizeof(msj), IP, puerto);
	socketlocal->envia(paq);
	PaqueteDatagrama paq1(sizeof(msj));
	res = socketlocal->recibe(paq1);
	resultado = paq1.obtieneDatos();

	if(res>=0)
		cout << "Respuesta obtenida" << endl;
	else
		cout << "Sin conexion con el servidor" << endl;

	return resultado;
}
