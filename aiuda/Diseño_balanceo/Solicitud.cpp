#include "Solicitud.h"
#include "mensaje.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

Solicitud::Solicitud(){
	socketlocal=new SocketDatagrama(0);

}

char* Solicitud::doOperation(char *IP, int puerto, int operation, char *arguments){
	
	mensaje *msg=new mensaje;

	msg->messageType=0;
int n,j;

	memcpy(msg->arguments,arguments,TAM_MAX_DATA);
	msg->requestId=id;
	msg->operationId=operation;
		PaqueteDatagrama *paquete=new PaqueteDatagrama((char*)msg,(unsigned int)sizeof(mensaje),IP,puerto);
		//cout<<paquete->obtieneDireccion()<<endl;
		//cout<<paquete->obtienePuerto()<<endl;
	
	
	n=socketlocal->envia(*paquete);
	
	if(n>0){
		//cout<<"Mensaje enviado"<<endl;
	}else{
		//cout<<"Mensaje no enviado"<<endl;
	}

for(int i=0;i<7;i++){
	j=socketlocal->recibeTimeout(*paquete,2,500000);
//cout<<j<<endl;
	if(j>0){

		mensaje* respuesta=(mensaje*)paquete->obtieneDatos();
		//printf("ServidoID=%u ClienteID=%u\n",respuesta->requestId,id);
		if(respuesta->requestId!=id){
			return doOperation(IP,puerto,operation,arguments);
		}else{
			id++;
		}
		//cout<<"Respuesta: "<<atoi(respuesta->arguments)<<endl;
		//cout<<id<<endl;
		return respuesta->arguments;
		
	}
	n=socketlocal -> envia(*paquete);




	}
	cout<<"Servidor no disponible, intentelo mas tarde"<<endl;
	exit(0);

}