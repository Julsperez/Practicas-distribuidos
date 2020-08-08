#ifndef SOCKETMULTICAST_H_
#define SOCKETMULTICAST_H_

#include <string.h>         // bzero
#include <arpa/inet.h>      // struct sockaddr_in
#include <unistd.h>         // close
#include <stdio.h>          // printf

using namespace std;

#include "PaqueteDatagrama.h"

class SocketMulticast{
    private:
        int s; //ID socket
        struct sockaddr_in direccionLocal;
        struct sockaddr_in direccionForanea;
    public:
        SocketMulticast(int);
        ~SocketMulticast();
        int recibe(PaqueteDatagrama & p);
        int envia(PaqueteDatagrama & p, unsigned int ttl);
        void unirseGrupo(char *);
        void salirseGrupo(char *);
};

// class SocketDatagrama {
//     private:
//         struct sockaddr_in direccionLocal;
//         struct sockaddr_in direccionForanea;
//         int s;                                  // ID socket
//         struct timeval timeout;
//     public:
//         SocketDatagrama(int);
//         ~SocketDatagrama();
//         int recibe(PaqueteDatagrama &p);        // Recibe un paquete tipo datagrama proveniente de este socket
//         int envia(PaqueteDatagrama &p);         // Envia un paquete tipo datagrama desde este socket
//         int recibeTimeout(PaqueteDatagrama &p, time_t segundos, suseconds_t microsegundos);
// };

#endif