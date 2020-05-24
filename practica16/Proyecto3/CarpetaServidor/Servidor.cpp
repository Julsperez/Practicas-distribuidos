#include <cstdlib>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include "Respuesta.h"
#include <bits/stdc++.h> 

using namespace std;

#define TAM_MAX_DATA 3500

int main(int argc, char const *argv[]) {

  if (argc < 2) {
      //std::cerr << "Insertar lo siguiente: puerto | Nombre de archivo a enviar" << endl;
	  std::cerr << "Insertar lo siguiente: puerto" << endl;
      exit(EXIT_FAILURE);
  }

  const short puerto = atoi(argv[1]);
  const char *fileName = const_cast<char *>("capturaPantalla.png");
  Respuesta respuesta(puerto);
  struct mensaje mensajeRecibido;
  bool flag = false;
  const char* aux = "FIN"; 
  char buffer[TAM_MAX_DATA];
  char *archivoEnviar;
  std::streamsize bytesRead;	
  std::streamsize bytesWritten;
  
  //system(command);
  while(1) {
	cout << "Esperando peticion del archivo..." << endl;	
	memcpy(&mensajeRecibido, respuesta.getRequest(), sizeof(struct mensaje));
	if(mensajeRecibido.calidad == 100){
		const char *command = "scrot capturaPantalla.png -q 100";
		system(command);
	}
	else if(mensajeRecibido.calidad == 65){
		const char *command = "scrot capturaPantalla.png -q 65";
		system(command);
	}
	else{
		const char *command = "scrot capturaPantalla.png -q 1";	
		system(command);
	}
	ifstream file(fileName, std::ifstream::binary);
	if (!file) {
    	cout << "Error" << endl;
      	exit(EXIT_FAILURE);
  	}   
	
	while (!file.eof()) {
		if(flag){
			memcpy(&mensajeRecibido, respuesta.getRequest(), sizeof(struct mensaje));
		}
		file.read(buffer, sizeof(buffer));
      	bytesRead = file.gcount();
		memcpy(mensajeRecibido.arguments, buffer, bytesRead);
		respuesta.sendReply(reinterpret_cast<char *>(&mensajeRecibido.arguments), mensajeRecibido.IP, mensajeRecibido.puerto, sizeof(mensajeRecibido.arguments));
		flag = true;
	}
	cout << "Archivo enviado con exito" << endl;
	memcpy(&mensajeRecibido, respuesta.getRequest(), sizeof(struct mensaje));
	memcpy(mensajeRecibido.arguments, aux, strlen(aux));
	respuesta.sendReply(reinterpret_cast<char *>(&mensajeRecibido.arguments), mensajeRecibido.IP, mensajeRecibido.puerto, sizeof(mensajeRecibido.arguments));	
	flag = false;
	file.close();
  }

	return 0;
}
