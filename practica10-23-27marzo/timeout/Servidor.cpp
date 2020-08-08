#include <cstdlib>
#include <iostream> 
#include <string> 
#include "Respuesta.h"

using namespace std;

char * suma (char * data) {
  string return_data (" "), word;
  size_t size_data = strlen(data);
  int val1, res = 0;
  for (size_t i = 0;i < size_data+1;i++)
  {
    unsigned char c = data[i];
    switch (c)
    {
      default:
        word += c;
        break;
      case '\0':
      case '\n':
      case ' ':
        if(!word.empty ())
        {
          val1 = stoi(word);
		  res = res + val1;
          word.clear();
        }
        break;
    }
  }
  return_data = std::to_string(res);
  char * resp = (char*)malloc (return_data.size());
  memcpy (resp,return_data.c_str(),return_data.size());
  return resp;
}


int main(int argc, char const *argv[]) {
	cout<<argv[1]<<endl;
	Respuesta respuesta(atoi(argv[1]));

	while(1) {
	struct mensaje msj;
    struct mensaje m1;
    
	cout << "\nEsperando conexion : " << endl;
	memcpy(&msj, respuesta.getRequest(), sizeof(struct mensaje));

    //cout << "Estos son los argumentos antes de la operacion: " << msj.arguments << endl;
		//cout << "id: " << msj.operationId << endl;
		//cout<< "IP: " <<msj.IP<<endl;
		switch(msj.operationId) {
			case 1:
				//cout << "Id encontrado :  1" << endl;
				//cout << "Los argumentos son : " << msj.arguments << endl;
				memcpy(m1.arguments, suma(msj.arguments), strlen(msj.arguments));
				m1.messageType = 1;
				memcpy(m1.IP, msj.IP, 16);//------------------
				m1.puerto = msj.puerto;
				m1.requestId = msj.requestId;
				respuesta.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
				//cout << "Fin del servicio" << endl;
				break;
			default:
				//cout << "Error en el numero de operación" << endl;
				//cout << "numero: " << msj.operationId << endl;
				exit(-1);
		}
	}


	return 0;
}