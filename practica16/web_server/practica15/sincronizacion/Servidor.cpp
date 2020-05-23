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

void enviarServer(char *ipServer, struct mensaje msj, Respuesta res){
	struct timeval timeout;
  	timeout.tv_sec = 2;
  	timeout.tv_usec = 500000;
	char *ip = ipServer;
	int puerto = 2407;
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
	cout << "Respondiendo a cliente" <<endl;
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
						if((phone[9]-'0')%2!=0 || phone[9]=='0' /*|| phone[9]=='0'*/){
							// cout<<"Enviando al servidor 1"<<endl;
							ipServerIndex = 0;
						} else {
							// cout<<"Enviando al servidor 2"<<endl;
							ipServerIndex = 1;
						}
					}
					carga[ipServerIndex] = carga[ipServerIndex] + 1;
					switch(ipServerIndex){
						case 0:
							const char *ipServer = "192.168.28.91";
							break;
						case 1:
							const char *ipServer = "192.168.32.23";
							break;
						default:
							const char *ipServer = "192.168.28.91";
							break;
					}
					thread th1(envioSolicitud, ipServer, msj, respuesta);
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
				cout << "Procesamiento" << endl;
				memcpy(m1.arguments, confirmacion, strlen(confirmacion)+1);
				m1.messageType = 1;
				memcpy(m1.IP, msj.IP, 16);
				m1.puerto = msj.puerto;
				m1.requestId = msj.requestId;
				respuesta.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
				break;
			default:
				cout << "Error de operacion" << endl;
				exit(-1);
		}
	}
	return 0;
}