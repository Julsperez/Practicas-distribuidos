#include <stdio.h>
#include <stdlib.h>         // atoi
#include <string.h>           // len
#include <string>           // tostring
using namespace std;

#include "Respuesta.h"

char* realiza_op(struct mensaje *msj, int &, int &);

int main(int argc, char *argv[]) {
    char *ip = argv[1];
    int puerto = atoi(argv[2]);

    Respuesta res = Respuesta(atoi(argv[2]), ip);

    struct mensaje *msj_recibir;

    printf("\n\tReceptor iniciado\n");

    while(1) {
        msj_recibir = res.getRequest();
    }

    return 0;
}