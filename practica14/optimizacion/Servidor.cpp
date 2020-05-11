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
	long int idEsperado =0, idAnterior = -1;
	struct TrieNode *root = getNode();
	int flag=0;
	struct timeval timeout;
  	timeout.tv_sec = 100;
  	timeout.tv_usec = 500000;
  	std::vector<string> v;
	Respuesta respuesta(atoi(argv[1]),timeout);
  	char confirmacion[] = "Registro guardado en bd servidor.";
  	FILE *f = fopen(argv[2], "w");
	if (f==NULL) {
		cout << "error al abrir el archivo (w) " << argv[2] << endl;
		exit(-1);
	}
	fclose(f);
	while(1) {
	struct mensaje msj;
  	struct mensaje m1;
  

  	string igual = "0000000000000000";
	cout << "\nEsperando conexion : " << endl;
	cout << "Se espera recibir id mensaje: " << idEsperado << endl;
	memcpy(&msj, respuesta.getRequest(), sizeof(struct mensaje));
		switch(msj.operationId) {
			case 1:
				if(msj.requestId == idEsperado){
					struct timeval tv;
    				gettimeofday(&tv,NULL);
					//const char *time_datails = NULL;
					//struct timeval aux;
					//struct tm *nowtm;
					
					char tmbuf[64];
					char tmbuf2[64];
					//aux.tv_usec = getTimeOfDay().tv_usec;
					//cout << aux.tv_usec;
					//nowtm = localtime(&aux.tv_usec);
					//size_t sz = strftime(tmbuf, sizeof tmbuf, "%Y-%m-%d %H:%M:%S", nowtm);
					//sprintf(tmbuf,"%lu",sz);
					string s = tmbuf;
					//strcat(msj.arguments,s);
					string segundos = std::to_string(tv.tv_sec);
					string microsec = std::to_string(tv.tv_usec);
	
					char linea[1024];
					bool existe = false;
					string copia;
					int count_aux = 0;
    				for (int i = 0; i < strlen(msj.arguments); i++) { 
       					copia = copia + msj.arguments[i]; 
    				}
    				
    				FILE *f = fopen(argv[2], "w+");
  					
  					if (f == NULL) {
    					cout << "Error al abrir el archivo (SERVIDOR)" << endl;
  					}				
  					if(v.empty()){
	  					v.push_back(msj.arguments);
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