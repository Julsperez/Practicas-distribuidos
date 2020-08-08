#include "SocketMulticast.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <cerrno>
#include <iostream>

static const size_t MAX_BUFFER_SIZE = sizeof(Mensaje);

SocketMulticast::SocketMulticast(unsigned int port) {
    emisor = !port;

    multicast = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    unicast = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

    int reuse = 1;
    if (setsockopt(multicast, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) == -1) {
        printf("Error al llamar a la función setsockopt\n");
        exit(0);
    }
    if (setsockopt(unicast, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) == -1) {
        printf("Error al llamar a la función setsockopt\n");
        exit(0);
    }
    if (setsockopt(multicast, SOL_SOCKET, SO_REUSEADDR, (char*) &reuse, sizeof(reuse)) < 0) {
        perror("Reusing ADDR failed");
        exit(0);
    }
    if (setsockopt(unicast, SOL_SOCKET, SO_REUSEADDR, (char*) &reuse, sizeof(reuse)) < 0) {
        perror("Reusing ADDR failed");
        exit(0);
    }
    if (port) {
        bzero((char *) &direccionLocal, sizeof(direccionLocal));
        direccionLocal.sin_family = AF_INET;
        direccionLocal.sin_addr.s_addr = htonl(INADDR_ANY);
        direccionLocal.sin_port = htons(port);
        bind(multicast, (struct sockaddr *) &direccionLocal, sizeof(direccionLocal));
    }
    FD_ZERO(&fds);
    FD_SET(unicast, &fds);
    FD_SET(multicast, &fds);
}

SocketMulticast::~SocketMulticast() {
    shutdown(multicast, SHUT_RDWR);
    shutdown(unicast, SHUT_RDWR);
}

std::vector<PaqueteDatagrama> SocketMulticast::recibe() {
    std::vector<PaqueteDatagrama> vector;
    PaqueteDatagrama resp;
    char *buffer = new char[MAX_BUFFER_SIZE];

    unsigned int lData = sizeof(direccionForanea);

    if (emisor) {
        struct timeval tv{};
        tv.tv_sec = 2;

        int ret;
        while ((ret = select(multicast+1, &fds, nullptr, nullptr, &tv)) > 0) {
            int longitud = recvfrom(multicast, buffer, MAX_BUFFER_SIZE, 0, (struct sockaddr *)&direccionForanea, &lData);
            resp.inicializaDatos(buffer, longitud);
            resp.inicializaIP(inet_ntoa(direccionForanea.sin_addr));
            resp.puerto = ntohs(direccionForanea.sin_port);
            vector.push_back(resp);
        }
        if(ret < 0) {
            std::cout << "Error recibe(): select()" << std::endl;
        }

    } else {
        select(multicast+1, &fds, nullptr, nullptr, nullptr);
        int longitud = recvfrom(multicast, buffer, MAX_BUFFER_SIZE, 0, (struct sockaddr *)&direccionForanea, &lData);
        //std::cout << "recibido : " << longitud << " emisor: " << emisor << std::endl;
        resp.inicializaDatos(buffer, longitud);
        resp.inicializaIP(inet_ntoa(direccionForanea.sin_addr));
        resp.puerto = ntohs(direccionForanea.sin_port);
        vector.push_back(resp);
    }
    delete[] buffer;
    return vector;
}

int SocketMulticast::envia(PaqueteDatagrama &p, unsigned char TTL) {
    int enviado;
    if (emisor) {
        setsockopt(multicast, IPPROTO_IP, IP_MULTICAST_TTL, &TTL, sizeof(TTL));
    }
    direccionForanea.sin_family = AF_INET;
    direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
    direccionForanea.sin_port = htons(p.puerto);

    unsigned int lData = sizeof(direccionForanea);
    enviado = sendto(emisor ? multicast : unicast, p.obtieneDatos(), p.longitud, 0, (struct sockaddr *)&direccionForanea, lData);
    //std::cout << "enviado : " << enviado << ", longitud: " << p.longitud << " emisor: " << emisor << std::endl;
    return enviado;
}

// int SocketMulticast::enviaConfiable(PaqueteDatagrama &p, unsigned char TTL, int num_receptores) {
//     //init header
//     memcpy(mensaje.arguments, p.obtieneDatos(), p.longitud);
//     mensaje.size = p.longitud;

//     PaqueteDatagrama aux(&mensaje, sizeof(Mensaje), p.obtieneDireccion(), p.puerto);

//     envia(aux, TTL);


//     auto vec = recibe();

//     if (vec.size() != num_receptores) {
//         std::cout << "Error: algun mensaje se perdio" << std::endl;
//         return -1;
//     }

//     for (auto & ack : vec) {
//         unsigned int ack_id = *(unsigned int *)ack.obtieneDatos();

//         if (ack_id != mensaje.requestId + 1) {
//             std::cout << "Error: mensaje no recibido, " << ack.obtieneDireccion() << std::endl;

//             return -1;
//         }
//     }

//     mensaje.requestId++;

//     return 0;
// }

// int SocketMulticast::recibeConfiable(PaqueteDatagrama &p) {
//     //recibe(p);

//     Mensaje aux{};
//     memcpy(&aux, p.obtieneDatos(), sizeof(Mensaje));

//     if (aux.requestId != mensaje.requestId) {
//         return -1;
//     }

//     mensaje.requestId++;

//     PaqueteDatagrama resp(&mensaje.requestId, sizeof(mensaje.requestId), p.obtieneDireccion(), p.puerto);
//     envia(resp, 0);

//     p.inicializaDatos(aux.arguments, aux.size);

//     return 0;
// }

int SocketMulticast::recibeTimeout(PaqueteDatagrama &p, time_t segundos, suseconds_t microsegundos) {
    int respuesta;

    struct timeval timeout{};
    timeout.tv_sec = segundos;
    timeout.tv_usec = microsegundos;

    setsockopt(multicast, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

    unsigned int lData = sizeof(direccionForanea);
    respuesta = recvfrom(multicast, p.obtieneDatos(), p.longitud, 0, (struct sockaddr *)&direccionForanea, &lData);

    if (respuesta < 0) {
        if (errno == EWOULDBLOCK) {
            std::cout << stderr << ": Timeout" << std::endl;

        } else {
            std::cout << stderr << ": recvfrom error" << std::endl;
        }
    }

    char str[INET_ADDRSTRLEN];
    auto* ip = (struct sockaddr_in*)&direccionForanea;
    struct in_addr ipAdd = ip->sin_addr;
    inet_ntop(AF_INET, &ipAdd, str, INET_ADDRSTRLEN);
    p.inicializaIP(inet_ntoa(direccionForanea.sin_addr));
    p.puerto = ntohs(direccionForanea.sin_port);

    return respuesta;
}

void SocketMulticast::unirseGrupo(const char * multicastIP) {
    struct ip_mreq multicast_str{};

    multicast_str.imr_multiaddr.s_addr = inet_addr(multicastIP);
    multicast_str.imr_interface.s_addr = htonl(INADDR_ANY);

    setsockopt(multicast, IPPROTO_IP, IP_ADD_MEMBERSHIP, &multicast_str, sizeof(multicast_str));
}

void SocketMulticast::salirseGrupo(const char * multicastIP) {
    struct ip_mreq multicast_str{};

    multicast_str.imr_multiaddr.s_addr = inet_addr(multicastIP);
    multicast_str.imr_interface.s_addr = htonl(INADDR_ANY);

    setsockopt(multicast, IPPROTO_IP, IP_DROP_MEMBERSHIP, &multicast_str, sizeof(multicast_str));
}