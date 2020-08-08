#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <sys/time.h>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include "./dependencies/Respuesta.h"

using namespace std;

int main(int argc, char const *argv[]) {

	char confirmacion[] = "Vote registered, thank you!";
	long int expected = 0, prev = -1;

	vector<string> votes;

	vector<string> telefonos;
	vector<string> curps;

	struct timeval timeout;
	timeout.tv_sec = 100;
	timeout.tv_usec = 500000;

	Respuesta respuesta(atoi(argv[1]), timeout);

	while (1) {
		struct mensaje msj;
		struct mensaje m1;

		FILE *archivo = NULL;
		archivo = fopen(argv[2], "a+");
		if (archivo == NULL) {
			cout << "Server error: No such file or directory " << argv[2]
					<< endl;
			break;
		}

		cout << "\nListening: " << expected << ":" << endl;
		//Request info
		memcpy(&msj, respuesta.getRequest(), sizeof(struct mensaje));

		const string zeros = "0000000000";
		string igual = zeros;

		switch (msj.operationId) {
		case 1:
			if (msj.requestId == expected) {
				bool exist = false;
				char timeBuffer[64];

				// getting the timestamp
				struct timeval tv;
				gettimeofday(&tv, NULL);
				string seconds = std::to_string(tv.tv_sec);
				string useconds = std::to_string(tv.tv_usec);

				if (votes.empty()) {
					votes.push_back(msj.arguments);
					for (auto vote : votes){
						cout << "Tel added: " << endl;
						cout << vote.substr(0, 10) << endl;
						telefonos.push_back(vote.substr(0, 10));
						cout << "Curp added: " << endl;
						cout << vote.substr(11, 16) << endl;
						curps.push_back(vote.substr(11, 16));
					}
				} else {
					cout << "Tel size: " << endl;
					cout << telefonos.size() << endl;

					for(string telef : telefonos) {
						cout << telef << endl;
					}

					vector<string> aux;
					vector<string> telToSearch;
					aux.push_back(msj.arguments);
					telToSearch.push_back(aux[0].substr(0, 10));

					for (auto tel : telToSearch) {
						cout << "Tel To Search: " << endl;
						cout << tel << endl;
						cout << "Binary Search: " << endl;
						cout << binary_search(telefonos.begin(), telefonos.end(), tel) << endl;
						if (binary_search(telefonos.begin(), telefonos.end(),
								tel)) {
							exist = true;
							igual = tel;
						} else {
							cout << "Tel added: " << endl;
							cout << tel << endl;
							telefonos.push_back(tel);
							cout << "Curp added: " << endl;
							cout << aux[0].substr(11, 16) << endl;
							curps.push_back(aux[0].substr(11, 16));
						}
					}
				}

				if (!exist) {
					fflush(archivo);
					strcpy(timeBuffer, seconds.c_str());
					fputs(timeBuffer, archivo);
					strcpy(timeBuffer, useconds.c_str());
					fputs(timeBuffer, archivo);
					fflush(archivo);
					fputs(" ", archivo);
					fputs(msj.arguments, archivo);
					fsync((long int) archivo);
				}

				fclose(archivo);

				prev = expected;
				expected++;

				m1.messageType = 1;
				m1.puerto = msj.puerto;
				m1.requestId = msj.requestId;
				memcpy(m1.arguments, confirmacion, strlen(confirmacion) + 1);
				memcpy(m1.IP, msj.IP, 16);

				if (igual == zeros) {
					respuesta.sendReply((char*) m1.arguments, m1.IP,
							msj.puerto);
				} else {
					memcpy(m1.arguments, igual.c_str(),
							strlen(igual.c_str()) + 1);
					respuesta.sendReply(m1.arguments, m1.IP, msj.puerto);
				}
			} else if (msj.requestId == prev) {
				fclose(archivo);
				m1.messageType = 1;
				m1.puerto = msj.puerto;
				m1.requestId = msj.requestId;
				memcpy(m1.arguments, confirmacion, strlen(confirmacion) + 1);
				memcpy(m1.IP, msj.IP, 16);
				respuesta.sendReply((char*) m1.arguments, m1.IP, msj.puerto);
			} else {
				// Caso en que los id son anteriores
				fclose(archivo);
				cout << "Action ignored" << endl;
				m1.messageType = 1;
				m1.puerto = msj.puerto;
				m1.requestId = msj.requestId;
				memcpy(m1.arguments, confirmacion, strlen(confirmacion) + 1);
				memcpy(m1.IP, msj.IP, 16);
				respuesta.sendReply((char*) m1.arguments, m1.IP, msj.puerto);
			}
			break;

		default:
			cout << "Server error: No existe operacion " << msj.operationId
					<< ", conexion ignorada." << endl;
		}
	}
	return 0;
}
