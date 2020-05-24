#include <algorithm>    // std::binary_search, std::sort
#include <bits/stdc++.h> // TrieNode struct 
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sys/time.h>
#include <unistd.h>
#include <vector>
#include <thread>
#include "./dependencies/Respuesta.h"
#include "dependencies/Solicitud.h"

using namespace std;

const char *ipServer1 = "127.0.0.1";
const char *ipServer2 = "192.168.15.17";
const int numServers = 2;
const int PHONE_SIZE = 10;

struct TrieNode {
	struct TrieNode *children[PHONE_SIZE];
	bool isWord;
};

void sendServer(char *, struct mensaje, Respuesta);

struct TrieNode *getNode();
void insert(struct TrieNode *, string);
bool search(struct TrieNode *, string);


int main(int argc, char const *argv[]) {
	bool exist = false;
	char duplicated[] = "Vote duplicated, timestamp: 0:0";
	char confirm[] = "fucking weirdo";
	int balance[numServers];
	int serverIndex;
	long int expected = 0;
	long int prevId = -1;
	struct TrieNode *root = getNode();
	vector <string> record;
	
	struct timeval timeout;
	timeout.tv_sec = 100;
	timeout.tv_usec = 500000;
	Respuesta response(atoi(argv[1]),timeout);

	cout << "Loading configurations..."<<endl;
	for(int i=0; i < numServers; i++)
		balance[i] = 0;
	cout << "Server ready..." << endl;

	int i = 0, j = 0;

	while(1) {
		struct mensaje msj;
	 	struct mensaje m1;
		cout << "\n------- New request "<<prevId+1<<"-------"<<endl; //for request: "<< prevId + 1 << endl;
		memcpy(&msj, response.getRequest(), sizeof(struct mensaje));

		// cout << "requestId: " << msj.requestId << endl;
		// cout << "operationId: " << msj.operationId << endl;
		switch(msj.operationId) {
			case 1:
				cout << "Balanceador"<<endl;
				if(msj.requestId > prevId){
					record.push_back(msj.arguments);
					string phone = record[0].substr(0, 10);
					record.clear();
					if((phone[9]-'0')%2!=0 || phone[0]=='0'){
						cout<< "ipServer 1, no pair + 0: " <<phone<< endl;
						i++;
						// serverIndex = 0; // For server A
						// thread thrx(sendServer, ipServer1, msj, response);
						// thrx.join();
					} else {
						cout<< "ipServer 2, pair: " <<phone<< endl;
						j++;
						// serverIndex = 1;
						// thread thrx(sendServer, ipServer2, msj, response);
						// thrx.join();
					}
					cout<< "[Counting balance]> ServA:"<< i << ": ServB:"<< j << endl;
					prevId = msj.requestId;
					balance[serverIndex] += 1;

					m1.messageType = 1;
					m1.puerto = msj.puerto;
					m1.requestId = msj.requestId;
					memcpy(m1.IP, msj.IP, 16);

					memcpy(m1.arguments, confirm, strlen(confirm)+1);
					response.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
					
				}/* else if (msj.requestId == prevId){

				} else {

				} */
				break;

			case 2:
				cout << "Procesamiento"<<endl;
				// m1.messageType = 1;
				// m1.puerto = msj.puerto;
				// m1.requestId = msj.requestId;
				// memcpy(m1.IP, msj.IP, 16);

				// if(msj.requestId == expected){
  				// 	record.push_back(msj.arguments);
  				// 	string phone_number = record[0].substr(0, 10);
				// 	record.clear();

				// 	// cout << "Searching for "<< phone_number << endl;
				// 	if(search(root, phone_number)) { // exist? 
				// 		// cout << "This phone number is already written." <<endl;
				// 		memcpy(m1.arguments, duplicated, strlen(duplicated)+1);
				// 		response.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
				// 	}else {
				// 		insert(root, phone_number);
				// 		struct timeval tv;
	    		// 		gettimeofday(&tv,NULL);
				// 		string seconds = std::to_string(tv.tv_sec);
				// 		string useconds = std::to_string(tv.tv_usec);
				// 		string timestamp = seconds + ':' + useconds;
				// 		string message = "Vote registered, timestamp: " + timestamp;
				// 		char timeBuffer[64];
				// 		char confirm[message.size()+1];
				// 		strcpy(confirm, message.c_str());
				// 		// cout << "First vote! " << endl;
				// 		fflush(dbFile);
	  			// 		strcpy(timeBuffer,seconds.c_str());
				// 		fputs(timeBuffer,dbFile);
				// 		strcpy(timeBuffer,useconds.c_str());
				// 		fputs(timeBuffer,dbFile);
				// 		fflush(dbFile);
				// 		fputs(" ",dbFile);
				// 		fputs(msj.arguments,dbFile);
				// 		fsync((long int)dbFile);
				// 		fclose(dbFile);			
				// 		memcpy(m1.arguments, confirm, strlen(confirm)+1);
				// 		response.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
				// 		// cout << "Request answered successfully." <<endl;
				// 	}
				// 	expected++;
				// }
				break;

			default:
				// cout << "Server error: No such operationId: " << msj.operationId  << ", fowarding."<< endl;
				continue;

		} // end switch

	} // end while,

	return 0;
} // end main



// Threads Methods ----------------------

/* void sendServer(char *ipAenviar, struct mensaje msj, Respuesta res){
	// cout << "[ Envio de la peticion al servidor ] " << indiceIPServidor <<endl;
	struct timeval timeout;
  	timeout.tv_sec = 2;
  	timeout.tv_usec = 500000;
	char *ip = ipAenviar;
	int puerto = 9999;
	int operacion = 2;
	Solicitud cliente = Solicitud(timeout);
	char *respuesta = cliente.doOperation(ip, puerto, operacion, msj.arguments); // id missing
	struct timeval tv;
    gettimeofday(&tv,NULL);
	string segundos = std::to_string(tv.tv_sec);
	string microsec = std::to_string(tv.tv_usec);
	char tmbuf[64];
	char tmbuf2[64];
	strcpy(tmbuf,segundos.c_str());
	fflush(f);
	strcpy(tmbuf2,microsec.c_str());
	fflush(f);
	struct mensaje m1;
	memcpy(m1.arguments, respuesta, strlen(respuesta)+1);
	m1.messageType = 1;
	memcpy(m1.IP, msj.IP, 16);
	m1.puerto = msj.puerto;
	m1.requestId = msj.requestId;
	cout << "[ Envio de la respuesta al cliente ] " <<endl;
	res.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
} */

// TrieNode Structure Methods ----------------------

struct TrieNode *getNode() {
	struct TrieNode *pNode = new TrieNode;
	pNode -> isWord = false;
	for(int i = 0; i < PHONE_SIZE; i++) {
		pNode -> children[i] = NULL;
	}
	return pNode;
}

void insert(struct TrieNode *root, string phone){
	struct TrieNode *pCrawl = root;
	for(int i = 0; i < phone.length(); i++) {
		int index = phone[i] - '0';
		if(!pCrawl -> children[index])
			pCrawl -> children[index] = getNode();
		pCrawl = pCrawl -> children[index];
	}
	pCrawl -> isWord = true;
}

bool search(struct TrieNode *root, string phone) {
	struct TrieNode *searcher = root;
	for(int i = 0; i < phone.length(); i++) {
		int index = phone[i] - '0';
		if(!searcher -> children[index])
			return false;
		searcher = searcher -> children[index];
	}
	return (searcher != NULL && searcher -> isWord);
}



// FILE *dbFile = NULL;
	  	// dbFile = fopen(argv[2], "a+");
	  	// if (dbFile == NULL) {
	    // 	cout << "Server error: No such file or directory " << argv[2] << endl;
	    // 	break;
	  	// }