using namespace std;

#include "SocketMulticast.h"
#include <errno.h>          // errno
#include <iostream>         // exit

int SocketMulticast::id_msn = 0;

SocketMulticast::SocketMulticast(int _puerto) {
    s = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    int reuse = 1;
    if (setsockopt(s, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) == -1) {
        printf("Error al llamar a la función setsockopt\n");
        exit(0);
    } 

    bzero((char*)&direccionLocal, sizeof(direccionLocal));
    direccionLocal.sin_family = AF_INET;
    direccionLocal.sin_addr.s_addr = INADDR_ANY;
    direccionLocal.sin_port = htons(_puerto);

    bind(s, (struct sockaddr*) &direccionLocal, sizeof(direccionLocal));
}

int SocketMulticast::~SocketMulticast(){
	close(s);
}

int SocketMulticast::obtenerIdMensaje(){
	return id_msn;
}

int SocketMulticast::recibeConfiable(PaqueteDatagrama & p){

	unsigned int clilen = sizeof(direccionForanea);
	int n = recvfrom(s, datos, p.obtieneLongitud(), 0, (struct sockaddr *)&direccionForanea, &clilen);

	bzero(p.obtieneDireccion(), 16);
	p.inicializaIp(inet_ntoa(direccionForanea.sin_addr));
	p.inicializaPuerto(ntohs(direccionForanea.sin_port));

	struct mensaje msn_recibido;

	memcpy(&msn_recibido, p.obtieneDatos(), p.obtieneLongitud());
	
	printf("Id del mensaje: %d\n", msn_recibido.requestId);
	printf("Mensaje: %d\n", *(int *)msn_recibido.arguments);

	memcpy(p.obtieneDatos(), msn_recibido.arguments, sizeof(msn_recibido.arguments) / sizeof(msn_recibido.arguments[0]));
	p.inicializaLongitud(sizeof(msn_recibido.arguments) / sizeof(msn_recibido.arguments[0]));

	//Comparacion del id de mensaje local y foraneo	
	if(msn_recibido.requestId == id_msn){
		printf("Los id de mensaje empatan: %d\n", id_msn);

		struct mensaje msn_ack;
		msn_ack.
	


}

int SocketMulticast::enviaConfiable(PaqueteDatagrama & p, unsigned int ttl, int num_receptores){

}


int SocketMulticast::recibe(PaqueteDatagrama &p){
    char datos[p.obtieneLongitud()];
    unsigned int clilen = sizeof(direccionForanea);

    recvfrom(s, datos, p.obtieneLongitud(), 0, (struct sockaddr *)&direccionForanea, &clilen);

    p.inicializaIp(inet_ntoa(direccionForanea.sin_addr));
    p.inicializaPuerto(ntohs(direccionForanea.sin_port));
    p.inicializaDatos(datos);

    return 0;
}

int SocketMulticast::recibeTimeout(PaqueteDatagrama &p, time_t segundos, suseconds_t microsegundos) {
    char datos[p.obtieneLongitud()];
    unsigned int clilen = sizeof(direccionForanea);

    timeout.tv_sec = segundos;
    timeout.tv_usec = microsegundos;
    setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));

    int n = recvfrom(s, datos, p.obtieneLongitud(), 0, (struct sockaddr *)&direccionForanea, &clilen);

    if (n < 0) {
        if (errno == EWOULDBLOCK)
            fprintf(stderr, "\t\t** Tiempo para recepción transcurrido\n");
        else
            fprintf(stderr, "\t\t** Error en recvfrom\n");
    } else {
        p.inicializaIp(inet_ntoa(direccionForanea.sin_addr));
        p.inicializaPuerto(ntohs(direccionForanea.sin_port));
        p.inicializaDatos(datos);
    }

    return n;
}

int SocketMulticast::envia(PaqueteDatagrama &p, unsigned int TTL) {
    if (p.obtienePuerto()>-1) {
        bzero((char*)&direccionForanea, sizeof(direccionForanea));
        direccionForanea.sin_family = AF_INET;
        direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
        direccionForanea.sin_port = htons(p.obtienePuerto());
    }
    
    setsockopt(s, IPPROTO_IP, IP_MULTICAST_TTL, (void *) &TTL, sizeof(TTL));
    sendto(s, p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr*)&direccionForanea, sizeof(direccionForanea));

    return 0;
}

void SocketMulticast::unirseGrupo(char *ip) {
    struct ip_mreq multicast;
    multicast.imr_multiaddr.s_addr = inet_addr(ip);
    multicast.imr_interface.s_addr = htonl(INADDR_ANY);
    setsockopt(s, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *) &multicast, sizeof(multicast));
}

void SocketMulticast::salirseGrupo(char *ip) {
    struct ip_mreq multicast;
    multicast.imr_multiaddr.s_addr = inet_addr(ip);
    multicast.imr_interface.s_addr = htonl(INADDR_ANY);
    setsockopt(s, IPPROTO_IP, IP_DROP_MEMBERSHIP, (void *) &multicast, sizeof(multicast));
}

