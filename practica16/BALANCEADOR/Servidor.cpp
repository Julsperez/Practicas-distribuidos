#include <cstdlib>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <sys/time.h>
#include "Respuesta.h"
#include <unistd.h>
#include <thread>
#include "Solicitud.h"

#define numServidores 3
using namespace std;

void envioSolicitud(char *ipAenviar, struct mensaje msj, Respuesta res){
	cout << "[ Envio de la peticion al servidor ] " <<indiceIPServidor <<endl;
	struct timeval timeout;
  	timeout.tv_sec = 2;
  	timeout.tv_usec = 500000;
	char *ip = ipAenviar;
	int puerto = 9999;
	int operacion = 2;
	Solicitud cliente = Solicitud(timeout);
	char *respuesta = cliente.doOperation(ip, puerto, operacion, msj.arguments);
	struct timeval tv;
    gettimeofday(&tv,NULL);
	string segundos = std::to_string(tv.tv_sec);
	string microsec = std::to_string(tv.tv_usec);
	char tmbuf[64];
	char tmbuf2[64];
	strcpy(tmbuf,segundos.c_str());
	fflush(f);
	strcpy(tmbuf2,microsec.c_str());
	fflush(f);
	struct mensaje m1;
	memcpy(m1.arguments, respuesta, strlen(respuesta)+1);
	m1.messageType = 1;
	memcpy(m1.IP, msj.IP, 16);
	m1.puerto = msj.puerto;
	m1.requestId = msj.requestId;
	cout << "[ Envio de la respuesta al cliente ] " <<endl;
	res.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
}

int main(int argc, char const *argv[]) {
	int carga[numServidores];
	long int idAnterior = -1;
	struct timeval timeout;
  	timeout.tv_sec = 100;
  	timeout.tv_usec = 500000;
	Respuesta respuesta(atoi(argv[1]),timeout);
  	char confirmacion[] = "Solicitud procesada";
	cout << "[ Configurando balanceador de carga ] " << endl;
	for(int index=0; index<numServidores; index++)
		carga[index] = 0;
	cout << "[ Servidor iniciado ] " << endl;
	
	while(1) {
	struct mensaje msj;
  	struct mensaje m1;
	cout << "[ Esperando conexion ]" << endl;
	cout << "[ ID del mensaje que se espera : " <<(idAnterior+1)  <<" ]" << endl;
	memcpy(&msj, respuesta.getRequest(), sizeof(struct mensaje));
	cout << "[ Mensaje recibido ]" << endl;
		switch(msj.operationId){
			case 1:
				cout << "[ BALANCEADOR ]" << endl;
				if(msj.requestId > idAnterior){
					int indiceIPServidor = 0;
					int historicoCarga = 0;
					for(int i=0; i<numServidores; i++){
						if(i==0 && carga[i]==0){
							indiceIPServidor = 0;
							break;
						}else{
							historicoCarga = carga[i];
						}
						if(carga[i]>=historicoCarga){
							historicoCarga = carga[i];
							indiceIPServidor = i;
						}
					}
					carga[indiceIPServidor] = carga[indiceIPServidor] + 1;
					switch(indiceIPServidor){
						case 0:
							const char *ipAenviar = "192.168.28.91";
							break;
						case 1:
							const char *ipAenviar = "192.168.32.23";
							break;
						case 2:
							const char *ipAenviar = "192.168.43.54";
							break;
						default:
							const char *ipAenviar = "192.168.28.91";
							break;
					}
					thread th1(envioSolicitud, ipAenviar, msj, respuesta);
					th1.join();
					idAnterior = msj.requestId;
				} else if(msj.requestId == idAnterior) {					
					memcpy(m1.arguments, confirmacion, strlen(confirmacion)+1);
					m1.messageType = 1;
					memcpy(m1.IP, msj.IP, 16);
					m1.puerto = msj.puerto;
					m1.requestId = msj.requestId;
					respuesta.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
				} else {
					memcpy(m1.arguments, confirmacion, strlen(confirmacion)+1);
					m1.messageType = 1;
					memcpy(m1.IP, msj.IP, 16);
					m1.puerto = msj.puerto;
					m1.requestId = msj.requestId;
					respuesta.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
				}
				break;
			case 2:
				cout << "[ SERVIDOR ]" << endl;
				memcpy(m1.arguments, confirmacion, strlen(confirmacion)+1);
				m1.messageType = 1;
				memcpy(m1.IP, msj.IP, 16);
				m1.puerto = msj.puerto;
				m1.requestId = msj.requestId;
				respuesta.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
				break;
			default:
				cout << "[ Error en el numero de operación ]" << endl;
				cout << "[ Numero de operacion enviado: " <<msj.operationId <<" ]" << endl;
				exit(-1);
		}
	}
	return 0;
}