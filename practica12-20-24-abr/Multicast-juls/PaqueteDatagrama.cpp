#include "PaqueteDatagrama.h"
#include <cstring>
#include <arpa/inet.h>
#include <utility>

using namespace std;

PaqueteDatagrama::PaqueteDatagrama(void *data, unsigned int size, const char * ip, int port) {
    datos = new char[size];
    std::memcpy(datos, data, size);

    _longitud = size;
    puerto = port;
    inicializaIP(ip);
}

PaqueteDatagrama::PaqueteDatagrama() {
    puerto = 0;
    inicializaIP("");
}

PaqueteDatagrama::PaqueteDatagrama(const PaqueteDatagrama &rhs) {
    _longitud = rhs._longitud;

    datos = new char[_longitud];
    memcpy(datos, rhs.datos, _longitud);

    puerto = rhs.puerto;
    IP = rhs.IP;
}

PaqueteDatagrama::PaqueteDatagrama(PaqueteDatagrama &&ths) noexcept  {
    std::swap(datos, ths.datos);

    _longitud = ths.longitud;
    puerto = ths.puerto;
    IP = ths.IP;
}

/*PaqueteDatagrama::PaqueteDatagrama(unsigned int size) {
    datos = new char[size];
    _longitud = size;

    puerto = 0;
    inicializaIP("");
}*/

PaqueteDatagrama::~PaqueteDatagrama(){
	delete[] datos;
}

char* PaqueteDatagrama::obtieneDireccion() {
    return inet_ntoa(IP);
}

char* PaqueteDatagrama::obtieneDatos() {
   return datos;
}

void PaqueteDatagrama::inicializaIP(const char* ip) {
    IP.s_addr = inet_addr(ip);
}

void PaqueteDatagrama::inicializaDatos(void* data, size_t size) {
    delete datos;

    _longitud = size;
    datos = new char[size];
    std::memcpy(datos, data, size);
}

PaqueteDatagrama& PaqueteDatagrama::operator=(PaqueteDatagrama const &rhs) {
    delete[] datos;

    datos = new char[rhs.longitud];
    std::memcpy(datos, rhs.datos, rhs.longitud);

    _longitud = rhs.longitud;
    puerto = rhs.puerto;
    IP = rhs.IP;

    return *this;
}

PaqueteDatagrama& PaqueteDatagrama::operator=(PaqueteDatagrama &&ths) noexcept {
    std::swap(datos, ths.datos);

    _longitud = ths.longitud;
    puerto = ths.puerto;
    IP = ths.IP;

    return *this;
}