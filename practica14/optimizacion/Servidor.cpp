#include <cstdlib>
#include <iostream>
#include <string>
#include "./dependencies/Respuesta.h"
#include <stdlib.h>
#include <vector>
#include <sys/time.h>

using namespace std;

const int ALPHABET_SIZE = 11; 

// trie node 
struct TrieNode { 
    struct TrieNode *children[ALPHABET_SIZE]; 
    bool isEndOfWord; 
}; 
  
// Returns new trie node (initialized to NULLs) 
struct TrieNode *getNode(void) { 
    struct TrieNode *pNode =  new TrieNode; 
    pNode->isEndOfWord = false; 
    for (int i = 0; i < ALPHABET_SIZE; i++) 
        pNode->children[i] = NULL; 
    return pNode; 
} 
  

void insert(struct TrieNode *root, string key) { 
    struct TrieNode *pCrawl = root; 
  
    for (int i = 0; i < key.length(); i++) { 
        int index = key[i] - 'a'; 
        if (!pCrawl->children[index]) 
            pCrawl->children[index] = getNode(); 
        pCrawl = pCrawl->children[index]; 
    } 

    pCrawl->isEndOfWord = true; 
} 
 
bool search(struct TrieNode *root, string key) { 
    struct TrieNode *pCrawl = root; 
  
    for (int i = 0; i < key.length(); i++) 
    { 
        int index = key[i] - 'a'; 
        if (!pCrawl->children[index]) 
            return false; 
  
        pCrawl = pCrawl->children[index]; 
    } 
  
    return (pCrawl != NULL && pCrawl->isEndOfWord); 
}

struct timeval timeNow;

struct timeval getTimeOfDay(){
	struct timeval timesnap;
	return timesnap;	
}

int main(int argc, char const *argv[]) {
	
	char confirm[] = "Vote registered, thank you!";
	char duplicated[] = "Duplicated: 0000000000000000";
	char weird[] = "Weirdo!";
	long int expected = 0, prev = -1;
	bool exist = false;

	std::vector<string> record;
	std::vector<string> phonebook;

	struct timeval timeout;
	timeout.tv_sec = 100;
	timeout.tv_usec = 500000;

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
  
		cout << "\nListening: "<< expected << ":"<< endl;
	  	//Request info
		memcpy(&msj, response.getRequest(), sizeof(struct mensaje));

		// const string zeros = "0000000000000000";
	  	// string igual = zeros;
		cout << "requestId: " << msj.requestId << endl;
		cout << "operationId: " << msj.operationId << endl;
		switch(msj.operationId) {
			case 1:
				m1.messageType = 1;
				m1.puerto = msj.puerto;
				m1.requestId = msj.requestId;
				memcpy(m1.IP, msj.IP, 16);

				if(msj.requestId == expected){
					char timeBuffer[64];

					// getting the timestamp
					struct timeval tv;
    				gettimeofday(&tv,NULL);
					string seconds = std::to_string(tv.tv_sec);
					string useconds = std::to_string(tv.tv_usec);

  					record.push_back(msj.arguments);
  					string phone = record[0].substr(0, 9);

  					// cout << "DEBUGER: ******************" <<endl;
  					// cout << "phone: "<< phone <<endl;
  					// cout << "phonebook:\n" << endl; 
  					// for(auto i : phonebook) 
  					// 	cout << i <<"\n"<<endl;
  					// cout << "----end phonebook ---" << endl; 
  					// cout << "exist?: " << binary_search(phonebook.begin(), phonebook.end(), phone) << endl;
  					// cout << "******* end DEBUGER ***********" <<endl;

  					exist = binary_search(phonebook.begin(), phonebook.end(), phone);

  					if( exist == false || phonebook.empty()){
  						if(phonebook.empty()) {
  							cout << "pushme its my first time" <<endl; 
  						}else {
  							cout << "Not first and NOT DUPLICATED" <<endl; 
  						}
  						phonebook.push_back(phone);
						// phonebook.push_back(phone);
						record.clear();
	  					// votes.push_back(msj.arguments);
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
  					}
	  				else{
	  					string aux;
	  					for (int i = 0; i < strlen(msj.arguments); i++) {
	       					aux = aux + msj.arguments[i];
							if( msj.arguments[i] == ' ' ){
								flag++;
							}
							if( flag == 1 && msj.arguments[i] == ' '){
								insert(root, aux);
							}
							if(flag == 2){
								flag=0;
							}
	    				}
	  					for (std::size_t i = 0; i < v.size(); i++) {
	  						if(search(root,v[i].substr(18,27))){
	  							igual = v[i].substr(1,16);
	  							existe = true;
	  							break;
	  						}
	  					}
	  				}
  					if(existe == false){
						strcpy(tmbuf2,segundos.c_str());
						fflush(f);
						fputs(tmbuf2,f);
						cout << tmbuf2 <<endl;
						fflush(f);
						strcpy(tmbuf2,microsec.c_str());
						fflush(f);
						cout << tmbuf2 <<endl; 
						fputs(tmbuf2,f);
						fflush(f);
						fputs(" ",f);
						fputs(msj.arguments,f);				
  					}
					fclose(f);
					idAnterior = idEsperado;
					idEsperado++;
					memcpy(m1.arguments, confirmacion, strlen(confirmacion)+1);
					//memcpy(m1.arguments, suma(msj.arguments), strlen(msj.arguments));
					m1.messageType = 1;
					memcpy(m1.IP, msj.IP, 16);//------------------
					m1.puerto = msj.puerto;
					m1.requestId = msj.requestId;
					if(igual == "0000000000000000"){
						respuesta.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
					}
					else{
						memcpy(m1.arguments, igual.c_str(),strlen(igual.c_str())+1);
						respuesta.sendReply(m1.arguments,m1.IP, msj.puerto);	
					}
				} else if(msj.requestId == idAnterior) {
					fclose(f);
					memcpy(m1.arguments, confirmacion, strlen(confirmacion)+1);
					//memcpy(m1.arguments, suma(msj.arguments), strlen(msj.arguments));
					m1.messageType = 1;
					memcpy(m1.IP, msj.IP, 16);//------------------
					m1.puerto = msj.puerto;
					m1.requestId = msj.requestId;
					respuesta.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
				} else {
					// Caso en que los id son anteriores
					cout << "id antiguo guardado en bd servidor." << endl;
					fclose(f);
					memcpy(m1.arguments, confirmacion, strlen(confirmacion)+1);
					//memcpy(m1.arguments, suma(msj.arguments), strlen(msj.arguments));
					m1.messageType = 1;
					memcpy(m1.IP, msj.IP, 16);//------------------
					m1.puerto = msj.puerto;
					m1.requestId = msj.requestId;
					respuesta.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
				}
				break;
			default:
				cout << "Error en el numero de operación" << endl;
				cout << "numero: " << msj.operationId << endl;
				exit(-1);
		}
	}
	return 0;
}