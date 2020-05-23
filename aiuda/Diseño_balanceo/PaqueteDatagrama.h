#ifndef PAQUETEDATAGRAMA_H_
#define PAQUETEDATAGRAMA_H_

class PaqueteDatagrama {
public:
   //cadena (datos), longitud de la cadena, dirección IP y el puerto. 
   PaqueteDatagrama(char *, unsigned int , char *, int );
   //mensaje vacío de una longitud determinada para la recepción.
   PaqueteDatagrama(unsigned int);
   ~PaqueteDatagrama();
   char * obtieneDireccion();
   unsigned int obtieneLongitud();
   int obtienePuerto();
   char *obtieneDatos();
   void inicializaPuerto(int);
   void inicializaIp(char *);
   void inicializaDatos(char *);
private:
   char *datos;            //Almacena los datos
   char ip[16];            //Almacena la IP
   unsigned int longitud;  //Almacena la longitude de la cadena de datos
   int puerto;             //Almacena el puerto
};

#endif
