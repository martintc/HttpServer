
#include "packet_parser.h"

struct packet_request* parse_request(char* message) {
  struct packet_request* request = malloc(sizeof(struct packet_request));
  request->request_method = malloc(sizeof(char)*5);
  request->request_resource = malloc(sizeof(char)*100);
  request->host = malloc(sizeof(char)*32);

  char* nl_delim = "\r\n, ";
  char* space_delim = " ";
  char* line_token;
  char* token;

  for (line_token = strtok(message, nl_delim); ; line_token = strtok(NULL, nl_delim)) {
    if (line_token == NULL) {
      break;
    }
    printf("%s\n", line_token);
    if ((strcmp("GET", line_token)) == 0) {
      strcpy(request->request_method, "GET");
      line_token = strtok(NULL, nl_delim);
      strcpy(request->request_resource, line_token);
    }
    if ((strcmp("Host:", line_token)) == 0) {
      line_token = strtok(NULL, nl_delim);
      strcpy(request->host, line_token);
    }
    line_token = NULL;
  }


  return request;
}

void destroy_packet(struct packet_request* packet) {
  free(&packet->request_method);
  free(&packet->request_resource);
  free(&packet->host);
  free(packet);
}