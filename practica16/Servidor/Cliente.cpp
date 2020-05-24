#include "./dependencies/Solicitud.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <thread>
#include <vector>
using namespace std;

int main(int argc, char*argv[]) {	
	char bufferVote[4000];
	char *ip = argv[1]; // Need to be server A ip
	int port = atoi(argv[2]); // Need to be the Server A port :9001 (balance)
	char *nVotes = argv[3]; // #votes to read
	int operation = 1;
	int id = 0;

	FILE *votesFile = fopen("votes.txt", "r+");
	if (votesFile == NULL) {
		cout << "Client file: No such file or directory";
		exit(-1);
	}

	struct timeval timeout;
  	timeout.tv_sec = 2;
	timeout.tv_usec = 500000;

	for(int i = 0; i < atoi(nVotes); i++) {
		// cout<<"--- new request: " << id << "---" << endl;
		fgets(bufferVote, 4000, votesFile); // take a vote from file
		Solicitud client = Solicitud(timeout);
		// should ip and port be constants?
		client.doOperation(ip, port, operation, bufferVote, id);
		id++;
	}
	return 0;
}

	

	