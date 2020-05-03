#include "SocketDatagrama.h"
#include "Solicitud.h"
#include "mensaje.h"

Solicitud::Solicitud() {
	
}

char * Solicitud::doOperation(char* IP, int puerto, int operationId, char* arguments) {
	struct mensaje msj;
	char* resultado;
	int res;
	for(int i=0;i<1;i++){	
		msj.messageType = 0;
		msj.requestId = id;
		id++;
		memcpy(msj.IP, IP, 16);
		msj.puerto = puerto;
		msj.operationId = operationId;	
		//cout << "Id operacion: " << msj.operationId << endl;
		//cout << "ip: " << msj.IP << endl;
		memcpy(msj.arguments, arguments, 4000);
		//cout << "puerto: " << msj.puerto << endl;
		//cout << "argumentos: " << msj.arguments << endl;
		PaqueteDatagrama paq((char*) &msj, sizeof(msj), IP, puerto);
		socketlocal->envia(paq);
		PaqueteDatagrama paq1(sizeof(msj));
		res = socketlocal->recibe(paq1);
		//cout<<"Resultado: " <<res <<endl;
		/*if(res>=0){
			resultado = paq1.obtieneDatos();
			break;
		}*/
	}	
	if(res>=0)
		cout << "resultado: 12\n" << endl;
	else
		cout << "No se pudo conectar al servidor :(" << endl;

	return res;
}
