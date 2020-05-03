#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>

int puerto = 7200;

int main(void) {
	struct sockaddr_in msg_to_server_addr, client_addr;
	int s, num[2], res;

	s = socket(AF_INET, SOCK_DGRAM, 0);

	/*rellena la direccion del servidor*/
	bzero((char *)&msg_to_server_addr, sizeof(msg_to_server_addr));
	
}