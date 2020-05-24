#include "Respuesta.h"
#include "mensaje.h"
#include <iostream>
#include <stdio.h>
#include <cstring>


#include <functional>
#include <vector> 
#include <algorithm> 
#include<bits/stdc++.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream> 
using namespace std;

const int TELEPHON_SIZE = 10; 
  
// trie node 
struct TrieNode 
{ 
    struct TrieNode *children[TELEPHON_SIZE]; 
  
    // isEndOfWord is true if the node represents 
    // end of a word 
    bool isEndOfWord; 
}; 
  
// Returns new trie node (initialized to NULLs) 
struct TrieNode *getNode(void) 
{ 
    struct TrieNode *pNode =  new TrieNode; 
  
    pNode->isEndOfWord = false; 
  
    for (int i = 0; i < TELEPHON_SIZE; i++) 
        pNode->children[i] = NULL; 
  
    return pNode; 
} 
  
// If not present, inserts key into trie 
// If the key is prefix of trie node, just 
// marks leaf node 
void insert(struct TrieNode *root, string key) 
{ 
    struct TrieNode *pCrawl = root; 
  
    for (int i = 0; i < key.length(); i++) 
    { 
        int index = key[i] - '0'; 
        if (!pCrawl->children[index]) 
            pCrawl->children[index] = getNode(); 
  
        pCrawl = pCrawl->children[index]; 
    } 
  
    // mark last node as leaf 
    pCrawl->isEndOfWord = true; 
} 
  
// Returns true if key presents in trie, else 
// false 
bool search(struct TrieNode *root, string key) 
{ 
    struct TrieNode *pCrawl = root; 
  
    for (int i = 0; i < key.length(); i++) 
    { 
        int index = key[i] - '0'; 
        if (!pCrawl->children[index]) 
            return false; 
  
        pCrawl = pCrawl->children[index]; 
    } 
  
    return (pCrawl != NULL && pCrawl->isEndOfWord); 
}

struct registro{
	char celular[11];
	char CURP[19];
	char partido[4];
	char seguridad[17];
};


int main(int argc,char**argv){
	Respuesta reply=Respuesta(9002);
	int i,nbd=0;
	struct registro rg1,rg2;
	int destino=open(argv[1], O_WRONLY|O_CREAT,0666);

	struct timeval prueba; 
	struct TrieNode *root = getNode();

	for(;;){
		struct mensaje msg;
		memcpy(&msg,reply.getRequest(),sizeof(msg));
		char contestacion[TAM_MAX_DATA], contestacion2[16];
		
		memcpy(&rg1,msg.arguments,sizeof(rg1));

		string tel(rg1.celular);
		if(search(root, tel)){
			cout << "ya existe telefono"<<endl; 
			sprintf(contestacion2,"%d:%d",0,0);
		}
		else{
			insert(root, tel);
			gettimeofday(&prueba,NULL);
	  		sprintf(contestacion2,"%ld:%ld",prueba.tv_sec,prueba.tv_usec);
		}
		
		memcpy(&rg1.seguridad,&contestacion2,17);

    	
		cout<<rg1.celular<<":"<<rg1.CURP<<":"<<rg1.partido<<":"<<rg1.seguridad<<endl;
		write(destino,&rg1,sizeof(rg1));

		if(msg.operationId==suma){
			nbd=1;
			//cout<<"registro recibido: "<<endl;
		}else{
			cout<<"operationId no reconocida"<<endl;
			return -1;
		}
		//cout<<contestacion2<<endl;
		reply.sendReply(contestacion2);
	}
	close(destino);

	return 0;
}