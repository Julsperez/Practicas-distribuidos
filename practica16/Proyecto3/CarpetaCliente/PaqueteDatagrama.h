#ifndef __PaqueteDatagrama__
#define __PaqueteDatagrama__

#include <iostream>
#include <cstring>

using namespace std;

class PaqueteDatagrama {
    
public:
    PaqueteDatagrama(char *, unsigned int, char *, int, int);
    PaqueteDatagrama(unsigned int );
    ~PaqueteDatagrama();
    char *obtieneDireccion();
    unsigned int obtieneLongitud();
    int obtienePuerto();
    char *obtieneDatos();
    void inicializaPuerto(int);
    void inicializaIp(char *);
    void inicializaDatos(char *);
    int obtieneLengthBytes();
    void inicializaLengthBytes(int);
    
private:
    char *datos;
    char ip[16];
    unsigned int longitud;
    int puerto;
    int lengthBytes;
};
#endif
