#include "Respuesta.h"
#include "mensaje.h"
#include <iostream>
#include <stdio.h>
#include <cstring>

#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream> 
using namespace std;

struct registro{
	char celular[11];
	char CURP[19];
	char partido[4];
	struct timeval seguridad;
};

//struct timeval {
//	time_t tv_sec; /* segundos */
//	suseconds_t tv_usec; /* microsegundos */
//};



int main(int argc,char**argv){
	Respuesta reply=Respuesta(9000);
	int i,nbd=0;
	struct registro rg1;
	int destino=open(argv[1], O_WRONLY|O_CREAT,0666);
	//SocketDatagrama socket= SocketDatagrama(9000);

	struct timeval prueba;
	cout<<sizeof(prueba)<<endl;
	cout<<sizeof(rg1)<<endl;
	//PaqueteDatagrama paquete=PaqueteDatagrama(sizeof(rg1));
	for(;;){
		struct mensaje msg;
		memcpy(&msg,reply.getRequest(),sizeof(msg));
		gettimeofday(&prueba,NULL);
		cout<<prueba.tv_sec<<":"<<prueba.tv_usec<<endl;
		char contestacion[TAM_MAX_DATA];
		//socket.recibe(paquete);
		//memcpy(&rg1,paquete.obtieneDatos(),sizeof(rg1));
		memcpy(&rg1,msg.arguments,sizeof(rg1));
		rg1.seguridad.tv_sec = prueba.tv_sec;
		rg1.seguridad.tv_usec= prueba.tv_usec;
		cout<<rg1.celular<<":"<<rg1.CURP<<endl;
		write(destino,&rg1,sizeof(rg1));

		if(msg.operationId==suma){
			nbd=1;
			//cout<<"registro recibido: "<<endl;
		}else{
			cout<<"operationId no reconocida"<<endl;
			return -1;
		}
		sprintf(contestacion,"%d",nbd);
		reply.sendReply(contestacion);
	}
	close(destino);

	return 0;
}