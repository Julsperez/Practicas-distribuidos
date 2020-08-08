#define MG_ENABLE_HTTP_STREAMING_MULTIPART 1
#include "mongoose.h"
#include <stdio.h>
#include <iostream>
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <errno.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include "./dependencies/SocketDatagrama.h";

using namespace std;

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;

void checkHostName(int hostname) { 
    if (hostname == -1) { 
        perror("gethostname"); 
        exit(1); 
    } 
} 

void checkHostEntry(struct hostent * hostentry){ 
    if (hostentry == NULL) { 
        perror("gethostbyname"); 
        exit(1); 
    } 
} 

void checkIPbuffer(char *IPbuffer) { 
    if (NULL == IPbuffer){ 
        perror("inet_ntoa"); 
        exit(1); 
    } 
}

static void handle_size(struct mg_connection *nc, struct http_message *hm) {
		char query[256];
		mg_get_http_var(&hm->body, "query", query,sizeof(query));
		char *IPbuffer; 
		struct hostent *host_entry; 
		int hostname; 
		hostname = gethostname(query, sizeof(query)); 
		checkHostName(hostname); 
		host_entry = gethostbyname(query); 
		checkHostEntry(host_entry); 
		IPbuffer = inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0]));
    	printf("Ip broadcast: %s\n", IPbuffer); 
		sprintf(query, "IP encontrada: ", IPbuffer);
		mg_send_head(nc,200,strlen(query), "Content-Type: text/plain");
		mg_printf(nc, "%s", query);
}

static void ev_handler(struct mg_connection *nc, int ev, void *p) {
	char query[256];
 	struct http_message *hm = (struct http_message *) p;

	if (ev == MG_EV_HTTP_REQUEST) {
		if (mg_vcmp(&hm->uri, "/search") == 0) { 
			mg_get_http_var(&hm->body, "query", query,sizeof(query));
			printf("IP introducida: %s\n",query);
		    handle_size(nc, hm);  
		}else{
			mg_serve_http(nc, (struct http_message *) p, s_http_server_opts);
		}
	}

}

int main(void) {
	struct mg_mgr mgr;
	struct mg_connection *nc;
	mg_mgr_init(&mgr, NULL);

	printf("Starting web server on port %s\n", s_http_port);
	nc = mg_bind(&mgr, s_http_port, ev_handler);
	if (nc == NULL) {
		printf("Failed to create listener\n");
		return 1;
	}
	// Set up HTTP server parameters
	mg_set_protocol_http_websocket(nc);
	s_http_server_opts.document_root = "www"; // Serve current directory
	s_http_server_opts.enable_directory_listing = "yes";
	for (;;) {
		mg_mgr_poll(&mgr, 1000);
	}
	mg_mgr_free(&mgr);
	return 0;
}
