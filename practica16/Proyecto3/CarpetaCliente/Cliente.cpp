#include "Solicitud.h"
//===============
#define MG_ENABLE_HTTP_STREAMING_MULTIPART 1
#include "mongoose.h"
#include <stdio.h>
//===============
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <unistd.h>
#include <string>
#include <ostream>
//================
#include <thread>
//===============
#define TAM_MAX_DATA 3500

using namespace std;

int calidad = 100;
//===============
static const char *s_http_port = "8888";
static struct mg_serve_http_opts s_http_server_opts;
int banderaDominio = false;
char * dominio = "192.168.8.";

static void handle_size(struct mg_connection *nc, struct http_message *hm) {
		char query[256];
		if(banderaDominio){
			sprintf(query, dominio, (int)strlen(dominio));
			mg_send_head(nc,200,strlen(query), "Content-Type: text/plain");
			mg_printf(nc, "%s", query);
			banderaDominio = false;
		}
		else{
			mg_get_http_var(&hm->body, "query", query, sizeof(query));
			sprintf(query, "Longitud de la cadena = %d caracteres", (int)strlen(query));
			printf("Cadena enviada: %s\n", query);
			mg_send_head(nc,200,strlen(query), "Content-Type: text/plain");
			mg_printf(nc, "%s", query);
		}
}

static void ev_handler(struct mg_connection *nc, int ev, void *p) {
	char query[256];
 	struct http_message *hm = (struct http_message *) p;

	if (ev == MG_EV_HTTP_REQUEST) {
		if (mg_vcmp(&hm->uri, "/search") == 0) { 
			
			mg_get_http_var(&hm->body, "query", query, sizeof(query));
			printf("Cadena introducida: %s\n",query);
			calidad = atoi(query);
		    handle_size(nc, hm);  
			
		}else if (mg_vcmp(&hm->uri, "/dominio") == 0) { 
			
			banderaDominio = true;
			handle_size(nc, hm);
			
		}else if (mg_vcmp(&hm->uri, "/actualiza") == 0) { 
			
			s_http_server_opts.document_root = "www";
			
		}else{
			mg_serve_http(nc, (struct http_message *) p, s_http_server_opts);
		}
	}

}
void servidorWeb(){
	struct mg_mgr mgr;
	struct mg_connection *nc;
	mg_mgr_init(&mgr, NULL);

	printf("Starting web server on port %s\n", s_http_port);
	nc = mg_bind(&mgr, s_http_port, ev_handler);
	if (nc == NULL) {
		printf("Failed to create listener\n");
		exit(1);
	}
	// Set up HTTP server parameters
	mg_set_protocol_http_websocket(nc);
	s_http_server_opts.document_root = "www"; // Serve current directory
	s_http_server_opts.enable_directory_listing = "yes";
	for (;;) {
		mg_mgr_poll(&mgr, 1000);
	}
	mg_mgr_free(&mgr);
}
void cliente(char*argv1, char*argv2, char*argv3, char*argv4){
	std::string auxDom = argv1;
	dominio = const_cast<char *>(auxDom.c_str());
	//===========
	ushort rango = atoi(argv2);
	ushort port = atoi(argv3);
	while(1){
		for(int i=0; i<rango; i++){
			std::string s = "www/" + std::to_string(107) + ".jpg";
			std::string a = argv1 + std::to_string(107);
			char *fileName = const_cast<char *>(s.c_str());
			char *address = const_cast<char *>(a.c_str());
			std::ofstream file(fileName, std::fstream::binary);
    		if (!file) {
        		std::cerr << "Error al abrir archivo" << endl;
        		exit(EXIT_FAILURE);
    		}		
			char *segmento;
    		Solicitud solicitud;
			cout << "Comienza la recepcion del archivo: " << endl;
			while (1) {
				int operation = 1;
				segmento = solicitud.doOperation(address, port, operation, NULL, 0, calidad);
				if( segmento[0] == 'F' && segmento[1] == 'I' && segmento[2] == 'N'){
					break;
				}		
				file.write(segmento, 3500);
			}
    		cout << "Se recibio el archivo correctamente" << endl;
			
		}
		sleep(atoi(argv4));
	}
}
//===============
int main(int argc, char*argv[]) {
	if (argc < 4) {
		cout << "Insertar lo siguiente: Primeros 24 bits de la ip de la red: ej. 10.100.20. | Numero de ordenadores | Puerto | Tiempo en segundos de espera" << endl;
        exit(EXIT_FAILURE);
    }        
	//===========
	thread th1(cliente, argv[1], argv[2], argv[3], argv[4]), th2(servidorWeb);
	th1.join();
	sleep(1);
	th2.join();
	return 0;
}
