#include "SocketDatagrama.h"
#include "Solicitud.h"
#include "mensaje.h"

Solicitud::Solicitud(struct timeval timeout) {
	timeoutSocket = timeout;
	socketlocal = new SocketDatagrama(0,timeout);
}

char * Solicitud::doOperation(char* IP, int puerto, int operationId, char* arguments) {
	struct mensaje msj;
	char aux[100];
	char* resultado;
	int res;
	unsigned int id, registros = atoi(arguments); // id de 0 a 65535
	cout << "Registros " << registros << endl;
	FILE *f = fopen("votos.txt", "r+");
	if (f==NULL) {
		cout << "Error al abrir el archivo votos.txt" << endl;
		exit(-1);
	}
	id = 0;
	for(int i=0;i<registros;i++){
		msj.messageType = 0;
		msj.requestId = id;
		//id++;
		memcpy(msj.IP, IP, 16);
		msj.puerto = puerto;
		msj.operationId = operationId;
		//cout << "Id operacion: " << msj.operationId << endl;
		//cout << "ip: " << msj.IP << endl;
		fgets(msj.arguments, 100, f);
		cout << msj.arguments;
		//memcpy(msj.arguments, arguments, 4000);
		//cout << "puerto: " << msj.puerto << endl;
		//cout << "argumentos: " << msj.arguments << endl;
		PaqueteDatagrama paq((char*) &msj, sizeof(msj), IP, puerto);
		socketlocal->envia(paq);
		PaqueteDatagrama paq1(sizeof(msj));
		res = socketlocal->recibeTimeout(paq1,timeoutSocket.tv_sec,timeoutSocket.tv_usec);
		if(res>=0){
			resultado  = paq1.obtieneDatos();
			cout << "resultado: " << resultado << endl;
			id++;
		} else {
			cout << "No se pudo conectar al servidor :(, reenviado paquete..." << endl;
			while (1) {
				PaqueteDatagrama paqReenvio((char*)&msj, sizeof(msj), IP, puerto);
				socketlocal->envia(paqReenvio);
				PaqueteDatagrama acuse(sizeof(msj));
				res = socketlocal->recibeTimeout(acuse,timeoutSocket.tv_sec,timeoutSocket.tv_usec);
				if(res >0 ){
					cout << "resultado: " << acuse.obtieneDatos() << endl;
					break;
				}
			}
			id++;
		}
		//cout<<"Resultado: " <<res <<endl;
		/*if(res>=0){
			resultado = paq1.obtieneDatos();
			break;
		}*/
	}
	fclose(f);


	return resultado;
}
