#include "packet_parser.h"

struct packet_request* parse_request(char* message) {
  struct packet_request* request = malloc(sizeof(struct packet_request));
  request->request_method = malloc(sizeof(char)*20);
  request->request_resource = malloc(sizeof(char)*100);
  request->host = malloc(sizeof(char)*32);

  char* nl_delim = "\r\n";
  char* space_delim = " ";
  char* line_token;
  char* token;

  /* line_token = strtok(message, nl_delim); */
  /* printf("%s\n", line_token); */
  // token = strtok(line_token, space_delim);
  //printf("%s\n", token);
  //token = strtok(NULL, space_delim);
  //printf("%s\n", token);

  for (line_token = strtok(message, nl_delim); ; line_token = strtok(NULL, nl_delim)) {
    if (line_token == NULL) {
      break;
    }
    printf("%s\n", line_token);
    for (token = strtok(line_token, space_delim); ; token = strtok(NULL, space_delim)) {
      if (token == NULL) {
        break;
      }
      printf("%s\n", token);
    }
  }

  printf("ta\n");


  //printf("%s %s\n%s", request->request_method, request->request_resource, request->host);

  return NULL;
  ///return request; // temp for testing
}
