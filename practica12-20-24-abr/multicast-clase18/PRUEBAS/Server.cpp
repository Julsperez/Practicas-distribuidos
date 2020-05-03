#include "PracticalSocket.h"  // For UDPSocket and SocketException
#include <iostream>           // For cout and cerr
#include <cstdlib>            // For atoi()
#include <cstring>
#ifdef WIN32
#include <windows.h>          // For ::Sleep()
void sleep(unsigned int seconds) {::Sleep(seconds * 1000);}
#else
#include <unistd.h>           // For sleep()
#endif
#include <string> 
#include "Respuesta.h"

using namespace std;

int main(int argc, char *argv[]) {
  if ((argc < 4) || (argc > 5)) {   // Test for correct number of arguments
    cerr << "Usage: " << argv[0] 
         << " <Destination Address> <Destination Port> <Send String> [<TTL>]\n";
    exit(1);
  }

  string servAddress = argv[1];         // First arg: multicast address
  unsigned short port = atoi(argv[2]);  // Second arg: port
  char* sendString = argv[3];           // Third arg: string to echo

  unsigned char multicastTTL = 1;       // Default TTL
  if (argc == 5) {
    multicastTTL = atoi(argv[4]);       // Command-line TTL
  }

  try {
    UDPSocket sock;

    sock.setMulticastTTL(multicastTTL);

    // Repeatedly send the string to the server
    //for (;;) {
      sock.sendTo(sendString, strlen(sendString), servAddress, port);
      //sleep(3);

    //}
     //////////////////////////////////////////////////////////////
    struct timeval timeout;
  	timeout.tv_sec = 100;
  	timeout.tv_usec = 500000; 
	Respuesta respuesta(8888,timeout);

	for(int i=0; i<4; i++){
		struct mensaje msj;
    	struct mensaje m1;
    	cout << "\nEsperando conexion : " << endl;
		memcpy(&msj, respuesta.getRequest(), sizeof(struct mensaje));
		cout << msj.arguments <<" " <<msj.IP <<endl;
		//switch(msj.operationId) {
			//case 1:
				//cout << "Id encontrado :  1" << endl;
				//cout << "Los argumentos son : " << msj.arguments << endl;
				//memcpy(m1.arguments, msj.arguments, strlen(msj.arguments));
				//m1.messageType = 1;
				//memcpy(m1.IP, msj.IP, 16);//------------------
				//m1.puerto = msj.puerto;
				//m1.requestId = msj.requestId;
				//respuesta.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
				//cout << "Fin del servicio" << endl;
				//break;
			//default:
				//cout << "Error en el numero de operación" << endl;
				//cout << "numero: " << msj.operationId << endl;
				//exit(-1);
		//}
	}
	
    
	

    //cout << "Estos son los argumentos antes de la operacion: " << msj.arguments << endl;
		//cout << "id: " << msj.operationId << endl;
		//cout<< "IP: " <<msj.IP<<endl;
		
	//}
  } catch (SocketException &e) {
    cerr << e.what() << endl;
    exit(1);
  }

  return 0;
}