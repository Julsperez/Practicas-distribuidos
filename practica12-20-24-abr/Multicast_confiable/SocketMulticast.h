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
        struct timeval timeout;
	static int id_msn;
	struct mensajes msn_almacenados[500];
    
	public:
        SocketMulticast(int); //done
        ~SocketMulticast(); //done
        int recibe(PaqueteDatagrama & p); //maybe
        int recibeTimeout(PaqueteDatagrama &p, time_t segundos, suseconds_t microsegundos); //maybe
        int envia(PaqueteDatagrama & p, unsigned int ttl); //maybe
        void unirseGrupo(char *); //maybe
        void salirseGrupo(char *); //maybe
	int enviaConfiable(PaqueteDatagrama & p, unsigned int ttl, int num_receptores);
	int recibeConfiable(PaqueteDatagrama & p);
	int obtenerIdMensaje();  ///static??? done
};


#endif
