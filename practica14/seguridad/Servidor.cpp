#include <algorithm>    // std::binary_search, std::sort
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
  						// send reply duplicated
  						cout << "WATCHOUT Duplicated" <<endl; 
						memcpy(m1.arguments, duplicated, strlen(duplicated)+1);
						response.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
  					}
					expected++;
				}

				else if(msj.requestId != expected) {
					cout << "WEIRDO :P " << endl;
					fclose(dbFile);
					memcpy(m1.arguments, weird, strlen(weird)+1);
					response.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
				}
				break;

			default:
				cout << "Server error: No such operationId: " << msj.operationId  << ", ignored."<< endl;

		} // end switch

	} // end while

	return 0;
} // end main