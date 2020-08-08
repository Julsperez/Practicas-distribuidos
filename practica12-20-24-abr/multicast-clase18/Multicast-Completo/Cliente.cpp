#include "SocketMulticast.h" // For UDPSocket and SocketException
#include <iostream>          // For cout and cerr
#include <cstdlib>           // For atoi()
#include "Solicitud.h"
#include <stdlib.h>
#include <string.h>

const int MAXRCVSTRING = 255;     // Longest string to receive

int main(int argc, char *argv[]) {

  if (argc != 3) {                  // Test for correct number of parameters
    cerr << "Uso: " << argv[0] << " <Direccion Multicast> <Puerto>" << endl;
    exit(1);
  }

  string multicastAddress = argv[1];       // First arg:  multicast address
  unsigned short port = atoi(argv[2]);     // Second arg:  port

  try {
    UDPSocket sock(port);

    sock.joinGroup(multicastAddress);
  	//for(;;){
    	char recvString[MAXRCVSTRING + 1];// Buffer for echo string + \0
    	string sourceAddress;             // Address of datagram source
    	unsigned short sourcePort;        // Port of datagram source
    	int bytesRcvd = sock.recvFrom(recvString, MAXRCVSTRING, sourceAddress, 
                                  sourcePort);
    	recvString[bytesRcvd] = '\0';     // Terminate string
    
    	cout << "Datos recibidos: " << recvString << " IP emisor: " << sourceAddress << " Puerto sin ntons: " 
         	 << sourcePort << endl;
//////////////////////////////////
	  	struct timeval timeout;
    	timeout.tv_sec = 2;
    	timeout.tv_usec = 500000;
	  	int valor1 = atoi(recvString[0]);
	  	int valor2 = atoi(recvString[2]);
	    int resultado = valor1 + valor2;
	    
		Solicitud cliente = Solicitud(timeout);	
		cliente.doOperation(ip, puerto, operacion, arreglo);
//////////////////////////////////
	//}
  } catch (SocketException &e) {
    cerr << e.what() << endl;
    exit(1);
  }

  return 0;
}