#include "SocketDatagrama.h"
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <netdb.h>
#include <strings.h>

using namespace std;

SocketDatagrama::SocketDatagrama(int puertoL)
{
   s = socket(AF_INET, SOCK_DGRAM, 0);
   bzero((char *)&direccionLocal, sizeof(struct sockaddr_in));
   bzero((char *)&direccionForanea, sizeof(struct sockaddr_in));      
   direccionLocal.sin_family = AF_INET;
   direccionLocal.sin_addr.s_addr = INADDR_ANY;
   direccionLocal.sin_port = htons(puertoL);
   bind(s, (struct sockaddr *)&direccionLocal,sizeof(direccionLocal)); //bind solo es util para recibir   

}

SocketDatagrama::~SocketDatagrama()
{
   close(s);
}

//Recibe un paquete tipo datagrama proveniente de este socket
int SocketDatagrama::recibe(PaqueteDatagrama & p)
{
   int retorno;
   socklen_t clilen; //Ojo no compila si es un tipo int en C
   
   clilen = sizeof(direccionForanea);
   retorno = recvfrom(s, (char *) p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *)&direccionForanea, &clilen);
	//printf("\n%d",retorno);
   p.inicializaPuerto(ntohs(direccionForanea.sin_port));
   p.inicializaIp(inet_ntoa(direccionForanea.sin_addr));
   
   return retorno;
}

//Envía un paquete tipo datagrama desde este socket
int SocketDatagrama::envia(PaqueteDatagrama & p)
{  int envio;
   
   direccionForanea.sin_family = AF_INET;
   direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
   direccionForanea.sin_port = htons(p.obtienePuerto());
   envio  = sendto(s, (char *)p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *) &direccionForanea, sizeof(direccionForanea));
  
   return envio;
}

  int SocketDatagrama::recibeTimeout(PaqueteDatagrama &p,time_t segundos,suseconds_t microsegundos){

  	int retorno;
  	timeout.tv_sec=segundos;
  	timeout.tv_usec=microsegundos;
   socklen_t clilen; //Ojo no compila si es un tipo int en C
   setsockopt(s,SOL_SOCKET,SO_RCVTIMEO,(char*)&timeout,sizeof(timeout));
   clilen = sizeof(direccionForanea);
   retorno = recvfrom(s, (char *) p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *)&direccionForanea, &clilen);
   if(retorno<0){
   	if(errno==EWOULDBLOCK)
   		fprintf(stderr, "Tiempo para recepcion transcurrido\n");
   		else{

   			fprintf(stderr, "Error en recvfrom\n" );
   			return -1;
   		}
   	
   }
   p.inicializaPuerto(ntohs(direccionForanea.sin_port));
   p.inicializaIp(inet_ntoa(direccionForanea.sin_addr));
   
   return retorno;

  }
