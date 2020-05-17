#include "./dependencies/Solicitud.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <thread>
#include <vector>
using namespace std;


const char *ipServer_2 = "192.168.15.17" ;
const int portServer_2 = 1996;

// void cliente_1(vector<string>);
// void cliente_2(vector<string>);

void cliente_1(vector<string> votes);
void cliente_2(vector<string> votes);


int main(int argc, char*argv[]) {	
	char vote[4000];

	vector<string> serv1_data;
	vector<string> serv2_data;

	FILE *votesFile = fopen("votes.txt", "r+");
	if (votesFile==NULL) {
		cout << "Client error, no such file or directory" << endl;
		exit(-1);
	}

	while(fgets(vote, 4000, votesFile) != NULL){
		vector <string> record;
		record.push_back(vote);

		string phone = record[0].substr(0, 10);
		// cout <<"phone:"<< phone[9]<<endl;

		if((phone[9]-'0')%2!=0 || phone[9]=='0' /*|| phone[9]=='0'*/){
			// cout<<"Enviando al servidor 1"<<endl;
			serv1_data.push_back(vote);
		} else {
			// cout<<"Enviando al servidor 2"<<endl;
			serv2_data.push_back(vote);
		}
	}

	// int i = 0;
	// for(auto data : serv1_data) {
	// 	cout << i<<"|"<< data <<endl;
	// 	i++;
	// }
	// int j = 0;
	// for(auto data : serv2_data) {
	// 	cout << j<<"-" << data <<endl;
	// 	j++;
	// }	

	thread server_1(cliente_1, serv1_data);
	thread server_2(cliente_2, serv2_data);

	server_1.join();
	server_2.join();

	return 0;
}


void cliente_1(vector<string> votes) {
	char *ipServer_1 = "127.0.0.1" ;
	int portServer_1 = 2407;
	struct timeval timeout;
	timeout.tv_sec = 2;
	timeout.tv_usec = 500000;
	Solicitud cliente = Solicitud(timeout);
	cliente.doOperation(ipServer_1, portServer_1, 1, votes);
}

void cliente_2(vector<string> votes) {
	char *ipServer_2 = "192.168.15.17" ;
	int portServer_2 = 1996;
	struct timeval timeout;
	timeout.tv_sec = 2;
	timeout.tv_usec = 500000;
	Solicitud cliente = Solicitud(timeout);
	cliente.doOperation(ipServer_2, portServer_2, 1, votes);
}
