#ifndef __SocketMulticast__
#define __SocketMulticast__

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include "PaqueteDatagrama.h"
#include <arpa/inet.h>

class SocketMulticast{

public:
    SocketMulticast(int = 0);
    SocketMulticast(int puerto, unsigned char TTL);
    ~SocketMulticast();
    int recibe(PaqueteDatagrama & p);
    int envia(PaqueteDatagrama & p, unsigned char ttl);
	//Se une a un grupo multicast, recibe la IP multicast
	void unirseGrupo(char *);
	//Se sale de un grupo multicast, recibe la IP multicast
	void salirseGrupo(char *);
private:    
    int s;
	struct sockaddr_in direccionLocal;
    struct sockaddr_in direccionForanea;
};

#endif
