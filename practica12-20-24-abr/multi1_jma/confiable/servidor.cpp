#include <stdio.h>
#include <stdlib.h>         // atoi
#include <string.h>           // len
#include <string>           // tostring
using namespace std;

#include "Respuesta.h"

char* realiza_op(struct mensaje *msj);

int main(int argc, char *argv[]) {
    char *ip = argv[1];
    int puerto = atoi(argv[2]);
    char *resultado;

    Respuesta res = Respuesta(atoi(argv[2]), ip);

    struct mensaje *msj_recibir;

    printf("\n\tReceptor iniciado\n");

    while(1) {
        msj_recibir = res.getRequest();
        resultado = realiza_op(msj_recibir);
        res.sendReply(resultado);
    }

    return 0;
}

char* realiza_op(struct mensaje *msj) {
    int indice, ires;
    char *cres;
    char *args = msj->arguments;

    for (int i=0 ; i<strlen(args) ; i++) {
        if (args[i]==' ') {
            indice = i;
            break;
        }
    }

    char num1[indice+1], num2[strlen(args)-indice+1];

    memcpy(num1, args, indice);
    memcpy(num2, args+indice+1, strlen(args)-indice);

    num1[indice] = 0;
    num2[strlen(args)-indice] = 0;

    if (msj->operationId==1) {
        ires = atoi(num1) + atoi(num2);
    }

    string aux = to_string(ires);
    cres = new char[aux.size()+1];
    memcpy(cres, aux.c_str(), aux.size());
    cres[aux.size()] = '\0';

    return cres;
}

