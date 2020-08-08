#include "SocketMulticast.h"

struct ip_mreq{
	struct in_addr imr_multiaddr; /* Dirección IP del grupo multicast */
	struct in_addr imr_interface; /* Dirección IP de la interfaz local IP */
};

SocketMulticast::SocketMulticast(int puerto, unsigned char TTL)
{
    //s = socket(AF_INET, SOCK_DGRAM, 0);
	s = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(s < 0 ){
		cout<<"ERROR: no se pudo crear el socket"<<endl;
		exit(1);
	}
	
}

SocketMulticast::~SocketMulticast()
{
    close(s);
}


int SocketMulticast::recibe(PaqueteDatagrama & p)
{
    unsigned int addr_len = sizeof(direccionForanea);
    bzero((char *)&direccionForanea, sizeof(direccionForanea));
    int regreso = recvfrom(s,p.obtieneDatos(),p.obtieneLongitud(), 0, (struct sockaddr *) &direccionForanea, &addr_len);
    
    p.inicializaPuerto(ntohs(direccionForanea.sin_port));
    p.inicializaIp(inet_ntoa(direccionForanea.sin_addr));
    //std::cout << "Mensaje recibido de: " << inet_ntoa(direccionForanea.sin_addr) << ":" << ntohs(direccionForanea.sin_port) << std::endl;
    //std::cout << "Puerto: " << p.obtienePuerto() << endl;
    //std::cout << "IP: " << p.obtieneDireccion() << endl;
    return regreso;
}

int SocketMulticast::envia(PaqueteDatagrama & p, unsigned char ttl)
{
	unsigned char TTL = ttl;
    int resultado = setsockopt(s, IPPROTO_IP, IP_MULTICAST_TTL, (void *) &TTL, sizeof(TTL));
	if(resultado < 0 ){
		cout<<"EROR: no se pudo establecer TTL"<<endl;
		exit(1);
	}

    bzero((char *)&direccionForanea, sizeof(direccionForanea));
    direccionForanea.sin_family = AF_INET;
    direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
    direccionForanea.sin_port = htons(p.obtienePuerto());
    
    return sendto(s,p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *) &direccionForanea, sizeof(direccionForanea));
}

void SocketMulticast::unirseGrupo(char * ipMulticast){
	struct ip_mreq multicast;
	multicast.imr_multiaddr.s_addr = inet_addr(ipMulticast);
	multicast.imr_interface.s_addr = htonl(INADDR_ANY);
	setsockopt(s, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *) &multicast, sizeof(multicast))
}

void SocketMulticast::salirseGrupo(char * ipMulticast){
	struct ip_mreq multicast;
	multicast.imr_multiaddr.s_addr = inet_addr(ipMulticast);
	multicast.imr_interface.s_addr = htonl(INADDR_ANY);
	setsockopt(s, IPPROTO_IP, IP_DROP_MEMBERSHIP, (void *) &multicast, sizeof(multicast))
}


