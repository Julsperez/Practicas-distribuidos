#ifndef __mensaje__
#define __mensaje__

#define TAM_MAX_DATA 3500

struct mensaje {
    int messageType;        //0 = Solicitud, 1 = Respuesta
    unsigned int requestId; //Identificador del mensaje
    char IP[16];
    int puerto;
    int lengthBytes;
    int operationId;        //Identificador del mensaje
    char arguments[TAM_MAX_DATA];
	int calidad;
};

#endif
