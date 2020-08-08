#include "PracticalSocket.h" // For UDPSocket and SocketException
#include <iostream>          // For cout and cerr
#include <cstdlib>           // For atoi()
#include "Solicitud.h"
#include <stdlib.h>
#include <string.h>

const int MAXRCVSTRING = 255;     // Longest string to receive

int main(int argc, char *argv[]) {

  if (argc != 3) {                  // Test for correct number of parameters
    cerr << "Usage: " << argv[0] << " <Multicast Address> <Port>" << endl;
    exit(1);
  }

  string multicastAddress = argv[1];       // First arg:  multicast address
  unsigned short port = atoi(argv[2]);     // Second arg:  port

  try {
    UDPSocket sock(port);

    sock.joinGroup(multicastAddress);
  
    char recvString[MAXRCVSTRING + 1];// Buffer for echo string + \0
    string sourceAddress;             // Address of datagram source
    unsigned short sourcePort;        // Port of datagram source
    int bytesRcvd = sock.recvFrom(recvString, MAXRCVSTRING, sourceAddress, 
                                  sourcePort);
    recvString[bytesRcvd] = '\0';     // Terminate string
   
    cout << "DATOS " << recvString << " IP " << sourceAddress << " PUERTO " 
         << sourcePort << endl;

    ////////////////////////////////////////////////////////7
    struct timeval timeout;
    timeout.tv_sec = 2;
    timeout.tv_usec = 500000;
    int val1 = recvString[0] - 48;;
    int val2 = recvString[2] - 48;
    int res = val1 + val2;
    string resultadoCadena =std::to_string(res);
    char arreglo[400];
    char ip[20];
    strcpy(arreglo,resultadoCadena.c_str());
    strcpy(ip,sourceAddress.c_str());
    cout<<arreglo<<endl;
    Solicitud cliente = Solicitud(timeout);	
	cliente.doOperation(ip, 8888, 1, arreglo);


  } catch (SocketException &e) {
    cerr << e.what() << endl;
    exit(1);
  }

  return 0;
}
