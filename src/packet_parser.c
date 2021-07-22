
#include "packet_parser.h"

struct packet_request* parse_request(char* message) {
  struct packet_request* request = malloc(sizeof(struct packet_request));
  request->request_method = malloc(sizeof(char)*8);
  request->request_resource = malloc(sizeof(char)*128);
  request->request_resource[0] = '\0';
  request->host = malloc(sizeof(char)*32);

  char* delim = "\r\n, ";
  char* line_token;

  for (line_token = strtok(message, delim); ; line_token = strtok(NULL, delim)) {
    if (line_token == NULL) {
      break;
    }
    if ((strcmp("GET", line_token)) == 0) {
      strcpy(request->request_method, "GET");
      line_token = strtok(NULL, delim);
      stpcpy(request->request_resource, line_token);
    }
    if ((strcmp("Host:", line_token)) == 0) {
      line_token = strtok(NULL, delim);
      strcpy(request->host, line_token);
    }
    line_token = NULL;
  }

  return request;
}

void destroy_packet(struct packet_request* packet) {
  /* packet->request_method = NULL; */
  /* packet->request_resource = NULL; */
  /* packet->host = NULL; */
  /* free(packet->request_resource); */
  free(packet->request_method);
  free(packet->host);
  free(packet);
  packet = NULL;
}
