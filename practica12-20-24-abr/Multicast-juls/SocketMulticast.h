#ifndef PR12_SOCKETMULTICAST
#define PR12_SOCKETMULTICAST

#include <vector>
#include "PaqueteDatagrama.h"
#include "mensaje.h"

class SocketMulticast{
public:
    SocketMulticast(unsigned int port);
    ~SocketMulticast();

    std::vector<PaqueteDatagrama> recibe();
    // int recibeConfiable(PaqueteDatagrama & p);

    int envia(PaqueteDatagrama & p, unsigned char ttl);
    // int enviaConfiable(PaqueteDatagrama & p, unsigned char ttl, int num_receptores);

    int recibeTimeout(PaqueteDatagrama &p, time_t segundos, suseconds_t microsegundos);

    //Se une a un grupo multicast, recibe la IP multicast
    void unirseGrupo(const char * multicastIP);
    //Se sale de un grupo multicast, recibe la IP multicast
    void salirseGrupo(const char * multicastIP);
    //int getID() const { return s; }

private:
    int multicast, unicast; //ID socket
    struct sockaddr_in direccionLocal;
    struct sockaddr_in direccionForanea;
    bool emisor;

    fd_set fds;
    Mensaje mensaje{};
};


#endif //PR12_SOCKETMULTICAST
