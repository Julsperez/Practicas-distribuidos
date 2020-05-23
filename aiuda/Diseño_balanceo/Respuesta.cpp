#include "Respuesta.h"
#include "mensaje.h"
#include <iostream>
#include <stdio.h>
using namespace std;

mensaje anterior;


Respuesta::Respuesta(int o){
	socketlocal=new SocketDatagrama(o);
	paquete=new PaqueteDatagrama(sizeof(mensaje));
}

void Respuesta::sendReply(char * respuesta){
	//static unsigned int id=1;
	mensaje msg;
	msg.messageType=1;
	msg.requestId=id;
	memcpy(&msg.arguments,respuesta,TAM_MAX_DATA);
	//cout<<"Mensaje enviado: "<<atoi(msg->arguments)<<endl;
	PaqueteDatagrama pack=PaqueteDatagrama((char*)&msg,paquete->obtieneLongitud(),paquete->obtieneDireccion(),paquete->obtienePuerto());
	socketlocal->envia(pack);
	anterior = msg;
	id++;
}

struct mensaje* Respuesta::getRequest(void){
	
	for(;;){
		int n=socketlocal->recibe(*paquete);
		mensaje* msg=(mensaje*)paquete->obtieneDatos();
		//printf("Id recibido:%u\n",msg -> requestId);
		//printf("Id servidor:%u\n",id);	
		if(msg -> requestId == id){
		 aux=id;
		// printf("%u\n",aux );
		if(n>0)
			return msg;
		}else{
			sendReply2(anterior.arguments,aux);
			cout<<"Perdida de datos"<<endl;
		}
	}
}

void Respuesta::sendReply2(char * respuesta,unsigned int aux){
	//static unsigned int id=1;
	mensaje msg;
	msg.messageType=1;
	msg.requestId=aux;
	memcpy(&msg.arguments,respuesta,TAM_MAX_DATA);
	//cout<<"Mensaje enviado: "<<atoi(msg->arguments)<<endl;
	PaqueteDatagrama pack=PaqueteDatagrama((char*)&msg,paquete->obtieneLongitud(),paquete->obtieneDireccion(),paquete->obtienePuerto());
	socketlocal->envia(pack);
	anterior = msg;
	
}
