#include "SocketDatagrama.h"
#include "Solicitud.h"
#include "mensaje.h"

Solicitud::Solicitud(struct timeval timeout) {
	timeoutSocket = timeout;
	socketlocal = new SocketDatagrama(0,timeout);
	
}

// takes votes as arguments
char * Solicitud::doOperation(char* IP, int puerto, int operationId, char* arguments, int idx) {
	struct mensaje msj;
	char* result;
	int response;
	unsigned int id = idx;
	cout<<"Sending message to: ["<<IP<<":"<<puerto<<"]"<<endl;
	cout <<"[Debugger: ARGS]> "<< operationId <<":"<< arguments <<":"<< id <<endl;
	// Preparing message
	msj.messageType = 0;
	msj.requestId = id;
	memcpy(msj.IP, IP, 16);
	msj.puerto = puerto;
	msj.operationId = operationId;
	memcpy(msj.arguments, arguments, 4000); // arguments = voteBuffer = vote string

	// send message
	// cout <<"[Debugger: msj.requestId]> "<< msj.requestId  <<endl;
	PaqueteDatagrama paq((char*) &msj, sizeof(msj), IP, puerto);
	if(socketlocal->setBroadcast() < 0){
		exit(-1);
	}
	socketlocal->envia(paq);
	PaqueteDatagrama paq1(sizeof(msj));
	response = socketlocal->recibeTimeout(paq1,timeoutSocket.tv_sec,timeoutSocket.tv_usec);
	// cout << "[Debugger: response]> "<< response <<endl;
	if(response >= 0){
		result  = paq1.obtieneDatos();
		cout <<"Server response: " << result <<endl;
	} else {
		cout << "Could not connect, fowarding message..." << endl;
		while (1) {
			PaqueteDatagrama paqRenvio((char*)&msj, sizeof(msj), IP, puerto);
			socketlocal->envia(paqRenvio);
			PaqueteDatagrama acuse(sizeof(msj));
			response = socketlocal->recibeTimeout(acuse,timeoutSocket.tv_sec,timeoutSocket.tv_usec);
			if(response >0 ){
				cout << "Server response: " << acuse.obtieneDatos() <<endl;
				break;
			}
		}
	}
	
	// cout<<"**Request done\n";
	return result;
}
