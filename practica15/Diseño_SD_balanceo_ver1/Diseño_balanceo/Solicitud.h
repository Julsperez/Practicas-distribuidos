#include "SocketDatagrama.h"
#include <string.h>
#define suma 1
class Solicitud{
public:
Solicitud();
char * doOperation(char *IP, int puerto, int operationId, char *arguments);
private:
SocketDatagrama *socketlocal;
unsigned int id=0;
};