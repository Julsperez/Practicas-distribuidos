#ifndef __Solicitud__
#define __Solicitud__

#include "SocketDatagrama.h"
#include <iostream>
#include <cstring>

using namespace std;

class Solicitud {
    
public:
    Solicitud();
    char * doOperation(char *IP, int puerto, int operationId, char *arguments, int length, int calidad);
    
private:
    SocketDatagrama *socketlocal;
    unsigned int id = 1;
};

#endif
