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
	char aux[100];
	unsigned int id, registros = atoi(arguments);
	
	cout << "Registros: " << registros << endl;
	FILE *f = fopen("7kvotes.txt", "r+");
	if (f==NULL) {
		cout << "Error al abrir el archivo de votos" << endl;
		exit(-1);
	}

	id = 0;
	for(int i=0;i<registros;i++){
		msj.messageType = 0;
		msj.requestId = id;
		memcpy(msj.IP, IP, 16);
		msj.puerto = puerto;
		msj.operationId = operationId;
		fgets(msj.arguments, 100, f);
		
		cout<<"Arguments:" << msj.arguments;

		PaqueteDatagrama paq((char*) &msj, sizeof(msj), IP, puerto);
		socketlocal->envia(paq);
		PaqueteDatagrama paq1(sizeof(msj));
		res = socketlocal->recibeTimeout(paq1,timeoutSocket.tv_sec,timeoutSocket.tv_usec);
		if(res>=0){
			resultado  = paq1.obtieneDatos();
			cout << "resultado: " << resultado << endl;
			id++;
		} else {
			cout << "Server error, reenviado paquete..." << endl;
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
