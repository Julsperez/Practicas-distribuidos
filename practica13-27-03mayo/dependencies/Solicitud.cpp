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
	char test[] = "cadena prueba";
	int res = 0;
	//for(int i=0;i<10000;i++){
		msj.messageType = 0;
		msj.requestId = id;
		id++;
		memcpy(msj.IP, IP, 16);
		// cout << "msj.ip " << msj.IP << endl;
		msj.puerto = puerto;
		msj.operationId = operationId;
		//cout << "Id operacion: " << msj.operationId << endl;
		//cout << "ip: " << msj.IP << endl;
		memcpy(msj.arguments, arguments, strlen(arguments)+1);
		//cout << "puerto: " << msj.puerto << endl;
		//cout << "argumentos: " << msj.arguments << endl;
		PaqueteDatagrama paq((char*) &msj, sizeof(msj), IP, puerto);
		socketlocal->envia(paq);
		PaqueteDatagrama paq1(sizeof(msj));
		res = socketlocal->recibe(paq1);
		//cout<<"Resultado: " <<res <<endl;
		resultado = paq1.obtieneDatos();
	//}
	if(res>=0)
		cout << "Respuesta obtenida" << endl;
	else
		cout << "Sin conexion con el servidor" << endl;

	return resultado;
}
