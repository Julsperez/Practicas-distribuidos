#include "mensaje.h"
#include "Solicitud.h"
#include <iostream>

Solicitud::Solicitud() {
    socketlocal = new SocketMulticast(0);
}

char* Solicitud::doOperation(char *IP, int puerto, int opId, int reqId, char *args) {
    int n;
    struct mensaje msj_enviar, *msj_recibir;

    msj_enviar.messageType = 0;
    msj_enviar.operationId = opId;
    msj_enviar.requestId = reqId;
    bzero(msj_enviar.arguments, 4000);
    memcpy(msj_enviar.arguments, args, sizeof(char)*4000);

    PaqueteDatagrama paquete_enviar((char*)&msj_enviar, sizeof(msj_enviar), IP, puerto), paquete_recibir(sizeof(msj_enviar));

    printf("\n\tDatos enviados \
            \n\t\tIP: %s \
            \n\t\tPuerto: %d \
            \n\t\tMensaje: %s.\n", paquete_enviar.obtieneDireccion(), paquete_enviar.obtienePuerto(), msj_enviar.arguments);

    socketlocal->envia(paquete_enviar, 1);
}