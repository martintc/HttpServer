#ifndef PACKET_PARSER
#define PACKET_PARSER

#include <stdio.h>
#include <string.h>

struct packet_request {
  char* request_method;
  char* request_resource;
  char* host;
};

struct packet_request* parse_request(char* message);

#endif
