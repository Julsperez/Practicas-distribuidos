#ifndef __Solicitud__
#define __Solicitud__

#include "SocketDatagrama.h"
#include <iostream>
#include <vector>

using namespace std;

class Solicitud {
    
public:
    Solicitud(struct timeval);
    // char * doOperation(char *IP, int puerto, int operationId, vector<string> votes );
    char * doOperation(char *IP, int puerto, int operationId, char *arguments);
    
private:
    SocketDatagrama *socketlocal;
    unsigned int id = 1;
	struct timeval timeoutSocket;
};

#endif
