#include "SocketDatagrama.h"
#include "Solicitud.h"
#include "mensaje.h"

Solicitud::Solicitud(struct timeval timeout) {
	timeoutSocket = timeout;
	socketlocal = new SocketDatagrama(0,timeout);
}

char * Solicitud::doOperation(char* IP, int puerto, int operationId, char* arguments) {
	struct mensaje msj;
	char* resultado;
	int res;
	int numEnvios = 1;
	int id = 0;
	for(int i=0 ; i<numEnvios; i++){
		cout<<"[ Comenzando el envio de paquete(s) ]"<<endl;
		msj.messageType = 0;
		msj.requestId = id;
		memcpy(msj.IP, IP, 16);
		msj.puerto = puerto;
		msj.operationId = operationId;
		memcpy(msj.arguments, arguments, 4000);
		PaqueteDatagrama paq((char*) &msj, sizeof(msj), IP, puerto);
		socketlocal->envia(paq);
		PaqueteDatagrama paq1(sizeof(msj));
		res = socketlocal->recibeTimeout(paq1,timeoutSocket.tv_sec,timeoutSocket.tv_usec);
		if(res>=0){
			resultado  = paq1.obtieneDatos();
			cout <<"[Respuesta del servidor: " <<resultado <<"]" <<endl;
			id++;
		} else {
			cout << "No se pudo conectar al servidor :(, reenviado el paquete..." << endl;
			while (1) {
				PaqueteDatagrama paqReenvio((char*)&msj, sizeof(msj), IP, puerto);
				socketlocal->envia(paqReenvio);
				PaqueteDatagrama acuse(sizeof(msj));
				res = socketlocal->recibeTimeout(acuse,timeoutSocket.tv_sec,timeoutSocket.tv_usec);
				if(res >0 ){
					cout << "[ Respuesta del servidor: " <<acuse.obtieneDatos() <<" ]" <<endl;
					break;
				}
			}
			id++;
		}
	}
	cout<<"[ Envio completo ]";
	return resultado;
}
