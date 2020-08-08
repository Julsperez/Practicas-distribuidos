#include "SocketMulticast.h"
#include "mensaje.h"
#include <cstdlib>
#include <sys/socket.h>
#include <iostream> 
#include <string>

using namespace std;

int main(int argc, char const *argv[]){
	char* ipMulticast = const_cast<char*>(argv[1]);
	int puerto = atoi(argv[2]);
	int ttl = atoi(argv[3]);
	char* cadenaChida = const_cast<char*>(argv[4]);
	cout << ipMulticast << endl;
	cout << puerto << endl;
	cout << ttl << endl;
	cout << cadenaChida << endl;

	/*SocketMulticast  s = new SocketMulticast(puerto);
	s.unirseGrupo(ipMulticast);
	while(1){
		PaqueteDatagrama paq(cadenaChida, sizeof(cadenaChida), , puerto);
		s.envia(PaqueteDatagrama & p, ttl);
	} */
	cout << INADDRY_ANY <<endl;
}
