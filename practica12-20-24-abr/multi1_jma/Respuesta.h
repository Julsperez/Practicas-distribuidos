#ifndef RESPUESTA_H_
#define RESPUESTA_H_

#include "SocketMulticast.h"
#include "mensaje.h"

class Respuesta {
    private:
        SocketMulticast *socketlocal;
    public:
        Respuesta(int pl, char*);
        struct mensaje *getRequest();
        // void sendReply(char *respuesta, unsigned int ndb);
};

#endif