#include "SocketDatagrama.h"

using namespace std;

SocketDatagrama::SocketDatagrama(int puerto){
	s = socket(AF_INET, SOCK_DGRAM, 0);
   //socket(dominio, tipo, protocolo)

   /* se asigna una direccion al socket del servidor*/
   bzero((char *)&direccionLocal, sizeof(direccionLocal));
   direccionLocal.sin_family = AF_INET;
   direccionLocal.sin_addr.s_addr = INADDR_ANY;
   direccionLocal.sin_port = htons(puerto);

   bind(s, (struct sockaddr *)&direccionLocal, sizeof(direccionLocal));
}

SocketDatagrama::~SocketDatagrama(){
	close(s);
}

int SocketDatagrama::recibe(PaqueteDatagrama &paquete){
	char datos[paquete.obtieneLongitud()];
   char aux[INET_ADDRSTRLEN];
   socklen_t clilen = sizeof(direccionForanea);
   int i = recvfrom(s, datos, paquete.obtieneLongitud(), 0, (struct sockaddr *) &direccionForanea, &clilen);
   inet_ntop(AF_INET, &(direccionForanea.sin_addr), aux, INET_ADDRSTRLEN);
   paquete.inicializaPuerto(ntohs(direccionForanea.sin_port));
   paquete.inicializaIp(aux);
   paquete.inicializaDatos(datos);
	return i; 
}

int SocketDatagrama::envia(PaqueteDatagrama &paquete){
   bzero((char *)&direccionForanea, sizeof(direccionForanea));
   direccionForanea.sin_family = AF_INET;
   direccionForanea.sin_addr.s_addr = inet_addr(paquete.obtieneDireccion());
   direccionForanea.sin_port = htons(paquete.obtienePuerto());
	
	return sendto(s, paquete.obtieneDatos(), paquete.obtieneLongitud(), 0, (struct sockaddr *) &direccionForanea, sizeof(direccionForanea));
}