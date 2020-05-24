#include "SocketDatagrama.h"
#include "Solicitud.h"
#include "mensaje.h"

Solicitud::Solicitud(struct timeval timeout) {
	timeoutSocket = timeout;
	socketlocal = new SocketDatagrama(0,timeout);
}

// takes votes as arguments
char * Solicitud::doOperation(char* IP, int puerto, int operationId, char* arguments, int id) {
	struct mensaje msj;
	char* result;
	int response;
	
	cout<<"Sending message to: ["<<IP<<":"<<puerto<<"]"<<endl;
	// Preparing message
	msj.messageType = 0;
	msj.requestId = id;
	memcpy(msj.IP, IP, 16);
	msj.puerto = puerto;
	msj.operationId = operationId;
	memcpy(msj.arguments, arguments, 4000); // arguments = voteBuffer = vote string

	// send message
	PaqueteDatagrama package((char*) &msj, sizeof(msj), IP, puerto);
	socketlocal->envia(package);
	PaqueteDatagrama package1(sizeof(msj));
	response = socketlocal->recibeTimeout(package1,timeoutSocket.tv_sec,timeoutSocket.tv_usec);
	if(response >= 0){
		result  = package1.obtieneDatos();
		cout <<"Server result: " << result <<endl;
	} else {
		cout << "Could not connect, fowarding message..." << endl;
		while (1) {
			PaqueteDatagrama packFowrd((char*)&msj, sizeof(msj), IP, puerto);
			socketlocal->envia(packFowrd);
			PaqueteDatagrama acuse(sizeof(msj));
			response = socketlocal->recibeTimeout(acuse,timeoutSocket.tv_sec,timeoutSocket.tv_usec);
			if(response >0 ){
				cout << "Server response: " << acuse.obtieneDatos() <<endl;
				break;
			}
		}
	}
	
	cout<<"Message sent [ok]";
	return result;
}
