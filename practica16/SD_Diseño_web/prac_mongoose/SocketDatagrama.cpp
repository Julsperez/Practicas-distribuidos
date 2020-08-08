#include "SocketDatagrama.h"


SocketDatagrama::SocketDatagrama(int puerto, struct timeval timeout)
{
	timeoutSocket = timeout;
    s = socket(AF_INET, SOCK_DGRAM, 0);
	setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeoutSocket, sizeof(timeoutSocket));
    bzero((char *)&direccionLocal, sizeof(direccionLocal));	
    direccionLocal.sin_family = AF_INET;
    direccionLocal.sin_addr.s_addr = INADDR_ANY;
    direccionLocal.sin_port = htons(puerto);
    bind(s, (struct sockaddr *)&direccionLocal,sizeof(direccionLocal));
}

SocketDatagrama::~SocketDatagrama()
{
    //close(s);
}

int SocketDatagrama::setBroadcast()
{
    int yes = 1;
    return setsockopt(s, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(int));
}

int SocketDatagrama::recibeTimeout(PaqueteDatagrama & p, time_t segundos, suseconds_t microsegundos)
{
    unsigned int addr_len = sizeof(direccionForanea);
    bzero((char *)&direccionForanea, sizeof(direccionForanea));
    int response = recvfrom(s,p.obtieneDatos(),p.obtieneLongitud(), 0, (struct sockaddr *) &direccionForanea, &addr_len);
    if (response < 0) {
        if (errno == EWOULDBLOCK)
            fprintf(stderr, "Socket timeout...\n");
        else
            fprintf(stderr, "Internal socket error\n");
    }
    /* cout <<  */p.inicializaPuerto(ntohs(direccionForanea.sin_port));
    /* cout <<  */p.inicializaIp(inet_ntoa(direccionForanea.sin_addr));
    // cout <<"response: "<< response<< endl;
    return response;
}


int SocketDatagrama::envia(PaqueteDatagrama & p)
{
    bzero((char *)&direccionForanea, sizeof(direccionForanea));
    direccionForanea.sin_family = AF_INET;
    direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
    direccionForanea.sin_port = htons(p.obtienePuerto());
    
    return sendto(s,p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *) &direccionForanea, sizeof(direccionForanea));
}


