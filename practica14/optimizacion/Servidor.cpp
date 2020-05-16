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
#include "./dependencies/Respuesta.h"

using namespace std;

const int PHONE_SIZE = 10;

struct TrieNode {
	struct TrieNode *children[PHONE_SIZE];
	bool isWord;
};

struct TrieNode *getNode();
void insert(struct TrieNode *, string);
bool search(struct TrieNode *, string);

int main(int argc, char const *argv[]) {
	char duplicated[] = "Vote duplicated, timestamp: 0:0";
	long int expected = 0;
	bool exist = false;
	vector <string> record;

	struct timeval timeout;
	timeout.tv_sec = 100;
	timeout.tv_usec = 500000;

	struct TrieNode *root = getNode();

	Respuesta response(atoi(argv[1]),timeout);

	while(1) {
		struct mensaje msj;
	 	struct mensaje m1;

	 	FILE *dbFile = NULL;
	  	dbFile = fopen(argv[2], "a+");
	  	if (dbFile == NULL) {
	    	cout << "Server error: No such file or directory " << argv[2] << endl;
	    	break;
	  	}
  
		// cout << "\nListening: "<< expected << ":"<< endl;
		memcpy(&msj, response.getRequest(), sizeof(struct mensaje));

		// cout << "requestId: " << msj.requestId << endl;
		// cout << "operationId: " << msj.operationId << endl;
		switch(msj.operationId) {
			case 1:
				m1.messageType = 1;
				m1.puerto = msj.puerto;
				m1.requestId = msj.requestId;
				memcpy(m1.IP, msj.IP, 16);

				if(msj.requestId == expected){
  					record.push_back(msj.arguments);
  					string phone_number = record[0].substr(0, 10);
					record.clear();

					// cout << "Searching for "<< phone_number << endl;
					if(search(root, phone_number)) { // exist? 
						// cout << "This phone number is already written." <<endl;
						memcpy(m1.arguments, duplicated, strlen(duplicated)+1);
						response.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
					}else {
						insert(root, phone_number);
						struct timeval tv;
	    				gettimeofday(&tv,NULL);
						string seconds = std::to_string(tv.tv_sec);
						string useconds = std::to_string(tv.tv_usec);
						string timestamp = seconds + ':' + useconds;
						string message = "Vote registered, timestamp: " + timestamp;
						char timeBuffer[64];
						char confirm[message.size()+1];
						strcpy(confirm, message.c_str());
						// cout << "First vote! " << endl;
						fflush(dbFile);
	  					strcpy(timeBuffer,seconds.c_str());
						fputs(timeBuffer,dbFile);
						strcpy(timeBuffer,useconds.c_str());
						fputs(timeBuffer,dbFile);
						fflush(dbFile);
						fputs(" ",dbFile);
						fputs(msj.arguments,dbFile);
						fsync((long int)dbFile);
						fclose(dbFile);			
						memcpy(m1.arguments, confirm, strlen(confirm)+1);
						response.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
						// cout << "Request answered successfully." <<endl;
					}
					expected++;
				}
				break;

			default:
				// cout << "Server error: No such operationId: " << msj.operationId  << ", fowarding."<< endl;
				continue;

		} // end switch

	} // end while,

	return 0;
} // end main


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