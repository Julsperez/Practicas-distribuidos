#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sys/time.h>
#include <unistd.h>
#include <vector>
#include "./dependencies/Respuesta.h"

using namespace std;

// struct timeval timeNow;

// struct timeval getTimeOfDay() {
// 	struct timeval timestamp;
// 	return timestamp;	
// }

int main(int argc, char const *argv[]) {
	
	char confirmacion[] = "Vote registered, thank you!";
	long int expected =0, prev = -1;
	
	std::vector<string> votes;

	struct timeval timeout;
	timeout.tv_sec = 100;
	timeout.tv_usec = 500000;

	Respuesta respuesta(atoi(argv[1]),timeout);

	while(1) {
		struct mensaje msj;
	 	struct mensaje m1;

	 	FILE *archivo = NULL;
	  	archivo = fopen(argv[2], "a+");
	  	if (archivo == NULL) {
	    	cout << "Server error: No such file or directory " << argv[2] << endl;
	    	break;
	  	}
  
		cout << "\nListening: "<< expected << ":"<< endl;
	  	//Request info
		memcpy(&msj, respuesta.getRequest(), sizeof(struct mensaje));

		const string zeros = "0000000000000000";
	  	string igual = zeros;

		switch(msj.operationId) {
			case 1:
				if(msj.requestId == expected){
					bool exist = false;
					char timeBuffer[64];

					// getting the timestamp
					struct timeval tv;
    				gettimeofday(&tv,NULL);
					string seconds = std::to_string(tv.tv_sec);
					string useconds = std::to_string(tv.tv_usec);

					
  					if(votes.empty()){
	  					votes.push_back(msj.arguments);

						// fflush(archivo);
	  			// 		strcpy(timeBuffer,seconds.c_str());
						// fputs(timeBuffer,archivo);
						// // fflush(archivo);
						// strcpy(timeBuffer,useconds.c_str());
						// fputs(timeBuffer,archivo);
						
						// fflush(archivo);
						// fputs(" ",archivo);
						// fputs(msj.arguments,archivo);

						// fsync((long int)archivo);
	  				} 
	  				else{
	  					// cp arguments aux
	  					string aux;
	  					for (int i = 0; i < strlen(msj.arguments); i++)
	       					aux = aux + msj.arguments[i];

	       				// instead of binary_search, search over phone number
	       				cout << ":---------------Debug secction: ----------- " <<endl;
	       				cout << "votes size: " << votes.size() <<endl;
	  					for (std::size_t i = 0; i < votes.size(); i++) {
	  						// phone number
	  						if(aux.substr(18,27) == votes[i].substr(18,27)){
	  							cout << votes[i].substr(0,15)<<endl;
	  							igual = votes[i].substr(1,16);
	  							cout << igual <<endl;
	  							exist = true;
	  							break;
	  						}
	  					}
	  				}

  					if(exist == false){
						fflush(archivo);
	  					strcpy(timeBuffer,seconds.c_str());
						fputs(timeBuffer,archivo);
						strcpy(timeBuffer,useconds.c_str());
						fputs(timeBuffer,archivo);
						fflush(archivo);
						fputs(" ",archivo);
						fputs(msj.arguments,archivo);
						fsync((long int)archivo);			
  					}

					fclose(archivo);
				
					prev = expected;
					expected++;

					m1.messageType = 1;
					m1.puerto = msj.puerto;
					m1.requestId = msj.requestId;
					memcpy(m1.arguments, confirmacion, strlen(confirmacion)+1);
					memcpy(m1.IP, msj.IP, 16);

					if (igual == zeros) {
						respuesta.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
					} else {
						memcpy(m1.arguments, igual.c_str(),strlen(igual.c_str())+1);
						respuesta.sendReply(m1.arguments,m1.IP, msj.puerto);	
					}
				}

				else if(msj.requestId == prev) {
					fclose(archivo);
					m1.messageType = 1;
					m1.puerto = msj.puerto;
					m1.requestId = msj.requestId;
					memcpy(m1.arguments, confirmacion, strlen(confirmacion)+1);
					memcpy(m1.IP, msj.IP, 16);
					respuesta.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
				} else {
					// Caso en que los id son anteriores
					fclose(archivo);
					cout << "Action ignored" << endl;
					m1.messageType = 1;
					m1.puerto = msj.puerto;
					m1.requestId = msj.requestId;
					memcpy(m1.arguments, confirmacion, strlen(confirmacion)+1);
					memcpy(m1.IP, msj.IP, 16);
					respuesta.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
				}
			break;
			
			default:
				cout << "Server error: No existe operacion " << msj.operationId  << ", conexion ignorada."<< endl;
		}
	}
	return 0;
}