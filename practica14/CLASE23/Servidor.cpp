#include <cstdlib>
#include <iostream>
#include <string>
#include "./dependencies/Respuesta.h"
#include <stdlib.h>
#include <vector>
#include <sys/time.h>

using namespace std;

struct timeval timeNow;

struct timeval getTimeOfDay() {
	struct timeval timestamp;
	return timestamp;	
}

int main(int argc, char const *argv[]) {
	struct timeval timeout;
	timeout.tv_sec = 100;
	timeout.tv_usec = 500000;
	long int expected =0, prev = -1;

	Respuesta respuesta(atoi(argv[1]),timeout);
	char confirmacion[] = "Registro guardado en bd servidor.";
	
	std::vector<string> v;

	while(1) {
		struct mensaje msj;
	 	struct mensaje m1;

	 	FILE *archivo = NULL;
	  	archivo = fopen(argv[2], "a+");
	  	if (archivo == NULL) {
	    	cout << "Server error: No se encontro el archivo " << argv[2] << endl;
	    	break;
	  	}
  
		cout << "\nEscuchando: "<< expected << ":"<< endl;
	  	//Request info
		memcpy(&msj, respuesta.getRequest(), sizeof(struct mensaje));

		const string zeros = "0000000000000000";
	  	string igual = zeros;

		switch(msj.operationId) {
			case 1:
				if(msj.requestId == expected){
					struct timeval tv;
    				gettimeofday(&tv,NULL);
					//const char *time_datails = NULL;
					//struct timeval aux;
					//struct tm *nowtm;
					// char tmbuf[64];
					char tmbuf2[64];
					//aux.tv_usec = getTimeOfDay().tv_usec;
					//cout << aux.tv_usec;
					//nowtm = localtime(&aux.tv_usec);
					//size_t sz = strftime(tmbuf, sizeof tmbuf, "%Y-%m-%d %H:%M:%S", nowtm);
					//sprintf(tmbuf,"%lu",sz);
					// string s = tmbuf;
					//strcat(msj.arguments,s);
					string segundos = std::to_string(tv.tv_sec);
					string microsec = std::to_string(tv.tv_usec);
	
					// char linea[1024];
					bool existe = false;
					// string copia;
					// int count_aux = 0;
    				// for (int i = 0; i < strlen(msj.arguments); i++) { 
       	// 				copia = copia + msj.arguments[i]; 
    				// }
    				
    				// FILE *f = fopen(argv[2], "w+");
  					// if (f == NULL) {
    					// cout << "Error al abrir el archivo (SERVIDOR)" << endl;
  					// }


					
  					if(v.empty()) {
	  					v.push_back(msj.arguments);
	  					strcpy(tmbuf2,segundos.c_str());
						fflush(archivo);
						fputs(tmbuf2,archivo);
						cout << "writing: " << tmbuf2 <<endl;

						// fflush(archivo);
						strcpy(tmbuf2,microsec.c_str());
						fflush(archivo);
						fputs(tmbuf2,archivo);
						cout << "writing-2: " << tmbuf2 <<endl;
						
						fflush(archivo);
						fputs(" ",archivo);
						fputs(msj.arguments,archivo);

	  				} 
	  				else {
	  					// cp arguments aux
	  					string aux;
	  					for (int i = 0; i < strlen(msj.arguments); i++)
	       					aux = aux + msj.arguments[i];

	       				// instead of binary_search
	  					for (std::size_t i = 0; i < v.size(); i++) {
	  						if(aux.substr(18,27) == v[i].substr(18,27)){
	  							igual = v[i].substr(1,16);
	  							existe = true;
	  							break;
	  						}
	  					}
	  				}


  					if(existe == false) {
						strcpy(tmbuf2,segundos.c_str());
						fflush(archivo);
						fputs(tmbuf2,archivo);
  						cout << "writing: " << tmbuf2 <<endl;
						// cout << tmbuf2 <<endl;
						strcpy(tmbuf2,microsec.c_str());
						fflush(archivo);
						fputs(tmbuf2,archivo);
						cout << "writing-2: " << tmbuf2 <<endl;
						// cout << tmbuf2 <<endl; 
						// fflush(archivo);
						fflush(archivo);
						fputs(" ",archivo);
						fputs(msj.arguments,archivo);				
  					}
					
					fclose(archivo);
				

					prev = expected;
					expected++;

					m1.messageType = 1;
					m1.puerto = msj.puerto;
					m1.requestId = msj.requestId;
					memcpy(m1.arguments, confirmacion, strlen(confirmacion)+1);
					memcpy(m1.IP, msj.IP, 16);

					if (igual == zeros) {
						respuesta.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
					} else {
						memcpy(m1.arguments, igual.c_str(),strlen(igual.c_str())+1);
						respuesta.sendReply(m1.arguments,m1.IP, msj.puerto);	
					}
				}

				else if(msj.requestId == prev) {
					fclose(archivo);
					m1.messageType = 1;
					m1.puerto = msj.puerto;
					m1.requestId = msj.requestId;
					memcpy(m1.arguments, confirmacion, strlen(confirmacion)+1);
					memcpy(m1.IP, msj.IP, 16);
					respuesta.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
				} else {
					// Caso en que los id son anteriores
					fclose(archivo);
					cout << "Action ignored" << endl;
					m1.messageType = 1;
					m1.puerto = msj.puerto;
					m1.requestId = msj.requestId;
					memcpy(m1.arguments, confirmacion, strlen(confirmacion)+1);
					memcpy(m1.IP, msj.IP, 16);
					respuesta.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
				}
			break;
			
			default:
				cout << "Server error: No existe operacion " << msj.operationId  << ", conexion ignorada."<< endl;
		}
	}
	return 0;
}