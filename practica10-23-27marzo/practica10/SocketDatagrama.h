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
    SocketDatagrama(int puerto);
    ~SocketDatagrama();
    int recibe(PaqueteDatagrama & p);
    int envia(PaqueteDatagrama & p);
private:
    struct sockaddr_in direccionLocal;
    struct sockaddr_in direccionForanea;
    int s;
};

#endif
