#ifndef __SocketDatagrama__
#define __SocketDatagrama__

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include "PaqueteDatagrama.h"
#include <arpa/inet.h>
#include <fstream>
#include <errno.h>
#include <sys/time.h>

class SocketDatagrama{

public:
    SocketDatagrama(int puerto, struct timeval);
    ~SocketDatagrama();
    int recibeTimeout(PaqueteDatagrama & p, time_t segundos, suseconds_t microsegundos);
    int envia(PaqueteDatagrama & p);
private:
    int s;
    struct sockaddr_in direccionLocal;
    struct sockaddr_in direccionForanea;
	struct timeval timeoutSocket;
};

#endif
