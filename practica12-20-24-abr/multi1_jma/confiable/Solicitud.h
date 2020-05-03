#ifndef _SOLICITUD_H_
#define _SOLICITUD_H_

#include "SocketMulticast.h"

class Solicitud {
    private:
        SocketMulticast *socketlocal;
    public:
        Solicitud();
        char* doOperation(char *IP, int puerto, int operationId, int requestId, char *argumnts);
};

#endif