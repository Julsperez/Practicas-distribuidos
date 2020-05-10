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
	long int expected =0, prev = -1;
	bool exist = false;
	
	// std::vector<string> votes;
	// std::vector<string> phones;
	// std::vector<string> curps;
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

		switch(msj.operationId) {
			case 1:
				m1.messageType = 1;
				m1.puerto = msj.puerto;
				m1.requestId = msj.requestId;
				memcpy(m1.IP, msj.IP, 16);

				if(msj.requestId == expected){
					exist = false;
					char timeBuffer[64];

					// getting the timestamp
					struct timeval tv;
    				gettimeofday(&tv,NULL);
					string seconds = std::to_string(tv.tv_sec);
					string useconds = std::to_string(tv.tv_usec);

					/************** oldway ***************
	  				// // cp arguments aux
					// string aux;
  					// for (int i = 0; i < strlen(msj.arguments); i++)
     				// 	aux = aux + msj.arguments[i];
					// // search for duplicate (validation)
	       			// // instead of binary_search, search over phone number
  					// for (std::size_t i = 0; i < votes.size(); i++) {
  					// 	if(aux.substr(0,9) == votes[i].substr(0,9)){
  					// 		cout << "WATCHOUT! DUPLICATED"<<endl;
  					// 		exist = true;
  					// 		// send reply
  					// 		break;
  					// 	}
  					// }
  					**************************************/


					/*

						exist = search(phone, phonebook) 
						exist ? duplicated() : save()

					*/
					// m1.messageType = 1;
					// m1.puerto = msj.puerto;
					// m1.requestId = msj.requestId;
					// memcpy(m1.IP, msj.IP, 16);

  					record.push_back(msj.arguments);
  					string phone = record[0].substr(0, 9);
  					cout << "phone: "<< phone <<endl;
  					// string curp = record.substr(11, 28)

  					// for(string telef : telefonos) {
						// 	cout << telef << endl;
						// }
  					cout << "phonebook:" << endl; 
  					for(auto i : phonebook) {
  						cout << i ;
  					}
  					cout << "phonebook-------------" << endl; 
  					cout << "exist?: " << binary_search(phonebook.begin(), phonebook.end(), phone) << endl;


  					if(phonebook.empty()){
  						phonebook.push_back(phone);
  					}
						// phoneNums.push_back(cpArgs[0].substr(0,9));

  					else if(binary_search(phonebook.begin(), phonebook.end(), phone)){
  						// send reply duplicated
						memcpy(m1.arguments, duplicated, strlen(duplicated)+1);
						response.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
  					}

					else{ // if (exist == false )
						phonebook.push_back(phone);
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
						prev = expected;
						expected++;
				}

				else if(msj.requestId == prev) {
					fclose(dbFile);
					memcpy(m1.arguments, confirm, strlen(confirm)+1);
					response.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
					// m1.messageType = 1;
					// m1.puerto = msj.puerto;
					// m1.requestId = msj.requestId;
					// memcpy(m1.IP, msj.IP, 16);
				} else {
					// Caso en que los id son anteriores
					fclose(dbFile);
					cout << "Action ignored" << endl;
					// m1.messageType = 1;
					// m1.puerto = msj.puerto;
					// m1.requestId = msj.requestId;
					// memcpy(m1.arguments, confirm, strlen(confirm)+1);
					// memcpy(m1.IP, msj.IP, 16);
					// response.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
				}
			break;

			default:
				cout << "Server error: No existe operacion " << msj.operationId  << ", conexion ignorada."<< endl;
		}
	}
	return 0;
}



  					
					


					// if (igual == zeros) {
					// } else {
					// 	memcpy(m1.arguments, igual.c_str(),strlen(igual.c_str())+1);
					// 	response.sendReply(m1.arguments,m1.IP, msj.puerto);	
					// }


					



					// for (auto vote : votes){
					// 	cout << "Tel added: " << vote.substr(0, 10) << endl;
					// 	telefonos.push_back(vote.substr(0, 10));
					// 	cout << "Curp added: " << vote.substr(11, 16) << endl;
					// 	curps.push_back(vote.substr(11, 16));
					// }
  					

					

  					// if (votes.empty()) {
  						// fill curps and phones
						// Add element to curp and phones from vote data
					// } 
					// else {
						// DEBUG --------
						// cout << "Tel size: " << endl;
						// cout << telefonos.size() << endl;

						// for(string telef : telefonos) {
						// 	cout << telef << endl;
						// }
						// DEBUG --------



						//  good way
						
					// 	aux.push_back(msj.arguments); // cast char msj to string class


					// 	telToSearch.push_back(aux[0].substr(0, 10));

					// 	// phoneRegister.push_back()

					// 	for (auto tel : telToSearch) {
					// 		cout << "Tel To Search: " << endl;
					// 		cout << tel << endl;
					// 		cout << "Binary Search: " << endl;
							
					// 		cout << binary_search(telefonos.begin(), telefonos.end(), tel) << endl;

					// 		if (binary_search(telefonos.begin(), telefonos.end(), tel)) {
					// 			exist = true;
					// 			igual = tel;
					// 		} else {
					// 			cout << "Tel added: " << endl;
					// 			cout << tel << endl;
					// 			telefonos.push_back(tel);
					// 			cout << "Curp added: " << endl;
					// 			cout << aux[0].substr(11, 16) << endl;
					// 			curps.push_back(aux[0].substr(11, 16));
					// 		}
					// 	}
					// }

					


















  					//if(votes.empty()){

						// fflush(dbFile);
	  			// 		strcpy(timeBuffer,seconds.c_str());
						// fputs(timeBuffer,dbFile);
						// // fflush(dbFile);
						// strcpy(timeBuffer,useconds.c_str());
						// fputs(timeBuffer,dbFile);
						
						// fflush(dbFile);
						// fputs(" ",dbFile);
						// fputs(msj.arguments,dbFile);

						// fsync((long int)dbFile);
	  				//}

	  				// else{

	  				// }


					

					
				











				
			
