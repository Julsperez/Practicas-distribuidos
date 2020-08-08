#ifndef PAQUETEDATAGRAMA_H_
#define PAQUETEDATAGRAMA_H_

#include <netinet/in.h>


class PaqueteDatagrama{
    char *datos = nullptr; //Almacena los datos
    struct in_addr IP; //Almacena la IP
    unsigned int _longitud = 0; //Almacena la longitude de la cadena de datos


public:
    int puerto;
    const unsigned int & longitud = _longitud;


    PaqueteDatagrama();
    PaqueteDatagrama(void * data, unsigned int size, const char * ip, int port);
    //PaqueteDatagrama(unsigned int size);
    PaqueteDatagrama(const PaqueteDatagrama & rhs);
    PaqueteDatagrama(PaqueteDatagrama && ths) noexcept ;
    ~PaqueteDatagrama();

    char *obtieneDireccion();
    char *obtieneDatos();
    void inicializaIP(const char *ip);
    void inicializaDatos(void *data, size_t size);

    PaqueteDatagrama & operator=(PaqueteDatagrama const &rhs);
    PaqueteDatagrama & operator=(PaqueteDatagrama && ths) noexcept ;

};

#endif