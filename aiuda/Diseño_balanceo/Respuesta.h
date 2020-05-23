
#include "SocketDatagrama.h"
#include <string.h>
class Respuesta{
public:
	Respuesta(int pl);
	struct mensaje *getRequest(void);
	void sendReply(char *respuesta);
	void sendReply2(char * respuesta,unsigned int aux);
private:
	SocketDatagrama *socketlocal;
	PaqueteDatagrama *paquete;
	unsigned int id = 0;
	unsigned int aux;

};
