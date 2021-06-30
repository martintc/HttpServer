#ifndef PACKET_PARSER
#define PACKET_PARSER

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct packet_request {
  char* request_method;
  char* request_resource;
  char* host;
};

struct packet_request* parse_request(char* message);

void destroy_packet(struct packet_request* packet);

#endif
