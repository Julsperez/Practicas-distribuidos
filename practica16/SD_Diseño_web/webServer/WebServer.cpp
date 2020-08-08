#define MG_ENABLE_HTTP_STREAMING_MULTIPART 1
#include "mongoose.h"
##include "RegistroVotos.h"
#include <stdio.h>
#include <iostream>

using namespace std;

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;
static RegistroVotos registrovotos;


static void send_data(struct mg_connection *nc, struct http_message *hm) {
		char data[256];
		data = registrovotos->getVotosSA();
		mg_get_http_var(&hm->body, "query", query,sizeof(query));
		sprintf(data, "votes: %s", data);
		printf("Datos enviados: %s\n", data);
		mg_send_head(nc,200,strlen(data), "Content-Type: text/plain");
		mg_printf(nc, "%s", data);
}

static void ev_handler(struct mg_connection *nc, int ev, void *p) {
	char query[256];
 	struct http_message *hm = (struct http_message *) p;


	if (ev == MG_EV_HTTP_REQUEST) {
		if (mg_vcmp(&hm->uri, "/search") == 0) {
			mg_get_http_var(&hm->body, "query", query,sizeof(query));
			printf("Cadena introducida: %s\n",query);
			send_data(nc, hm);
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
	s_http_server_opts.document_root = "."; // Serve current directory
	s_http_server_opts.enable_directory_listing = "yes";
	for (;;) {
		mg_mgr_poll(&mgr, 1000);
	}
	mg_mgr_free(&mgr);
	return 0;
}
