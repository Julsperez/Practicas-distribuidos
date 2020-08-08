#ifndef SERVER2_MENSAJE_H
#define SERVER2_MENSAJE_H

#define TAM_MAX_DATA  4000
//Definicion de identificadores para operaciones permitidas

//#define suma 1
// Definicion del formato de mensaje
struct Mensaje {
    int messageType; //0= Solicitud, 1 = Respuesta
    int chunk;
    int parts;
    size_t size;
    unsigned int requestId = 0; //Identificador del mensaje
    int operationId; //Identificador de la operación
    char arguments[TAM_MAX_DATA];
};

#endif
