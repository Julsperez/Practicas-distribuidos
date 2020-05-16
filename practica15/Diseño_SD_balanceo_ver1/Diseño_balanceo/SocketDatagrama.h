#ifndef SOCKETDATAGRAMA_H_
#define SOCKETDATAGRAMA_H_

#include "PaqueteDatagrama.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

class SocketDatagrama{
public:
   SocketDatagrama(int); // puerto local no se podrá cambiar para el proceso. Si es cero lo asigna el SO
   ~SocketDatagrama();
   //Recibe un paquete tipo datagrama proveniente de este socket
   int recibe(PaqueteDatagrama & p);
   //Envía un paquete tipo datagrama desde este socket
   int envia(PaqueteDatagrama & p);
   //Recibe un paquete en un tiempo determinado
   int recibeTimeout(PaqueteDatagrama &p,time_t segundos,suseconds_t microsegundos);
private:   
   struct sockaddr_in direccionLocal;
   struct sockaddr_in direccionForanea;
   struct timeval timeout;
   int s; //ID socket
};

#endif

