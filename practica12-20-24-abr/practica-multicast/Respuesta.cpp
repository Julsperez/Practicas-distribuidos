#include "Respuesta.h"

Respuesta::Respuesta(int pl, char *ip) {
    socketlocal = new SocketMulticast(pl);
    socketlocal->unirseGrupo(ip);
}

struct mensaje* Respuesta::getRequest() {
    struct mensaje *msj_recibir, aux;
    PaqueteDatagrama paquete_recibir(sizeof(aux));

    socketlocal->recibe(paquete_recibir);
    msj_recibir = (struct mensaje*)paquete_recibir.obtieneDatos();

    printf("\n\tDatos recibidos \
            \n\t\tIP: %s \
            \n\t\tPuerto: %d \
            \n\t\tMensaje: %s.\n", paquete_recibir.obtieneDireccion(), paquete_recibir.obtienePuerto(), msj_recibir->arguments);

    return msj_recibir;
}